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

#include "modules/canbus/vehicle/tayron/protocol/shift_report_324.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace tayron {

using ::apollo::drivers::canbus::Byte;

Shiftreport324::Shiftreport324() {}
const int32_t Shiftreport324::ID = 0x324;

void Shiftreport324::Parse(const std::uint8_t* bytes, int32_t length,
                         ChassisDetail* chassis) const {
  chassis->mutable_tayron()->mutable_shift_report_324()->set_shift_wh_position(shift_wh_position(bytes, length));
  int gear_pos=shift_gear_position_status(bytes, length);
  switch (gear_pos)
  {
  case 1:
    chassis->mutable_gear()->set_gear_state(Chassis::GEAR_PARKING);
    break;
  case 2:
    chassis->mutable_gear()->set_gear_state(Chassis::GEAR_REVERSE);
    break;
  case 3:
    chassis->mutable_gear()->set_gear_state(Chassis::GEAR_NEUTRAL);
    break;
  case 4:
    chassis->mutable_gear()->set_gear_state(Chassis::GEAR_DRIVE);
    break;
  default:
    chassis->mutable_gear()->set_gear_state(Chassis::GEAR_INVALID);
  }
  
  chassis->mutable_tayron()->mutable_shift_report_324()->set_shift_fehler_status(shift_fehler_status(bytes, length));
  int mode=shift_control_status(bytes, length);
  chassis->mutable_tayron()->mutable_shift_report_324()->set_shift_control_status(mode);
  if (mode==3)
    chassis->mutable_check_response()->set_is_gear_online(false);
  else
    chassis->mutable_check_response()->set_is_gear_online(true);
}

// config detail: {'name': 'shift_wh_position', 'enum': {0: 'SHIFT_WH_POSITION_N', 1: 'SHIFT_WH_POSITION_D', 2: 'SHIFT_WH_POSITION_R', 3: 'SHIFT_WH_POSITION_P', 4: 'SHIFT_WH_POSITION_NONE'}, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|15]', 'bit': 16, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
int Shiftreport324::shift_wh_position(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 4);
  return x;
}

// config detail: {'name': 'shift_gear_position_status', 'enum': {0: 'SHIFT_GEAR_POSITION_STATUS_N', 1: 'SHIFT_GEAR_POSITION_STATUS_D', 2: 'SHIFT_GEAR_POSITION_STATUS_R', 3: 'SHIFT_GEAR_POSITION_STATUS_P', 4: 'SHIFT_GEAR_POSITION_STATUS_NONE'}, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|15]', 'bit': 8, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
int Shiftreport324::shift_gear_position_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 4);
  return x;
}

// config detail: {'name': 'shift_fehler_status', 'enum': {0: 'SHIFT_FEHLER_STATUS_INVALID', 1: 'SHIFT_FEHLER_STATUS_NORMAL', 2: 'SHIFT_FEHLER_STATUS_FEHLER', 3: 'SHIFT_FEHLER_STATUS_RESERVED'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 3, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
int Shiftreport324::shift_fehler_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(3, 2);
  return x;
}

// config detail: {'name': 'shift_control_status', 'enum': {0: 'SHIFT_CONTROL_STATUS_INVALID', 1: 'SHIFT_CONTROL_STATUS_INTELLIGENCE', 2: 'SHIFT_CONTROL_STATUS_MANUAL', 3: 'SHIFT_CONTROL_STATUS_MANUALINTERVENE'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 0, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
int Shiftreport324::shift_control_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);
  return x;
}
}  // namespace tayron
}  // namespace canbus
}  // namespace apollo
