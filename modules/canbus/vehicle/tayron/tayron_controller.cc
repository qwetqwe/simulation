/* Copyright 2018 The Apollo Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "modules/canbus/vehicle/tayron/tayron_controller.h"

#include "modules/common/proto/vehicle_signal.pb.h"

#include "modules/canbus/vehicle/tayron/tayron_message_manager.h"
#include "modules/canbus/vehicle/vehicle_controller.h"
#include "cyber/common/log.h"
#include "modules/common/time/time.h"
#include "modules/drivers/canbus/can_comm/can_sender.h"
#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace tayron {

using ::apollo::drivers::canbus::ProtocolData;
using ::apollo::common::ErrorCode;
using ::apollo::control::ControlCommand;
using ::apollo::common::time::Clock;
namespace {

const int32_t kMaxFailAttempt = 10;
const int32_t CHECK_RESPONSE_STEER_UNIT_FLAG = 1;
const int32_t CHECK_RESPONSE_SPEED_UNIT_FLAG = 2;
}

ErrorCode TayronController::Init(
	const VehicleParameter& params,
	CanSender<::apollo::canbus::ChassisDetail> *const can_sender,
    MessageManager<::apollo::canbus::ChassisDetail> *const message_manager) {
  if (is_initialized_) {
    AINFO << "TayronController has already been initiated.";
    return ErrorCode::CANBUS_ERROR;
  }
  vehicle_params_.CopyFrom(
      common::VehicleConfigHelper::Instance()->GetConfig().vehicle_param());
  params_.CopyFrom(params);
  if (!params_.has_driving_mode()) {
    AERROR << "Vehicle conf pb not set driving_mode.";
    return ErrorCode::CANBUS_ERROR;
  }

  if (can_sender == nullptr) {
    return ErrorCode::CANBUS_ERROR;
  }
  can_sender_ = can_sender;

  if (message_manager == nullptr) {
    AERROR << "protocol manager is null.";
    return ErrorCode::CANBUS_ERROR;
  }
  message_manager_ = message_manager;

  // sender part
  brake_cmd_214_ = dynamic_cast<Brakecmd214*>
          (message_manager_->GetMutableProtocolDataById(Brakecmd214::ID));
  if (brake_cmd_214_ == nullptr) {
     AERROR << "Brakecmd214 does not exist in the TayronMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  gas_cmd_216_ = dynamic_cast<Gascmd216*>
          (message_manager_->GetMutableProtocolDataById(Gascmd216::ID));
  if (gas_cmd_216_ == nullptr) {
     AERROR << "Gascmd216 does not exist in the TayronMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  shift_cmd_217_ = dynamic_cast<Shiftcmd217*>
          (message_manager_->GetMutableProtocolDataById(Shiftcmd217::ID));
  if (shift_cmd_217_ == nullptr) {
     AERROR << "Shiftcmd217 does not exist in the TayronMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  steering_cmd_215_ = dynamic_cast<Steeringcmd215*>
          (message_manager_->GetMutableProtocolDataById(Steeringcmd215::ID));
  if (steering_cmd_215_ == nullptr) {
     AERROR << "Steeringcmd215 does not exist in the TayronMessageManager!";
     return ErrorCode::CANBUS_ERROR;
  }

  can_sender_->AddMessage(Brakecmd214::ID, brake_cmd_214_, false);
  can_sender_->AddMessage(Gascmd216::ID, gas_cmd_216_, false);
  can_sender_->AddMessage(Shiftcmd217::ID, shift_cmd_217_, false);
  can_sender_->AddMessage(Steeringcmd215::ID, steering_cmd_215_, false);

  // need sleep to ensure all messages received
  AINFO << "TayronController is initialized.";

  is_initialized_ = true;
  return ErrorCode::OK;
}

TayronController::~TayronController() {}

bool TayronController::Start() {
  if (!is_initialized_) {
    AERROR << "TayronController has NOT been initiated.";
    return false;
  }
  const auto& update_func = [this] { SecurityDogThreadFunc(); };
  thread_.reset(new std::thread(update_func));

  return true;
}

void TayronController::Stop() {
  if (!is_initialized_) {
    AERROR << "TayronController stops or starts improperly!";
    return;
  }

  if (thread_ != nullptr && thread_->joinable()) {
    thread_->join();
    thread_.reset();
    AINFO << "TayronController stopped.";
  }
}

Chassis TayronController::chassis() {
  chassis_.Clear();

  ChassisDetail chassis_detail;
  message_manager_->GetSensorData(&chassis_detail);

  // 21, 22, previously 1, 2
  if (driving_mode() == Chassis::EMERGENCY_MODE) {
    set_chassis_error_code(Chassis::NO_ERROR);
  }

  chassis_.set_driving_mode(driving_mode());
  chassis_.set_error_code(chassis_error_code());

  // 3
  chassis_.set_engine_started(true);
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
  // 4
  if (chassis_detail.has_ems() && chassis_detail.ems().has_engine_rpm()) {
    chassis_.set_engine_rpm(
        static_cast<float>(chassis_detail.ems().engine_rpm()));
  } else {
    chassis_.set_engine_rpm(0);
  }
  // 5

  if (chassis_detail.has_tayron() && chassis_detail.tayron().has_wheel_speed_4a0() &&
      chassis_detail.tayron().wheel_speed_4a0().has_br3_rad_kmh_vr()) {
    chassis_.mutable_wheel_speed()->set_is_wheel_spd_rr_valid(1);
    chassis_.mutable_wheel_speed()->set_wheel_spd_rr(
        chassis_detail.tayron().wheel_speed_4a0().br3_rad_kmh_hr());

    chassis_.mutable_wheel_speed()->set_is_wheel_spd_rl_valid(1);
    chassis_.mutable_wheel_speed()->set_wheel_spd_rl(
        chassis_detail.tayron().wheel_speed_4a0().br3_rad_kmh_hl());

    chassis_.mutable_wheel_speed()->set_is_wheel_spd_fr_valid(1);
    chassis_.mutable_wheel_speed()->set_wheel_spd_fr(
        chassis_detail.tayron().wheel_speed_4a0().br3_rad_kmh_vr());

    chassis_.mutable_wheel_speed()->set_is_wheel_spd_fl_valid(1);
    chassis_.mutable_wheel_speed()->set_wheel_spd_fl(
        chassis_detail.tayron().wheel_speed_4a0().br3_rad_kmh_vl());
    chassis_.set_speed_mps(
        static_cast<float>(chassis_.wheel_speed().wheel_spd_fl()+
        chassis_.wheel_speed().wheel_spd_fr()+
        chassis_.wheel_speed().wheel_spd_rl()+
        chassis_.wheel_speed().wheel_spd_rr())/4.0/3.6);  //km/h->m/s

  } else {
    chassis_.set_speed_mps(0);
  }

  if (chassis_detail.has_tayron() && chassis_detail.tayron().has_gas_report_323() &&
      chassis_detail.tayron().gas_report_323().has_gas_pedal_out_status()) {
    chassis_.set_throttle_percentage(
        static_cast<float>(chassis_detail.tayron().gas_report_323().gas_pedal_out_status()/100));
    chassis_.set_gas_status(chassis_detail.tayron().gas_report_323().gas_control_status());
  } else {
    chassis_.set_throttle_percentage(0);
  }
  // 9

  if (chassis_detail.has_tayron() && chassis_detail.tayron().has_brake_report_321() &&
      chassis_detail.tayron().brake_report_321().has_pedal_travel()) {
    chassis_.set_brake_percentage(
        static_cast<float>(chassis_detail.tayron().brake_report_321().pedal_travel()/100));
    chassis_.set_brake_status(chassis_detail.tayron().brake_report_321().brake_control_status());
  } else {
    chassis_.set_brake_percentage(0);
  }
  // 23, previously 10
  if (chassis_detail.has_gear() && chassis_detail.gear().has_gear_state()) {
    chassis_.set_gear_location(chassis_detail.gear().gear_state());
    chassis_.set_gear_status(chassis_detail.tayron().shift_report_324().shift_control_status());
  } else {
    chassis_.set_gear_location(Chassis::GEAR_NONE);
  }
  // 11

  if (chassis_detail.has_tayron() && chassis_detail.tayron().has_steering_report_322() &&
      chassis_detail.tayron().steering_report_322().has_steering_angle_status()){
    chassis_.set_steering_percentage(
        static_cast<float>(chassis_detail.tayron().steering_report_322().steering_angle_status() * 100.0 /
                           490));
  } else {
    chassis_.set_steering_percentage(0);
  }
  // 12
  if (chassis_detail.has_tayron() && chassis_detail.tayron().has_steering_report_322() &&
      chassis_detail.tayron().steering_report_322().has_steering_toque_status()) {
    chassis_.set_steering_torque_nm(
        static_cast<float>(chassis_detail.tayron().steering_report_322().steering_toque_status()));
    chassis_.set_steer_status(chassis_detail.tayron().steering_report_322().steering_control_status());
  } else {
    chassis_.set_steering_torque_nm(0);
  }
  if (driving_mode()!=Chassis::EMERGENCY_MODE)
    chassis_.mutable_engage_advice()->set_advice(
        apollo::common::EngageAdvice::READY_TO_ENGAGE);
  else {
    chassis_.mutable_engage_advice()->set_advice(
        apollo::common::EngageAdvice::DISALLOW_ENGAGE);
    chassis_.mutable_engage_advice()->set_reason(
        "CANBUS not ready, firmware error or emergency button pressed!");
  }
    
  
  return chassis_;
}



void TayronController::Emergency() {
  set_driving_mode(Chassis::EMERGENCY_MODE);
  ResetProtocol();
  clear_driver_override();
  set_chassis_error_code(Chassis::CHASSIS_ERROR);
}

ErrorCode TayronController::EnableAutoMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE) {
    AINFO << "already in COMPLETE_AUTO_DRIVE mode";
    return ErrorCode::OK;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION*/
  brake_cmd_214_->set_enable();
  gas_cmd_216_->set_enable();
  steering_cmd_215_->set_enable();
  shift_cmd_217_->set_enable();
  can_sender_->Update();
  const int32_t flag =
      CHECK_RESPONSE_STEER_UNIT_FLAG | CHECK_RESPONSE_SPEED_UNIT_FLAG;
  if (!CheckResponse(flag, true)) {
    AERROR << "Failed to switch to COMPLETE_AUTO_DRIVE mode.";
    Emergency();
    set_chassis_error_code(Chassis::CHASSIS_ERROR);
    return ErrorCode::CANBUS_ERROR;
  } else {
    set_driving_mode(Chassis::COMPLETE_AUTO_DRIVE);
    AINFO << "Switch to COMPLETE_AUTO_DRIVE mode ok.";
    return ErrorCode::OK;
  }
}

