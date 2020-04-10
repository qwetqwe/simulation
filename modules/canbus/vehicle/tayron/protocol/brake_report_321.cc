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

#include "modules/canbus/vehicle/tayron/protocol/brake_report_321.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace tayron {

using ::apollo::drivers::canbus::Byte;

Brakereport321::Brakereport321() {}
const int32_t Brakereport321::ID = 0x321;

void Brakereport321::Parse(const std::uint8_t* bytes, int32_t length,
                         ChassisDetail* chassis) const {
  chassis->mutable_tayron()->mutable_brake_report_321()->set_pu_pressure(pu_pressure(bytes, length));
  chassis->mutable_tayron()->mutable_brake_report_321()->set_pedal_travel(pedal_travel(bytes, length));
  chassis->mutable_brake()->set_brake_output(pedal_travel(bytes, length));
  chassis->mutable_tayron()->mutable_brake_report_321()->set_brake_pedal_status(brake_pedal_status(bytes, length));
  chassis->mutable_tayron()->mutable_brake_report_321()->set_brake_fehler_status(brake_fehler_status(bytes, length));
  int mode=brake_control_status(bytes, length);
  chassis->mutable_tayron()->mutable_brake_report_321()->set_brake_control_status(mode);
  if (mode==3)
    chassis->mutable_check_response()->set_is_esp_online(false);
  else
    chassis->mutable_check_response()->set_is_esp_online(true);
}

// config detail: {'name': 'pu_pressure', 'offset': 0.0, 'precision': 0.1, 'len': 12, 'is_signed_var': True, 'physical_range': '[0|409.5]', 'bit': 40, 'type': 'double', 'order': 'intel', 'physical_unit': 'bar'}
double Brakereport321::pu_pressure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 5);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 20;
  x >>= 20;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'name': 'pedal_travel', 'offset': -20.0, 'precision': 0.1, 'len': 16, 'is_signed_var': True, 'physical_range': '[0|0]', 'bit': 24, 'type': 'double', 'order': 'intel', 'physical_unit': ''}
double Brakereport321::pedal_travel(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 3);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  double ret = x * 0.100000 + -20.000000;
  return ret;
}

// config detail: {'name': 'brake_pedal_status', 'enum': {0: 'BRAKE_PEDAL_STATUS_WIRECONTROLUNABLE', 1: 'BRAKE_PEDAL_STATUS_WIRECONTROLENABLE', 2: 'BRAKE_PEDAL_STATUS_MANUALUNABLE', 3: 'BRAKE_PEDAL_STATUS_MANUALENABLE'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 0, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
int Brakereport321::brake_pedal_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);
  return x;
}

// config detail: {'name': 'brake_fehler_status', 'enum': {0: 'BRAKE_FEHLER_STATUS_INVALID', 1: 'BRAKE_FEHLER_STATUS_NORMAL', 2: 'BRAKE_FEHLER_STATUS_FEHLER', 3: 'BRAKE_FEHLER_STATUS_RESERVED'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 11, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
int Brakereport321::brake_fehler_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(3, 2);
  return x;
}

// config detail: {'name': 'brake_control_status', 'enum': {0: 'BRAKE_CONTROL_STATUS_INITIAL', 1: 'BRAKE_CONTROL_STATUS_INTELLIGENCE', 2: 'BRAKE_CONTROL_STATUS_MANUAL', 3: 'BRAKE_CONTROL_STATUS_MANUALINTERVENE', 4: 'BRAKE_CONTROL_STATUS_ERROR', 5: 'BRAKE_CONTROL_STATUS_ERRORRECOVERY'}, 'precision': 1.0, 'len': 3, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|5]', 'bit': 8, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
int Brakereport321::brake_control_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 3);
  return x;
}
}  // namespace tayron
}  // namespace canbus
}  // namespace apollo
