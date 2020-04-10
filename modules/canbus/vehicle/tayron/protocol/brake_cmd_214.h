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

class Brakecmd214 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::ChassisDetail> {
 public:
  static const int32_t ID;

  Brakecmd214();

  uint32_t GetPeriod() const override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'name': 'brake_pedal_cmd', 'offset': 0.0, 'precision': 0.005, 'len': 8, 'is_signed_var': False, 'physical_range': '[0|100]', 'bit': 0, 'type': 'double', 'order': 'intel', 'physical_unit': ''}
  Brakecmd214* set_brake_pedal_cmd(double brake_pedal_cmd);

  // config detail: {'name': 'brake_control_cmd', 'enum': {0: 'BRAKE_CONTROL_CMD_INVALID', 1: 'BRAKE_CONTROL_CMD_INTELLIGENCE', 2: 'BRAKE_CONTROL_CMD_MANUAL', 3: 'BRAKE_CONTROL_CMD_INTERVENERECOVERY'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 8, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  Brakecmd214* set_brake_control_cmd(Brake_cmd_214::Brake_control_cmdType brake_control_cmd);

  Brakecmd214* set_enable();//brake_control_cmd = 1
  Brakecmd214* set_disable();//brake_control_cmd = 2
  Brakecmd214* set_driver_override();//brake_control_cmd = 3

 private:

  // config detail: {'name': 'brake_pedal_cmd', 'offset': 0.0, 'precision': 0.005, 'len': 8, 'is_signed_var': False, 'physical_range': '[0|100]', 'bit': 0, 'type': 'double', 'order': 'intel', 'physical_unit': ''}
  void set_p_brake_pedal_cmd(uint8_t* data, double brake_pedal_cmd);

  // config detail: {'name': 'brake_control_cmd', 'enum': {0: 'BRAKE_CONTROL_CMD_INVALID', 1: 'BRAKE_CONTROL_CMD_INTELLIGENCE', 2: 'BRAKE_CONTROL_CMD_MANUAL', 3: 'BRAKE_CONTROL_CMD_INTERVENERECOVERY'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 8, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  void set_p_brake_control_cmd(uint8_t* data, Brake_cmd_214::Brake_control_cmdType brake_control_cmd);

 private:
  double brake_pedal_cmd_;
  Brake_cmd_214::Brake_control_cmdType brake_control_cmd_;
};

}  // namespace tayron
}  // namespace canbus
}  // namespace apollo


