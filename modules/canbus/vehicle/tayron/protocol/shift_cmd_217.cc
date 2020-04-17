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

#include "modules/canbus/vehicle/tayron/protocol/shift_cmd_217.h"

#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace canbus {
namespace tayron {

using ::apollo::drivers::canbus::Byte;

const int32_t Shiftcmd217::ID = 0x217;

// public
Shiftcmd217::Shiftcmd217() { Reset(); }

uint32_t Shiftcmd217::GetPeriod() const {
  // TODO(All) :  modify every protocol's period manually
  static const uint32_t PERIOD = 10 * 1000; //manually changed by lx
  return PERIOD;
}

void Shiftcmd217::UpdateData(uint8_t* data) {
  for (int i=0;i<=7;i++)
    data[i]=0;
  set_p_shift_gear_position_cmd(data, shift_gear_position_cmd_);
  set_p_shift_control_cmd(data, shift_control_cmd_);
}

void Shiftcmd217::Reset() {
  // TODO(All) :  you should check this manually
  shift_gear_position_cmd_ = 3;
  shift_control_cmd_ = Shift_cmd_217::SHIFT_CONTROL_CMD_MANUAL;
}

Shiftcmd217* Shiftcmd217::set_shift_gear_position_cmd(
    int shift_gear_position_cmd) {
  shift_gear_position_cmd_ = shift_gear_position_cmd;
  return this;
 }

Shiftcmd217* Shiftcmd217::set_shift_control_cmd(
    Shift_cmd_217::Shift_control_cmdType shift_control_cmd) {
  shift_control_cmd_ = shift_control_cmd;
  return this;
 }

Shiftcmd217* Shiftcmd217::set_gear_none() {
  shift_gear_position_cmd_ = 0;
  return this;
}

Shiftcmd217* Shiftcmd217::set_gear_park() {
  shift_gear_position_cmd_ = 1;
  return this;
}

Shiftcmd217* Shiftcmd217::set_gear_reverse() {
  shift_gear_position_cmd_ = 2;
  return this;
}

Shiftcmd217* Shiftcmd217::set_gear_neutral() {
  shift_gear_position_cmd_ = 3;
  return this;
}

Shiftcmd217* Shiftcmd217::set_gear_drive() {
  shift_gear_position_cmd_ = 4;
  return this;
}

Shiftcmd217* Shiftcmd217::set_enable() {
	shift_control_cmd_ = Shift_cmd_217::SHIFT_CONTROL_CMD_INTELLIGENCE;
	return this;
}

Shiftcmd217* Shiftcmd217::set_disable() {
	shift_control_cmd_ = Shift_cmd_217::SHIFT_CONTROL_CMD_MANUAL;
	return this;
}
Shiftcmd217* Shiftcmd217::set_driver_override() {
  shift_control_cmd_ = Shift_cmd_217::SHIFT_CONTROL_CMD_MANUALINTERVENERECOVERY;
	return this;
}


// config detail: {'name': 'shift_gear_position_cmd', 'enum': {0: 'SHIFT_GEAR_POSITION_CMD_N', 1: 'SHIFT_GEAR_POSITION_CMD_D', 2: 'SHIFT_GEAR_POSITION_CMD_R', 3: 'SHIFT_GEAR_POSITION_CMD_P', 4: 'SHIFT_GEAR_POSITION_CMD_NONE'}, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|7]', 'bit': 8, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
void Shiftcmd217::set_p_shift_gear_position_cmd(uint8_t* data,
    int shift_gear_position_cmd) {
  int x = shift_gear_position_cmd;

  Byte to_set(data + 1);
  to_set.set_value(x, 0, 4);
}


// config detail: {'name': 'shift_control_cmd', 'enum': {0: 'SHIFT_CONTROL_CMD_INVALID', 1: 'SHIFT_CONTROL_CMD_INTELLIGENCE', 2: 'SHIFT_CONTROL_CMD_MANUAL', 3: 'SHIFT_CONTROL_CMD_MANUALINTERVENERECOVERY'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 0, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
void Shiftcmd217::set_p_shift_control_cmd(uint8_t* data,
    Shift_cmd_217::Shift_control_cmdType shift_control_cmd) {
  int x = shift_control_cmd;

  Byte to_set(data + 0);
  to_set.set_value(x, 0, 2);
}

}  // namespace tayron
}  // namespace canbus
}  // namespace apollo
