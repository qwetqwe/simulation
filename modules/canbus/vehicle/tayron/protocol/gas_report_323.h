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

class Gasreport323 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::ChassisDetail> {
 public:
  static const int32_t ID;
  Gasreport323();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     ChassisDetail* chassis) const override;

 private:

  // config detail: {'name': 'gas_control_status', 'enum': {0: 'GAS_CONTROL_STATUS_INVALID', 1: 'GAS_CONTROL_STATUS_INTELLIGENCE', 2: 'GAS_CONTROL_STATUS_MANUAL', 3: 'GAS_CONTROL_STATUS_RESERVED'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 0, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  int gas_control_status(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'gas_pedal_status', 'offset': 0.0, 'precision': 0.39, 'len': 8, 'is_signed_var': False, 'physical_range': '[0|99.45]', 'bit': 16, 'type': 'double', 'order': 'intel', 'physical_unit': ''}
  double gas_pedal_status(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'gas_pedal_out_status', 'offset': 0.0, 'precision': 0.39, 'len': 8, 'is_signed_var': False, 'physical_range': '[0|99.45]', 'bit': 8, 'type': 'double', 'order': 'intel', 'physical_unit': ''}
  double gas_pedal_out_status(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'gas_fehler_status', 'enum': {0: 'GAS_FEHLER_STATUS_INVALID', 1: 'GAS_FEHLER_STATUS_NORMAL', 2: 'GAS_FEHLER_STATUS_FEHLER', 3: 'GAS_FEHLER_STATUS_RESERVED'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 2, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  int gas_fehler_status(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace tayron
}  // namespace canbus
}  // namespace apollo