ErrorCode TayronController::DisableAutoMode() {
  ResetProtocol();
  can_sender_->Update();
  set_driving_mode(Chassis::COMPLETE_MANUAL);
  set_chassis_error_code(Chassis::NO_ERROR);
  AINFO << "Switch to COMPLETE_MANUAL ok.";
  return ErrorCode::OK;
}

ErrorCode TayronController::EnableSteeringOnlyMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
      driving_mode() == Chassis::AUTO_STEER_ONLY) {
    set_driving_mode(Chassis::AUTO_STEER_ONLY);
    AINFO << "Already in AUTO_STEER_ONLY mode";
    return ErrorCode::OK;
  }
  //return ErrorCode::OK;
  /* ADD YOUR OWN CAR CHASSIS OPERATION*/
  brake_cmd_214_->set_disable();
  gas_cmd_216_->set_disable();
  steering_cmd_215_->set_enable();

  can_sender_->Update();
  if (CheckResponse(CHECK_RESPONSE_STEER_UNIT_FLAG, true) == false) {
    AERROR << "Failed to switch to AUTO_STEER_ONLY mode.";
    Emergency();
    set_chassis_error_code(Chassis::CHASSIS_ERROR);
    return ErrorCode::CANBUS_ERROR;
  } else {
    set_driving_mode(Chassis::AUTO_STEER_ONLY);
    AINFO << "Switch to AUTO_STEER_ONLY mode ok.";
    return ErrorCode::OK;
  }
  
}

