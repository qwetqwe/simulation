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

#pragma once


#include "modules/drivers/canbus/can_comm/protocol_data.h"
#include "modules/canbus/proto/chassis_detail.pb.h"

namespace apollo {
namespace canbus {
namespace tayron {

class Shiftreport324 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::ChassisDetail> {
 public:
  static const int32_t ID;
  Shiftreport324();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     ChassisDetail* chassis) const override;

 private:

  // config detail: {'name': 'shift_WH_position', 'enum': {0: 'SHIFT_WH_POSITION_N', 1: 'SHIFT_WH_POSITION_D', 2: 'SHIFT_WH_POSITION_R', 3: 'SHIFT_WH_POSITION_P', 4: 'SHIFT_WH_POSITION_NONE'}, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|15]', 'bit': 16, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  int shift_wh_position(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'shift_gear_position_status', 'enum': {0: 'SHIFT_GEAR_POSITION_STATUS_N', 1: 'SHIFT_GEAR_POSITION_STATUS_D', 2: 'SHIFT_GEAR_POSITION_STATUS_R', 3: 'SHIFT_GEAR_POSITION_STATUS_P', 4: 'SHIFT_GEAR_POSITION_STATUS_NONE'}, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|15]', 'bit': 8, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  int shift_gear_position_status(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'shift_fehler_status', 'enum': {0: 'SHIFT_FEHLER_STATUS_INVALID', 1: 'SHIFT_FEHLER_STATUS_NORMAL', 2: 'SHIFT_FEHLER_STATUS_FEHLER', 3: 'SHIFT_FEHLER_STATUS_RESERVED'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 3, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  int shift_fehler_status(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'shift_control_status', 'enum': {0: 'SHIFT_CONTROL_STATUS_INVALID', 1: 'SHIFT_CONTROL_STATUS_INTELLIGENCE', 2: 'SHIFT_CONTROL_STATUS_MANUAL', 3: 'SHIFT_CONTROL_STATUS_MANUALINTERVENE'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 0, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  int shift_control_status(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace tayron
}  // namespace canbus
}  // namespace apollo


