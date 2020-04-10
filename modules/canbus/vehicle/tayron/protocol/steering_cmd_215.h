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

class Steeringcmd215 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::ChassisDetail> {
 public:
  static const int32_t ID;

  Steeringcmd215();

  uint32_t GetPeriod() const override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'name': 'steering_Angle_cmd', 'offset': -870.0, 'precision': 0.1, 'len': 16, 'is_signed_var': False, 'physical_range': '[-870|870]', 'bit': 16, 'type': 'double', 'order': 'intel', 'physical_unit': 'deg'}
  Steeringcmd215* set_steering_angle_cmd(double steering_angle_cmd);

  // config detail: {'name': 'steering_control_cmd', 'enum': {0: 'STEERING_CONTROL_CMD_STANDBYMODEORDER', 1: 'STEERING_CONTROL_CMD_AUTOSTEERINGMODEORDER', 4: 'STEERING_CONTROL_CMD_EPSMODEORDER', 5: 'STEERING_CONTROL_CMD_INTERVENTRECOVERORDER', 6: 'STEERING_CONTROL_CMD_CLEARFAULTORDER'}, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|15]', 'bit': 8, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  Steeringcmd215* set_steering_control_cmd(Steering_cmd_215::Steering_control_cmdType steering_control_cmd);

  // config detail: {'name': 'steering_V_angle_cmd', 'offset': 0.0, 'precision': 4.0, 'len': 8, 'is_signed_var': False, 'physical_range': '[0|1016]', 'bit': 32, 'type': 'double', 'order': 'intel', 'physical_unit': ''}
  Steeringcmd215* set_steering_v_angle_cmd(double steering_v_angle_cmd);

  // config detail: {'name': 'steering_Angle_valid_cmd', 'enum': {0: 'STEERING_ANGLE_VALID_CMD_INVALID', 1: 'STEERING_ANGLE_VALID_CMD_VALID'}, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|1]', 'bit': 12, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  Steeringcmd215* set_steering_angle_valid_cmd(Steering_cmd_215::Steering_angle_valid_cmdType steering_angle_valid_cmd);

  // config detail: {'name': 'steering_LKA_EN_cmd', 'enum': {0: 'STEERING_LKA_EN_CMD_LKAUNABLE', 1: 'STEERING_LKA_EN_CMD_LKAENABLE'}, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|1]', 'bit': 56, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  Steeringcmd215* set_steering_lka_en_cmd(Steering_cmd_215::Steering_lka_en_cmdType steering_lka_en_cmd);

  // config detail: {'name': 'steering_LKA_Overlay_TQ_cmd', 'offset': -12.8, 'precision': 0.1, 'len': 8, 'is_signed_var': False, 'physical_range': '[-12.8|12.7]', 'bit': 40, 'type': 'double', 'order': 'intel', 'physical_unit': 'Nm'}
  Steeringcmd215* set_steering_lka_overlay_tq_cmd(double steering_lka_overlay_tq_cmd);

  // config detail: {'name': 'steering_control_counter_cmd', 'offset': 0.0, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'physical_range': '[0|15]', 'bit': 4, 'type': 'int', 'order': 'intel', 'physical_unit': ''}
  Steeringcmd215* set_steering_control_counter_cmd(int steering_control_counter_cmd);

  // config detail: {'name': 'steering_DCU_VCU_state', 'enum': {0: 'STEERING_DCU_VCU_STATE_INVALID', 1: 'STEERING_DCU_VCU_STATE_VALID'}, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|1]', 'bit': 13, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  Steeringcmd215* set_steering_dcu_vcu_state(Steering_cmd_215::Steering_dcu_vcu_stateType steering_dcu_vcu_state);

  Steeringcmd215* set_enable();

  Steeringcmd215* set_disable();

  Steeringcmd215* set_driver_override();

 private:

  // config detail: {'name': 'steering_Angle_cmd', 'offset': -870.0, 'precision': 0.1, 'len': 16, 'is_signed_var': False, 'physical_range': '[-870|870]', 'bit': 16, 'type': 'double', 'order': 'intel', 'physical_unit': 'deg'}
  void set_p_steering_angle_cmd(uint8_t* data, double steering_angle_cmd);

  // config detail: {'name': 'steering_control_cmd', 'enum': {0: 'STEERING_CONTROL_CMD_STANDBYMODEORDER', 1: 'STEERING_CONTROL_CMD_AUTOSTEERINGMODEORDER', 4: 'STEERING_CONTROL_CMD_EPSMODEORDER', 5: 'STEERING_CONTROL_CMD_INTERVENTRECOVERORDER', 6: 'STEERING_CONTROL_CMD_CLEARFAULTORDER'}, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|15]', 'bit': 8, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  void set_p_steering_control_cmd(uint8_t* data, Steering_cmd_215::Steering_control_cmdType steering_control_cmd);

  // config detail: {'name': 'steering_V_angle_cmd', 'offset': 0.0, 'precision': 4.0, 'len': 8, 'is_signed_var': False, 'physical_range': '[0|1016]', 'bit': 32, 'type': 'double', 'order': 'intel', 'physical_unit': ''}
  void set_p_steering_v_angle_cmd(uint8_t* data, double steering_v_angle_cmd);

  // config detail: {'name': 'steering_Angle_valid_cmd', 'enum': {0: 'STEERING_ANGLE_VALID_CMD_INVALID', 1: 'STEERING_ANGLE_VALID_CMD_VALID'}, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|1]', 'bit': 12, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  void set_p_steering_angle_valid_cmd(uint8_t* data, Steering_cmd_215::Steering_angle_valid_cmdType steering_angle_valid_cmd);

  // config detail: {'name': 'steering_LKA_EN_cmd', 'enum': {0: 'STEERING_LKA_EN_CMD_LKAUNABLE', 1: 'STEERING_LKA_EN_CMD_LKAENABLE'}, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|1]', 'bit': 56, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  void set_p_steering_lka_en_cmd(uint8_t* data, Steering_cmd_215::Steering_lka_en_cmdType steering_lka_en_cmd);

  // config detail: {'name': 'steering_LKA_Overlay_TQ_cmd', 'offset': -12.8, 'precision': 0.1, 'len': 8, 'is_signed_var': False, 'physical_range': '[-12.8|12.7]', 'bit': 40, 'type': 'double', 'order': 'intel', 'physical_unit': 'Nm'}
  void set_p_steering_lka_overlay_tq_cmd(uint8_t* data, double steering_lka_overlay_tq_cmd);

  // config detail: {'name': 'steering_control_counter_cmd', 'offset': 0.0, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'physical_range': '[0|15]', 'bit': 4, 'type': 'int', 'order': 'intel', 'physical_unit': ''}
  void set_p_steering_control_counter_cmd(uint8_t* data, int steering_control_counter_cmd);

  // config detail: {'name': 'steering_DCU_VCU_state', 'enum': {0: 'STEERING_DCU_VCU_STATE_INVALID', 1: 'STEERING_DCU_VCU_STATE_VALID'}, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|1]', 'bit': 13, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  void set_p_steering_dcu_vcu_state(uint8_t* data, Steering_cmd_215::Steering_dcu_vcu_stateType steering_dcu_vcu_state);


 private:
  double steering_angle_cmd_;
  Steering_cmd_215::Steering_control_cmdType steering_control_cmd_;
  double steering_v_angle_cmd_;
  Steering_cmd_215::Steering_angle_valid_cmdType steering_angle_valid_cmd_;
  Steering_cmd_215::Steering_lka_en_cmdType steering_lka_en_cmd_ = Steering_cmd_215::STEERING_LKA_EN_CMD_LKAUNABLE;
  double steering_lka_overlay_tq_cmd_ = 0.0;
  int steering_control_counter_cmd_;
  Steering_cmd_215::Steering_dcu_vcu_stateType steering_dcu_vcu_state_;
};

}  // namespace tayron
}  // namespace canbus
}  // namespace apollo


