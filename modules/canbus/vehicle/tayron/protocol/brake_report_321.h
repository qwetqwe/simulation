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

class Brakereport321 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::ChassisDetail> {
 public:
  static const int32_t ID;
  Brakereport321();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     ChassisDetail* chassis) const override;

 private:

  // config detail: {'name': 'PU_Pressure', 'offset': 0.0, 'precision': 0.1, 'len': 12, 'is_signed_var': True, 'physical_range': '[0|409.5]', 'bit': 40, 'type': 'double', 'order': 'intel', 'physical_unit': 'bar'}
  double pu_pressure(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'pedal_travel', 'offset': -20.0, 'precision': 0.1, 'len': 16, 'is_signed_var': True, 'physical_range': '[0|0]', 'bit': 24, 'type': 'double', 'order': 'intel', 'physical_unit': ''}
  double pedal_travel(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'brake_pedal_status', 'enum': {0: 'BRAKE_PEDAL_STATUS_WIRECONTROLUNABLE', 1: 'BRAKE_PEDAL_STATUS_WIRECONTROLENABLE', 2: 'BRAKE_PEDAL_STATUS_MANUALUNABLE', 3: 'BRAKE_PEDAL_STATUS_MANUALENABLE'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 0, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  int brake_pedal_status(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'brake_fehler_status', 'enum': {0: 'BRAKE_FEHLER_STATUS_INVALID', 1: 'BRAKE_FEHLER_STATUS_NORMAL', 2: 'BRAKE_FEHLER_STATUS_FEHLER', 3: 'BRAKE_FEHLER_STATUS_RESERVED'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 11, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  int brake_fehler_status(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'brake_control_status', 'enum': {0: 'BRAKE_CONTROL_STATUS_INITIAL', 1: 'BRAKE_CONTROL_STATUS_INTELLIGENCE', 2: 'BRAKE_CONTROL_STATUS_MANUAL', 3: 'BRAKE_CONTROL_STATUS_MANUALINTERVENE', 4: 'BRAKE_CONTROL_STATUS_ERROR', 5: 'BRAKE_CONTROL_STATUS_ERRORRECOVERY'}, 'precision': 1.0, 'len': 3, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|5]', 'bit': 8, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  int brake_control_status(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace tayron
}  // namespace canbus
}  // namespace apollo


