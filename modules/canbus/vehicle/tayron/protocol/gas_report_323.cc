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

#include "modules/canbus/vehicle/tayron/protocol/gas_report_323.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace tayron {

using ::apollo::drivers::canbus::Byte;

Gasreport323::Gasreport323() {}
const int32_t Gasreport323::ID = 0x323;

void Gasreport323::Parse(const std::uint8_t* bytes, int32_t length,
                         ChassisDetail* chassis) const {
  chassis->mutable_check_response()->set_is_vcu_online(true);
  chassis->mutable_tayron()->mutable_gas_report_323()->set_gas_control_status(gas_control_status(bytes, length));
  chassis->mutable_tayron()->mutable_gas_report_323()->set_gas_pedal_status(gas_pedal_status(bytes, length));
  chassis->mutable_tayron()->mutable_gas_report_323()->set_gas_pedal_out_status(gas_pedal_out_status(bytes, length));
  chassis->mutable_tayron()->mutable_gas_report_323()->set_gas_fehler_status(gas_fehler_status(bytes, length));
}

// config detail: {'name': 'gas_control_status', 'enum': {0: 'GAS_CONTROL_STATUS_INVALID', 1: 'GAS_CONTROL_STATUS_INTELLIGENCE', 2: 'GAS_CONTROL_STATUS_MANUAL', 3: 'GAS_CONTROL_STATUS_RESERVED'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 0, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
int Gasreport323::gas_control_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 2);
  return x;
}

// config detail: {'name': 'gas_pedal_status', 'offset': 0.0, 'precision': 0.39, 'len': 8, 'is_signed_var': False, 'physical_range': '[0|99.45]', 'bit': 16, 'type': 'double', 'order': 'intel', 'physical_unit': ''}
double Gasreport323::gas_pedal_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.390000;
  return ret;
}

// config detail: {'name': 'gas_pedal_out_status', 'offset': 0.0, 'precision': 0.39, 'len': 8, 'is_signed_var': False, 'physical_range': '[0|99.45]', 'bit': 8, 'type': 'double', 'order': 'intel', 'physical_unit': ''}
double Gasreport323::gas_pedal_out_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.390000;
  return ret;
}

// config detail: {'name': 'gas_fehler_status', 'enum': {0: 'GAS_FEHLER_STATUS_INVALID', 1: 'GAS_FEHLER_STATUS_NORMAL', 2: 'GAS_FEHLER_STATUS_FEHLER', 3: 'GAS_FEHLER_STATUS_RESERVED'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 2, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
int Gasreport323::gas_fehler_status(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(2, 2);
  return x;
}
}  // namespace tayron
}  // namespace canbus
}  // namespace apollo
