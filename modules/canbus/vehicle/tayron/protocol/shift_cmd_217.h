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

class Shiftcmd217 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::ChassisDetail> {
 public:
  static const int32_t ID;

  Shiftcmd217();

  uint32_t GetPeriod() const override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  Shiftcmd217* set_enable();

  Shiftcmd217* set_disable();

  Shiftcmd217* set_driver_override();

  Shiftcmd217* set_gear_none();

  Shiftcmd217* set_gear_park();

  Shiftcmd217* set_gear_reverse();

  Shiftcmd217* set_gear_neutral();

  Shiftcmd217* set_gear_drive();


  // config detail: {'name': 'shift_gear_position_cmd', 'enum': {0: 'SHIFT_GEAR_POSITION_CMD_N', 1: 'SHIFT_GEAR_POSITION_CMD_D', 2: 'SHIFT_GEAR_POSITION_CMD_R', 3: 'SHIFT_GEAR_POSITION_CMD_P', 4: 'SHIFT_GEAR_POSITION_CMD_NONE'}, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|7]', 'bit': 8, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  Shiftcmd217* set_shift_gear_position_cmd(Shift_cmd_217::Shift_gear_position_cmdType shift_gear_position_cmd);

  // config detail: {'name': 'shift_control_cmd', 'enum': {0: 'SHIFT_CONTROL_CMD_INVALID', 1: 'SHIFT_CONTROL_CMD_INTELLIGENCE', 2: 'SHIFT_CONTROL_CMD_MANUAL', 3: 'SHIFT_CONTROL_CMD_MANUALINTERVENERECOVERY'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 0, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  Shiftcmd217* set_shift_control_cmd(Shift_cmd_217::Shift_control_cmdType shift_control_cmd);


 private:

  // config detail: {'name': 'shift_gear_position_cmd', 'enum': {0: 'SHIFT_GEAR_POSITION_CMD_N', 1: 'SHIFT_GEAR_POSITION_CMD_D', 2: 'SHIFT_GEAR_POSITION_CMD_R', 3: 'SHIFT_GEAR_POSITION_CMD_P', 4: 'SHIFT_GEAR_POSITION_CMD_NONE'}, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|7]', 'bit': 8, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  void set_p_shift_gear_position_cmd(uint8_t* data, Shift_cmd_217::Shift_gear_position_cmdType shift_gear_position_cmd);

  // config detail: {'name': 'shift_control_cmd', 'enum': {0: 'SHIFT_CONTROL_CMD_INVALID', 1: 'SHIFT_CONTROL_CMD_INTELLIGENCE', 2: 'SHIFT_CONTROL_CMD_MANUAL', 3: 'SHIFT_CONTROL_CMD_MANUALINTERVENERECOVERY'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 0, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  void set_p_shift_control_cmd(uint8_t* data, Shift_cmd_217::Shift_control_cmdType shift_control_cmd);

 private:
  Shift_cmd_217::Shift_gear_position_cmdType shift_gear_position_cmd_;
  Shift_cmd_217::Shift_control_cmdType shift_control_cmd_;
};

}  // namespace tayron
}  // namespace canbus
}  // namespace apollo


