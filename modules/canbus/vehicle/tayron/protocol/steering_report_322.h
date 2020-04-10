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

class Steeringreport322 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::ChassisDetail> {
 public:
  static const int32_t ID;
  Steeringreport322();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     ChassisDetail* chassis) const override;

 private:

  // config detail: {'name': 'steering_Angle_status', 'offset': -870.0, 'precision': 0.1, 'len': 16, 'is_signed_var': False, 'physical_range': '[-870|870]', 'bit': 0, 'type': 'double', 'order': 'intel', 'physical_unit': 'deg'}
  double steering_angle_status(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'steering_control_status', 'enum': {0: 'STEERING_CONTROL_STATUS_STANDBYMODE', 1: 'STEERING_CONTROL_STATUS_AUTOSTEERINGMODE', 3: 'STEERING_CONTROL_STATUS_LKAMODE', 4: 'STEERING_CONTROL_STATUS_EPSMODE', 5: 'STEERING_CONTROL_STATUS_MANUALINTERVENTMODE', 6: 'STEERING_CONTROL_STATUS_WARNINGMODE', 7: 'STEERING_CONTROL_STATUS_ERRORMODE'}, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|15]', 'bit': 60, 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  int steering_control_status(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'steering_Toque_status', 'offset': -15.0, 'precision': 0.12, 'len': 8, 'is_signed_var': False, 'physical_range': '[-15|15.6]', 'bit': 24, 'type': 'double', 'order': 'intel', 'physical_unit': 'Nm'}
  double steering_toque_status(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'steering_V_angle_status', 'offset': 0.0, 'precision': 4.0, 'len': 8, 'is_signed_var': False, 'physical_range': '[0|1016]', 'bit': 16, 'type': 'double', 'order': 'intel', 'physical_unit': ''}
  double steering_v_angle_status(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'steering_counter_status', 'offset': 0.0, 'precision': 1.0, 'len': 4, 'is_signed_var': False, 'physical_range': '[0|15]', 'bit': 56, 'type': 'int', 'order': 'intel', 'physical_unit': ''}
  int steering_counter_status(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'steering_real_current_status', 'offset': -160.0, 'precision': 0.08, 'len': 12, 'is_signed_var': False, 'physical_range': '[-160|167.6]', 'bit': 44, 'type': 'double', 'order': 'intel', 'physical_unit': 'A'}
  double steering_real_current_status(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'steering_ref_current_status', 'offset': -160.0, 'precision': 0.08, 'len': 12, 'is_signed_var': False, 'physical_range': '[-160|167.6]', 'bit': 32, 'type': 'double', 'order': 'intel', 'physical_unit': 'A'}
  double steering_ref_current_status(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace tayron
}  // namespace canbus
}  // namespace apollo


