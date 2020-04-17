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

#include "modules/canbus/vehicle/tayron/protocol/brake_cmd_214.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace tayron {

using ::apollo::drivers::canbus::Byte;

const int32_t Brakecmd214::ID = 0x214;

// public
Brakecmd214::Brakecmd214() { Reset(); }

uint32_t Brakecmd214::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 10 * 1000; //changed by lx
  return PERIOD;
}

void Brakecmd214::UpdateData(uint8_t* data) {
  for (int i=0;i<=7;i++)
    data[i]=0;  
  set_p_brake_pedal_cmd(data, brake_pedal_cmd_);
  set_p_brake_control_cmd(data, brake_control_cmd_);
}

void Brakecmd214::Reset() {
  // TODO(All) :  you should check this manually
  brake_pedal_cmd_ = 0.0;
  brake_control_cmd_ = Brake_cmd_214::BRAKE_CONTROL_CMD_MANUAL;
}

Brakecmd214* Brakecmd214::set_brake_pedal_cmd(
    double brake_pedal_cmd) {
  brake_pedal_cmd_ = brake_pedal_cmd;
  return this;
 }

Brakecmd214* Brakecmd214::set_enable() {
  brake_control_cmd_ = Brake_cmd_214::BRAKE_CONTROL_CMD_INTELLIGENCE;
  return this;
}

Brakecmd214* Brakecmd214::set_disable() {
  brake_control_cmd_ = Brake_cmd_214::BRAKE_CONTROL_CMD_MANUAL;
  return this;
}
Brakecmd214* Brakecmd214::set_driver_override(){
  brake_control_cmd_ = Brake_cmd_214::BRAKE_CONTROL_CMD_INTERVENERECOVERY;
  return this;
}

// config detail: {'name': 'brake_pedal_cmd', 'offset': 0.0, 'precision': 0.005, 'len': 8, 'is_signed_var': False, 'physical_range': '[0|100]', 'bit': 0, 'type': 'double', 'order': 'intel', 'physical_unit': ''}
void Brakecmd214::set_p_brake_pedal_cmd(uint8_t* data,
    double brake_pedal_cmd) {
  brake_pedal_cmd = ProtocolData::BoundedValue(0.0, 100.0, brake_pedal_cmd/100.0);
  int x = brake_pedal_cmd / 0.005000;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 8);
}


Brakecmd214* Brakecmd214::set_brake_control_cmd(
    Brake_cmd_214::Brake_control_cmdType brake_control_cmd) {
  brake_control_cmd_ = brake_control_cmd;
  return this;
 }

// config detail: {'name': 'brake_control_cmd', 'enum': {0: 'BRAKE_CONTROL_CMD_INVALID', 1: 'BRAKE_CONTROL_CMD_INTELLIGENCE', 2: 'BRAKE_CONTROL_CMD_MANUAL', 3: 'BRAKE_CONTROL_CMD_INTERVENERECOVERY'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 8, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
void Brakecmd214::set_p_brake_control_cmd(uint8_t* data,
    Brake_cmd_214::Brake_control_cmdType brake_control_cmd) {
  int x = brake_control_cmd;

  Byte to_set(data + 1);
  to_set.set_value(x, 0, 2);
}

}  // namespace tayron
}  // namespace canbus
}  // namespace apollo