ErrorCode TayronController::EnableSpeedOnlyMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
      driving_mode() == Chassis::AUTO_SPEED_ONLY) {
    set_driving_mode(Chassis::AUTO_SPEED_ONLY);
    AINFO << "Already in AUTO_SPEED_ONLY mode";
    return ErrorCode::OK;
  }
  //return ErrorCode::OK;
  /* ADD YOUR OWN CAR CHASSIS OPERATION*/
  brake_cmd_214_->set_enable();
  gas_cmd_216_->set_enable();
  steering_cmd_215_->set_disable();

  can_sender_->Update();
  if (CheckResponse(CHECK_RESPONSE_SPEED_UNIT_FLAG, true) == false) {
    AERROR << "Failed to switch to AUTO_STEER_ONLY mode.";
    Emergency();
    set_chassis_error_code(Chassis::CHASSIS_ERROR);
    return ErrorCode::CANBUS_ERROR;
  } else {
    set_driving_mode(Chassis::AUTO_SPEED_ONLY);
    AINFO << "Switch to AUTO_SPEED_ONLY mode ok.";
    return ErrorCode::OK;
  }
}

// NEUTRAL, REVERSE, DRIVE
void TayronController::Gear(Chassis::GearPosition gear_position) {
  if (!(driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
        driving_mode() == Chassis::AUTO_SPEED_ONLY)) {
    AINFO << "this drive mode no need to set gear.";
    return;
  }
  //return;
  /* ADD YOUR OWN CAR CHASSIS OPERATION*/
  switch (gear_position) {
    case Chassis::GEAR_NEUTRAL: {
      shift_cmd_217_->set_gear_neutral();
      break;
    }
    case Chassis::GEAR_REVERSE: {
      shift_cmd_217_->set_gear_reverse();
      break;
    }
    case Chassis::GEAR_DRIVE: {
      shift_cmd_217_->set_gear_drive();
      break;
    }
    case Chassis::GEAR_PARKING: {
      shift_cmd_217_->set_gear_park();
      break;
    }
    /*
    case Chassis::GEAR_LOW: {
      shift_cmd_217_->set_gear_low();
      break;
    }
    */
    case Chassis::GEAR_NONE: {
      shift_cmd_217_->set_gear_none();
      break;
    }
    /*
    case Chassis::GEAR_INVALID: {
      AERROR << "Gear command is invalid!";
      shift_cmd_217_->set_gear_none();
      break;
    }
    */
    default: {
      shift_cmd_217_->set_gear_none();
      break;
    }
  }
}

