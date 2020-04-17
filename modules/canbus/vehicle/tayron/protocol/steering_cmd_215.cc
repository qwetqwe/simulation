/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "modules/canbus/vehicle/tayron/protocol/steering_cmd_215.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace tayron {

using ::apollo::drivers::canbus::Byte;

const int32_t Steeringcmd215::ID = 0x215;

// public
Steeringcmd215::Steeringcmd215() { Reset(); }

uint32_t Steeringcmd215::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 10 * 1000; //changed by lx
  return PERIOD;
}

void Steeringcmd215::UpdateData(uint8_t* data) {
  set_p_steering_angle_cmd(data, steering_angle_cmd_);
  set_p_steering_control_cmd(data, steering_control_cmd_);
  set_p_steering_v_angle_cmd(data, steering_v_angle_cmd_);
  set_p_steering_angle_valid_cmd(data, steering_angle_valid_cmd_);
  set_p_steering_control_counter_cmd(data, steering_control_counter_cmd_);
  set_p_steering_dcu_vcu_state(data, steering_dcu_vcu_state_);
  set_p_steering_lka_en_cmd(data, Steering_cmd_215::STEERING_LKA_EN_CMD_LKAUNABLE);//转向助力先不用
  set_p_steering_lka_overlay_tq_cmd(data, 0.00);//转向助力先不用
}

void Steeringcmd215::Reset() {
  // TODO(All) :  you should check this manually
  steering_angle_cmd_ = 0.0;
  steering_control_cmd_ = Steering_cmd_215::STEERING_CONTROL_CMD_EPSMODEORDER;
  steering_v_angle_cmd_ = 0.0;
  steering_lka_en_cmd_ = Steering_cmd_215::STEERING_LKA_EN_CMD_LKAUNABLE;
  steering_lka_overlay_tq_cmd_ = 0.0;
  steering_control_counter_cmd_ = 0;
  steering_dcu_vcu_state_ = Steering_cmd_215::STEERING_DCU_VCU_STATE_VALID;
}

Steeringcmd215* Steeringcmd215::set_steering_angle_cmd(
    double steering_angle_cmd) {
  steering_angle_cmd_ = steering_angle_cmd;
  return this;
 }

Steeringcmd215* Steeringcmd215::set_enable() {
  steering_control_cmd_ = Steering_cmd_215::STEERING_CONTROL_CMD_AUTOSTEERINGMODEORDER;
  steering_angle_valid_cmd_=Steering_cmd_215::STEERING_ANGLE_VALID_CMD_VALID;
  return this;
}

Steeringcmd215* Steeringcmd215::set_disable() {
  steering_control_cmd_ = Steering_cmd_215::STEERING_CONTROL_CMD_EPSMODEORDER;
  steering_angle_valid_cmd_=Steering_cmd_215::STEERING_ANGLE_VALID_CMD_INVALID;
  return this;
}

Steeringcmd215* Steeringcmd215::set_driver_override() {
  steering_control_cmd_ = Steering_cmd_215::STEERING_CONTROL_CMD_INTERVENTRECOVERORDER;
  return this;
}

// config detail: {'name': 'steering_Angle_cmd', 'offset': -870.0, 'precision': 0.1, 'len': 16, 'is_signed_var': False, 'physical_range': '[-870|870]', 'bit': 16, 'type': 'double', 'order': 'intel', 'physical_unit': 'deg'}
void Steeringcmd215::set_p_steering_angle_cmd(uint8_t* data,
    double steering_angle_cmd) {
  steering_angle_cmd = ProtocolData::BoundedValue(-870.0, 870.0, steering_angle_cmd);
  int x = (steering_angle_cmd + 870.000000) / 0.100000;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(data + 2);
  to_set0.set_value(t, 0, 8);
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(data + 3);
  to_set1.set_value(t, 0, 8);
}


Steeringcmd215* Steeringcmd215::set_steering_control_cmd(
    Steering_cmd_215::Steering_control_cmdType steering_control_cmd) {
  steering_control_cmd_ = steering_control_cmd;
  return this;
 }

// config detail: {'name': 'steering_control_cmd', 'enum': {0: 'STEERING_CONTROL_CMD_STANDBYMODEORDER', 1: 'STEERING_CONTROL_CMD_AUTOSTEERINGMODEORDER', 4: 'STEERING_CONTROL_CMD_EPSMODEORDER', 5: 'STEERING_CONTROL_CMD_INTERVENTRECOVERORDER', 6: 'STEERING_CONTROL_CMD_CLEARFAULTORDER'}, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|15]', 'bit': 8, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
void Steeringcmd215::set_p_steering_control_cmd(uint8_t* data,
    Steering_cmd_215::Steering_control_cmdType steering_control_cmd) {
  int x = steering_control_cmd;

  Byte to_set(data + 1);
  to_set.set_value(x, 0, 4);
}


Steeringcmd215* Steeringcmd215::set_steering_v_angle_cmd(
    double steering_v_angle_cmd) {
  steering_v_angle_cmd_ = steering_v_angle_cmd;
  return this;
 }

