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

class Wheelspeed4a0 : public ::apollo::drivers::canbus::ProtocolData<
                    ::apollo::canbus::ChassisDetail> {
 public:
  static const int32_t ID;
  Wheelspeed4a0();
  void Parse(const std::uint8_t* bytes, int32_t length,
                     ChassisDetail* chassis) const override;

 private:

  // config detail: {'name': 'BR3_Rad_kmh_VR', 'offset': 0.0, 'precision': 0.01, 'len': 15, 'is_signed_var': False, 'physical_range': '[0|326.39]', 'bit': 17, 'type': 'double', 'order': 'intel', 'physical_unit': 'Unit KiloMeterPerHour'}
  double br3_rad_kmh_vr(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'BR3_Rad_kmh_VL', 'offset': 0.0, 'precision': 0.01, 'len': 15, 'is_signed_var': False, 'physical_range': '[0|326.39]', 'bit': 1, 'type': 'double', 'order': 'intel', 'physical_unit': 'Unit KiloMeterPerHour'}
  double br3_rad_kmh_vl(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'BR3_Rad_kmh_HR', 'offset': 0.0, 'precision': 0.01, 'len': 15, 'is_signed_var': False, 'physical_range': '[0|326.39]', 'bit': 49, 'type': 'double', 'order': 'intel', 'physical_unit': 'Unit KiloMeterPerHour'}
  double br3_rad_kmh_hr(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'BR3_Rad_kmh_HL', 'offset': 0.0, 'precision': 0.01, 'len': 15, 'is_signed_var': False, 'physical_range': '[0|326.39]', 'bit': 33, 'type': 'double', 'order': 'intel', 'physical_unit': 'Unit KiloMeterPerHour'}
  double br3_rad_kmh_hl(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'BR3_Fahtr_VL', 'offset': 0.0, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 0, 'type': 'bool', 'order': 'intel', 'physical_unit': ''}
  bool br3_fahtr_vl(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'BR3_Fahrtr_VR', 'offset': 0.0, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 16, 'type': 'bool', 'order': 'intel', 'physical_unit': ''}
  bool br3_fahrtr_vr(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'BR3_Fahrtr_HR', 'offset': 0.0, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 48, 'type': 'bool', 'order': 'intel', 'physical_unit': ''}
  bool br3_fahrtr_hr(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'BR3_Fahrtr_HL', 'offset': 0.0, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 32, 'type': 'bool', 'order': 'intel', 'physical_unit': ''}
  bool br3_fahrtr_hl(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace tayron
}  // namespace canbus
}  // namespace apollo