// brake with new acceleration
// acceleration:0.00~99.99, unit:
// acceleration:0.0 ~ 7.0, unit:m/s^2
// acceleration_spd:60 ~ 100, suggest: 90
// -> pedal
void TayronController::Brake(double pedal) {
  // double real_value = params_.max_acc() * acceleration / 100;
  // TODO(All) :  Update brake value based on mode
  if (!(driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
        driving_mode() == Chassis::AUTO_SPEED_ONLY)) {
    AINFO << "The current drive mode does not need to set acceleration.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION*/
    brake_cmd_214_->set_brake_pedal_cmd(pedal);
}

// drive with old acceleration
// gas:0.00~99.99 unit:
void TayronController::Throttle(double pedal) {
  if (!(driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
        driving_mode() == Chassis::AUTO_SPEED_ONLY)) {
    AINFO << "The current drive mode does not need to set throttle pedal.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION*/
  gas_cmd_216_->set_gas_pedal_cmd(pedal);
}

// confirm the car is driven by acceleration command or throttle/brake pedal
// drive with acceleration/deceleration
// acc:-7.0 ~ 5.0, unit:m/s^2

void TayronController::Acceleration(double acc) {
  if (!(driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
        driving_mode() == Chassis::AUTO_SPEED_ONLY)) {
    AINFO << "The current drive mode does not need to set acceleration.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
}

// tayron default, -470 ~ 470, left:+, right:-
// need to be compatible with control module, so reverse
// steering with old angle speed
// angle:-99.99~0.00~99.99, unit:, left:-, right:+
void TayronController::Steer(double angle) {
  if (!(driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
        driving_mode() == Chassis::AUTO_STEER_ONLY)) {
    AINFO << "The current driving mode does not need to set steer.";
    return;
  }
  //const double real_angle = vehicle_params_.max_steer_angle() * angle / 100.0;
  // reverse sign
  /* ADD YOUR OWN CAR CHASSIS OPERATION*/
  const double real_angle = vehicle_params_.max_steer_angle() * angle / 100.0*180/M_PI;
  steering_cmd_215_->set_steering_angle_cmd(real_angle)->set_steering_v_angle_cmd(200);
}

// steering with new angle speed
// angle:-99.99~0.00~99.99, unit:, left:-, right:+
// angle_spd:0.00~99.99, unit:deg/s
void TayronController::Steer(double angle, double angle_spd) {
  if (!(driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
        driving_mode() == Chassis::AUTO_STEER_ONLY)) {
    AINFO << "The current driving mode does not need to set steer.";
    return;
  }
  /* ADD YOUR OWN CAR CHASSIS OPERATION*/
  const double real_angle = vehicle_params_.max_steer_angle() * angle / 100.0*180/M_PI;
  steering_cmd_215_->set_steering_angle_cmd(real_angle)
      ->set_steering_v_angle_cmd(200);
}

void TayronController::SetEpbBreak(const ControlCommand& command) {
  if (command.has_brake()) {
    // None
    brake_percentage_=command.brake();
  } 
}

void TayronController::SetBeam(const ControlCommand& command) {
  if (command.signal().high_beam()) {
    // None
  } else if (command.signal().low_beam()) {
    // None
  } else {
    // None
  }
}

void TayronController::SetHorn(const ControlCommand& command) {
  if (command.signal().horn()) {
    // None
  } else {
    // None
  }
}

void TayronController::SetTurningSignal(const ControlCommand& command) {
  // Set Turn Signal
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  auto signal = command.signal().turn_signal();
  if (signal == Signal::TURN_LEFT) {
    turnsignal_68_->set_turn_left();
  } else if (signal == Signal::TURN_RIGHT) {
    turnsignal_68_->set_turn_right();
  } else {
    turnsignal_68_->set_turn_none();
  }
  */
}

void TayronController::ResetProtocol() {
  message_manager_->ResetSendMessages();
}

bool TayronController::CheckChassisError() {
  /* ADD YOUR OWN CAR CHASSIS OPERATION
  */
  ChassisDetail chassis_detail;
  message_manager_->GetSensorData(&chassis_detail);

  int32_t error_cnt = 0;
  int32_t chassis_error_mask = 0;
  if (!chassis_detail.has_tayron() || !chassis_detail.tayron().has_steering_report_322()) {
    AERROR_EVERY(100) << "ChassisDetail has NO steering."
                      << chassis_detail.DebugString();
    return false;
  }
  // Steer fault
  bool steer_fault;
  if (chassis_detail.tayron().steering_report_322().steering_control_status()==0x7)
    steer_fault = true;
  else
    steer_fault = false; 

  if (!chassis_detail.has_tayron() || !chassis_detail.tayron().has_brake_report_321()) {
    AERROR_EVERY(100) << "ChassisDetail has NO brake."
                      << chassis_detail.DebugString();
    return false;
  }
  // Brake fault
  bool brake_fault;
  if (chassis_detail.tayron().brake_report_321().brake_fehler_status()==2)
    brake_fault =true;
  else
    brake_fault=false;

  if (!chassis_detail.has_tayron() || !chassis_detail.tayron().has_gas_report_323()) {
    AERROR_EVERY(100) << "ChassisDetail has NO gas."
                      << chassis_detail.DebugString();
    return false;
  }
  // Throttle fault
  bool throttle_fault;
  if (chassis_detail.tayron().gas_report_323().gas_fehler_status()==2)
    throttle_fault =true;
  else
    throttle_fault=false; 
  
  if (!chassis_detail.has_tayron() || !chassis_detail.tayron().has_shift_report_324()) {
    AERROR_EVERY(100) << "ChassisDetail has NO gear."
                      << chassis_detail.DebugString();
    return false;
  }
  // Gear fault
  bool gear_fault;
  if (chassis_detail.tayron().shift_report_324().shift_fehler_status()==2)
    gear_fault = true;
  else 
    gear_fault = false;

  if (steer_fault) {
    set_chassis_error_code(Chassis::CHASSIS_ERROR_ON_STEER);
    AERROR_EVERY(100) << "Steering fault detected: ";
  }

  if (brake_fault) {
    set_chassis_error_code(Chassis::CHASSIS_ERROR_ON_BRAKE);
    AERROR_EVERY(100) << "Brake fault detected: ";
  }

  if (throttle_fault) {
    set_chassis_error_code(Chassis::CHASSIS_ERROR_ON_THROTTLE);
    AERROR_EVERY(100) << "Throttle fault detected: ";
  }

  if (gear_fault) {
    set_chassis_error_code(Chassis::CHASSIS_ERROR_ON_GEAR);
    AERROR_EVERY(100) << "Gear fault detected: ";
  }

  if (steer_fault || brake_fault || throttle_fault || gear_fault) {
    return true;
  } 
  return false;
}

void TayronController::SecurityDogThreadFunc() {
  if (can_sender_ == nullptr) {
    AERROR << "Fail to run SecurityDogThreadFunc() because can_sender_ is "
              "nullptr.";
    return;
  }
  while (!can_sender_->IsRunning()) {
    std::this_thread::yield();
  }

  std::chrono::duration<double, std::micro> default_period{50000};
  int64_t start = absl::ToUnixMicros(Clock::Now());

  int32_t speed_ctrl_fail = 0;
  int32_t steer_ctrl_fail = 0;

  while (can_sender_->IsRunning()) {
    const Chassis::DrivingMode mode = driving_mode();
    bool emergency_mode = false;

    // 1. steer control check
    if ((mode == Chassis::COMPLETE_AUTO_DRIVE ||
         mode == Chassis::AUTO_STEER_ONLY) &&
        CheckResponse(CHECK_RESPONSE_STEER_UNIT_FLAG, false) == false) {
      ++steer_ctrl_fail;
      if (steer_ctrl_fail >= kMaxFailAttempt) {
        emergency_mode = true;
        set_chassis_error_code(Chassis::MANUAL_INTERVENTION);
      }
    } else {
      steer_ctrl_fail = 0;
    }

    // 2. speed control check
    if ((mode == Chassis::COMPLETE_AUTO_DRIVE ||
         mode == Chassis::AUTO_SPEED_ONLY) &&
        CheckResponse(CHECK_RESPONSE_SPEED_UNIT_FLAG, false) == false) {
      ++speed_ctrl_fail;
      if (speed_ctrl_fail >= kMaxFailAttempt) {
        emergency_mode = true;
        set_chassis_error_code(Chassis::MANUAL_INTERVENTION);
      }
    } else {
      speed_ctrl_fail = 0;
    }
    if (CheckChassisError()) {
      set_chassis_error_code(Chassis::CHASSIS_ERROR);
      emergency_mode = true;
    }

    if (emergency_mode && mode != Chassis::EMERGENCY_MODE) {
      Emergency();
    }
    int64_t end = absl::ToUnixMicros(Clock::Now());
    std::chrono::duration<double, std::micro> elapsed{end - start};
    if (elapsed < default_period) {
      std::this_thread::sleep_for(default_period - elapsed);
      start = absl::ToUnixMicros(Clock::Now());
    } else {
      AERROR
          << "Too much time consumption in ctrekController looping process:"
          << elapsed.count();
      start = end;
    }
  }
}

bool TayronController::CheckResponse(const int32_t flags, bool need_wait) {
  // for Tayron, CheckResponse commonly takes 300ms. We leave a 100ms buffer
  // for it.
  int32_t retry_num = 20;
  ChassisDetail chassis_detail;
  bool is_eps_online = false;
  bool is_vcu_online = false;
  bool is_esp_online = false;
  bool is_gear_online = false;
  bool check_ok = false;

  do {
    if (message_manager_->GetSensorData(&chassis_detail) != ErrorCode::OK) {
      AERROR << "get chassis detail failed.";
      return false;
    }
    check_ok = true;
    if (flags) {
      is_eps_online = chassis_detail.has_check_response() &&
                      chassis_detail.check_response().has_is_eps_online() &&
                      chassis_detail.check_response().is_eps_online();
      check_ok = check_ok && is_eps_online;
    }

    if (flags) {
      is_vcu_online = chassis_detail.has_check_response() &&
                      chassis_detail.check_response().has_is_vcu_online() &&
                      chassis_detail.check_response().is_vcu_online();
      is_esp_online = chassis_detail.has_check_response() &&
                      chassis_detail.check_response().has_is_esp_online() &&
                      chassis_detail.check_response().is_esp_online();
      is_gear_online= chassis_detail.has_check_response() &&
                      chassis_detail.check_response().has_is_gear_online() &&
                      chassis_detail.check_response().is_gear_online();
      is_gear_online = true;  // for debug 
      check_ok = check_ok && is_vcu_online && is_esp_online && is_gear_online;
    }
    if (check_ok) {
      return true;
    } else {
      AINFO << "Need to check response again.";
    }
    if (need_wait) {
      --retry_num;
      std::this_thread::sleep_for(
          std::chrono::duration<double, std::milli>(20));
    }
  } while (need_wait && retry_num);

  AWARN << "check_response fail: is_eps_online:" << is_eps_online
        << ", is_vcu_online:" << is_vcu_online
        << ", is_esp_online:" << is_esp_online
        << ", is_gear_online:"<<is_gear_online;
  return false;
}

void TayronController::set_chassis_error_mask(const int32_t mask) {
  std::lock_guard<std::mutex> lock(chassis_mask_mutex_);
  chassis_error_mask_ = mask;
}

int32_t TayronController::chassis_error_mask() {
  std::lock_guard<std::mutex> lock(chassis_mask_mutex_);
  return chassis_error_mask_;
}

Chassis::ErrorCode TayronController::chassis_error_code() {
  std::lock_guard<std::mutex> lock(chassis_error_code_mutex_);
  return chassis_error_code_;
}

void TayronController::set_chassis_error_code(
    const Chassis::ErrorCode& error_code) {
  std::lock_guard<std::mutex> lock(chassis_error_code_mutex_);
  chassis_error_code_ = error_code;
}
void TayronController::clear_driver_override()
{
  shift_cmd_217_->set_driver_override();
  brake_cmd_214_->set_driver_override();
  //light_218_->set_driver_override();
  steering_cmd_215_->set_driver_override();
}

}  // namespace tayron
}  // namespace canbus
}  // namespace apollo
