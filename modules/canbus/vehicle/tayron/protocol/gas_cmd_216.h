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

class Gascmd216 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::ChassisDetail> {
 public:
  static const int32_t ID;

  Gascmd216();

  uint32_t GetPeriod() const override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'name': 'gas_pedal_cmd', 'offset': 0.0, 'precision': 0.39, 'len': 8, 'is_signed_var': False, 'physical_range': '[0|99.45]', 'bit': 8, 'type': 'double', 'order': 'intel', 'physical_unit': '%'}
  Gascmd216* set_gas_pedal_cmd(double gas_pedal_cmd);

  // config detail: {'name': 'gas_control_cmd', 'enum': {0: 'GAS_CONTROL_CMD_INVALID', 1: 'GAS_CONTROL_CMD_INTELLIGENCE', 2: 'GAS_CONTROL_CMD_MANUAL', 3: 'GAS_CONTROL_CMD_RESERVED'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 0, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  Gascmd216* set_gas_control_cmd(Gas_cmd_216::Gas_control_cmdType gas_control_cmd);
  Gascmd216* set_enable();
  Gascmd216* set_disable();

 private:

  // config detail: {'name': 'gas_pedal_cmd', 'offset': 0.0, 'precision': 0.39, 'len': 8, 'is_signed_var': False, 'physical_range': '[0|99.45]', 'bit': 8, 'type': 'double', 'order': 'intel', 'physical_unit': '%'}
  void set_p_gas_pedal_cmd(uint8_t* data, double gas_pedal_cmd);

  // config detail: {'name': 'gas_control_cmd', 'enum': {0: 'GAS_CONTROL_CMD_INVALID', 1: 'GAS_CONTROL_CMD_INTELLIGENCE', 2: 'GAS_CONTROL_CMD_MANUAL', 3: 'GAS_CONTROL_CMD_RESERVED'}, 'precision': 1.0, 'len': 2, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|3]', 'bit': 0, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  void set_p_gas_control_cmd(uint8_t* data, Gas_cmd_216::Gas_control_cmdType gas_control_cmd);

 private:
  double gas_pedal_cmd_;
  Gas_cmd_216::Gas_control_cmdType gas_control_cmd_;
};

}  // namespace tayron
}  // namespace canbus
}  // namespace apollo


