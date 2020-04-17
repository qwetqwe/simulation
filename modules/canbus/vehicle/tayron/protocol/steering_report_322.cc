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

#include "modules/canbus/vehicle/tayron/protocol/steering_report_322.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace tayron {

using ::apollo::drivers::canbus::Byte;

Steeringreport322::Steeringreport322() {}
const int32_t Steeringreport322::ID = 0x322;

void Steeringreport322::Parse(const std::uint8_t* bytes, int32_t length,
                         ChassisDetail* chassis) const {
  chassis->mutable_tayron()->mutable_steering_report_322()->set_steering_angle_status(steering_angle_status(bytes, length));
  int mode=steering_control_status(bytes, length);
  chassis->mutable_tayron()->mutable_steering_report_322()->set_steering_control_status(mode);
  if (mode==5)
    chassis->mutable_check_response()->set_is_eps_online(false);
  else
    chassis->mutable_check_response()->set_is_eps_online(true);
  chassis->mutable_tayron()->mutable_steering_report_322()->set_steering_toque_status(steering_toque_status(bytes, length));
  chassis->mutable_tayron()->mutable_steering_report_322()->set_steering_v_angle_status(steering_v_angle_status(bytes, length));
  chassis->mutable_tayron()->mutable_steering_report_322()->set_steering_counter_status(steering_counter_status(bytes, length));
  chassis->mutable_tayron()->mutable_steering_report_322()->set_steering_real_current_status(steering_real_current_status(bytes, length));
  chassis->mutable_tayron()->mutable_steering_report_322()->set_steering_ref_current_status(steering_ref_current_status(bytes, length));
}

// config detail: {'name': 'steering_angle_status', 'offset': -870.0, 'precision': 0.1, 'len': 16, 'is_signed_var': False, 'physical_range': '[-870|870]', 'bit': 0, 'type': 'double', 'order': 'intel', 'physical_unit': 'deg'}
double Steeringreport322::steering_angle_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000 + -870.000000;
  return ret;
}

// config detail: {'name': 'steering_control_status', 'enum': {0: 'STEERING_CONTROL_STATUS_STANDBYMODE', 1: 'STEERING_CONTROL_STATUS_AUTOSTEERINGMODE', 3: 'STEERING_CONTROL_STATUS_LKAMODE', 4: 'STEERING_CONTROL_STATUS_EPSMODE', 5: 'STEERING_CONTROL_STATUS_MANUALINTERVENTMODE', 6: 'STEERING_CONTROL_STATUS_WARNINGMODE', 7: 'STEERING_CONTROL_STATUS_ERRORMODE'}, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|15]', 'bit': 60, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
int Steeringreport322::steering_control_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 4);
  return x;
}

// config detail: {'name': 'steering_toque_status', 'offset': -15.0, 'precision': 0.12, 'len': 8, 'is_signed_var': False, 'physical_range': '[-15|15.6]', 'bit': 24, 'type': 'double', 'order': 'intel', 'physical_unit': 'Nm'}
double Steeringreport322::steering_toque_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.120000 + -15.000000;
  return ret;
}

// config detail: {'name': 'steering_v_angle_status', 'offset': 0.0, 'precision': 4.0, 'len': 8, 'is_signed_var': False, 'physical_range': '[0|1016]', 'bit': 16, 'type': 'double', 'order': 'intel', 'physical_unit': ''}
double Steeringreport322::steering_v_angle_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 4.000000;
  return ret;
}

// config detail: {'name': 'steering_counter_status', 'offset': 0.0, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'physical_range': '[0|15]', 'bit': 56, 'type': 'int', 'order': 'intel', 'physical_unit': ''}
int Steeringreport322::steering_counter_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'name': 'steering_real_current_status', 'offset': -160.0, 'precision': 0.08, 'len': 12, 'is_signed_var': False, 'physical_range': '[-160|167.6]', 'bit': 44, 'type': 'double', 'order': 'intel', 'physical_unit': 'A'}
double Steeringreport322::steering_real_current_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 5);
  int32_t t = t1.get_byte(4, 4);
  x <<= 4;
  x |= t;

  double ret = x * 0.080000 + -160.000000;
  return ret;
}

// config detail: {'name': 'steering_ref_current_status', 'offset': -160.0, 'precision': 0.08, 'len': 12, 'is_signed_var': False, 'physical_range': '[-160|167.6]', 'bit': 32, 'type': 'double', 'order': 'intel', 'physical_unit': 'A'}
double Steeringreport322::steering_ref_current_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 4);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.080000 + -160.000000;
  return ret;
}
}  // namespace tayron
}  // namespace canbus
}  // namespace apollo
