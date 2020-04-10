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

#include "modules/canbus/vehicle/tayron/protocol/gas_cmd_216.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace tayron {

using ::apollo::drivers::canbus::Byte;

const int32_t Gascmd216::ID = 0x216;

// public
Gascmd216::Gascmd216() { Reset(); }

uint32_t Gascmd216::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 10 * 1000; //changed by lx
  return PERIOD;
}

void Gascmd216::UpdateData(uint8_t* data) {
  for (int i=0;i<=7;i++)
    data[i]=0;  
  set_p_gas_pedal_cmd(data, gas_pedal_cmd_);
  set_p_gas_control_cmd(data, gas_control_cmd_);
}

void Gascmd216::Reset() {
  // TODO(All) :  you should check this manually
  gas_pedal_cmd_ = 0.0;
  gas_control_cmd_ = Gas_cmd_216::GAS_CONTROL_CMD_MANUAL;
}

Gascmd216* Gascmd216::set_gas_pedal_cmd(
    double gas_pedal_cmd) {
  gas_pedal_cmd_ = gas_pedal_cmd;
  return this;
 }

// config detail: {'name': 'gas_pedal_cmd', 'offset': 0.0, 'precision': 0.39, 'len': 8, 'is_signed_var': False, 'physical_range': '[0|99.45]', 'bit': 8, 'type': 'double', 'order': 'intel', 'physical_unit': '%'}
void Gascmd216::set_p_gas_pedal_cmd(uint8_t* data,
    double gas_pedal_cmd) {
  gas_pedal_cmd = ProtocolData::BoundedValue(0.0, 99.45, gas_pedal_cmd);
  uint8_t x = (uint8_t)(gas_pedal_cmd / 0.390000);

  Byte to_set(data + 1);
  to_set.set_value(x, 0, 8);
}

Gascmd216* Gascmd216::set_enable() {
  gas_control_cmd_ = Gas_cmd_216::GAS_CONTROL_CMD_INTELLIGENCE;
  return this;
}

Gascmd216* Gascmd216::set_disable() {
  gas_control_cmd_ = Gas_cmd_216::GAS_CONTROL_CMD_MANUAL;
  return this;
}

Gascmd216* Gascmd216::set_gas_control_cmd(
    Gas_cmd_216::Gas_control_cmdType gas_control_cmd) {
  gas_control_cmd_ = gas_control_cmd;
  return this;
 }

// config detail: {'name': 'gas_control_cmd', 'enum': {0: 'GAS_CONTROL_CMD_INVALID', 1: 'GAS_CONTROL_CMD_INTELLIGENCE', 2: 'GAS_CONTROL_CMD_MANUAL', 3: 'GAS_CONTROL_CMD_RESERVED'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 0, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
void Gascmd216::set_p_gas_control_cmd(uint8_t* data,
    Gas_cmd_216::Gas_control_cmdType gas_control_cmd) {
  int x = gas_control_cmd;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 2);
}

}  // namespace tayron
}  // namespace canbus
}  // namespace apollo