// config detail: {'name': 'steering_V_angle_cmd', 'offset': 0.0, 'precision': 4.0, 'len': 8, 'is_signed_var': False, 'physical_range': '[0|1016]', 'bit': 32, 'type': 'double', 'order': 'intel', 'physical_unit': ''}
void Steeringcmd215::set_p_steering_v_angle_cmd(uint8_t* data,
    double steering_v_angle_cmd) {
  steering_v_angle_cmd = ProtocolData::BoundedValue(0.0, 1016.0, steering_v_angle_cmd);
  int x = steering_v_angle_cmd / 4.000000;

  Byte to_set(data + 4);
  to_set.set_value(x, 0, 8);
}


Steeringcmd215* Steeringcmd215::set_steering_angle_valid_cmd(
    Steering_cmd_215::Steering_angle_valid_cmdType steering_angle_valid_cmd) {
  steering_angle_valid_cmd_ = steering_angle_valid_cmd;
  return this;
 }

// config detail: {'name': 'steering_Angle_valid_cmd', 'enum': {0: 'STEERING_ANGLE_VALID_CMD_INVALID', 1: 'STEERING_ANGLE_VALID_CMD_VALID'}, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|1]', 'bit': 12, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
void Steeringcmd215::set_p_steering_angle_valid_cmd(uint8_t* data,
    Steering_cmd_215::Steering_angle_valid_cmdType steering_angle_valid_cmd) {
  int x = steering_angle_valid_cmd;

  Byte to_set(data + 1);
  to_set.set_value(x, 4, 1);
}


Steeringcmd215* Steeringcmd215::set_steering_lka_en_cmd(
    Steering_cmd_215::Steering_lka_en_cmdType steering_lka_en_cmd) {
  steering_lka_en_cmd_ = steering_lka_en_cmd;
  return this;
 }

// config detail: {'name': 'steering_LKA_EN_cmd', 'enum': {0: 'STEERING_LKA_EN_CMD_LKAUNABLE', 1: 'STEERING_LKA_EN_CMD_LKAENABLE'}, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|1]', 'bit': 56, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
void Steeringcmd215::set_p_steering_lka_en_cmd(uint8_t* data,
    Steering_cmd_215::Steering_lka_en_cmdType steering_lka_en_cmd) {
  int x = steering_lka_en_cmd;

  Byte to_set(data + 7);
  to_set.set_value(x, 0, 1);
}


Steeringcmd215* Steeringcmd215::set_steering_lka_overlay_tq_cmd(
    double steering_lka_overlay_tq_cmd) {
  steering_lka_overlay_tq_cmd_ = steering_lka_overlay_tq_cmd;
  return this;
 }

// config detail: {'name': 'steering_LKA_Overlay_TQ_cmd', 'offset': -12.8, 'precision': 0.1, 'len': 8, 'is_signed_var': False, 'physical_range': '[-12.8|12.7]', 'bit': 40, 'type': 'double', 'order': 'intel', 'physical_unit': 'Nm'}
void Steeringcmd215::set_p_steering_lka_overlay_tq_cmd(uint8_t* data,
    double steering_lka_overlay_tq_cmd) {
  steering_lka_overlay_tq_cmd = ProtocolData::BoundedValue(-12.8, 12.7, steering_lka_overlay_tq_cmd);
  int x = (steering_lka_overlay_tq_cmd - -12.800000) / 0.100000;

  Byte to_set(data + 5);
  to_set.set_value(x, 0, 8);
}


Steeringcmd215* Steeringcmd215::set_steering_control_counter_cmd(
    int steering_control_counter_cmd) {
  steering_control_counter_cmd_ = steering_control_counter_cmd;
  return this;
 }

// config detail: {'name': 'steering_control_counter_cmd', 'offset': 0.0, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'physical_range': '[0|15]', 'bit': 4, 'type': 'int', 'order': 'intel', 'physical_unit': ''}
void Steeringcmd215::set_p_steering_control_counter_cmd(uint8_t* data,
    int steering_control_counter_cmd) {
  steering_control_counter_cmd = ProtocolData::BoundedValue(0, 15, steering_control_counter_cmd);
  int x = steering_control_counter_cmd;

  Byte to_set(data + 0);
  to_set.set_value(x, 4, 4);
}


Steeringcmd215* Steeringcmd215::set_steering_dcu_vcu_state(
    Steering_cmd_215::Steering_dcu_vcu_stateType steering_dcu_vcu_state) {
  steering_dcu_vcu_state_ = steering_dcu_vcu_state;
  return this;
 }

// config detail: {'name': 'steering_DCU_VCU_state', 'enum': {0: 'STEERING_DCU_VCU_STATE_INVALID', 1: 'STEERING_DCU_VCU_STATE_VALID'}, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|1]', 'bit': 13, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
void Steeringcmd215::set_p_steering_dcu_vcu_state(uint8_t* data,
    Steering_cmd_215::Steering_dcu_vcu_stateType steering_dcu_vcu_state) {
  int x = steering_dcu_vcu_state;

  Byte to_set(data + 1);
  to_set.set_value(x, 5, 1);
}

}  // namespace tayron
}  // namespace canbus
}  // namespace apollo
