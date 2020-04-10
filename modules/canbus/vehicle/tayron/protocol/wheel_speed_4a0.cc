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

#include "modules/canbus/vehicle/tayron/protocol/wheel_speed_4a0.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace tayron {

using ::apollo::drivers::canbus::Byte;

Wheelspeed4a0::Wheelspeed4a0() {}
const int32_t Wheelspeed4a0::ID = 0x4A0;

void Wheelspeed4a0::Parse(const std::uint8_t* bytes, int32_t length,
                         ChassisDetail* chassis) const {
  chassis->mutable_tayron()->mutable_wheel_speed_4a0()->set_br3_rad_kmh_vr(br3_rad_kmh_vr(bytes, length));
  chassis->mutable_tayron()->mutable_wheel_speed_4a0()->set_br3_rad_kmh_vl(br3_rad_kmh_vl(bytes, length));
  chassis->mutable_tayron()->mutable_wheel_speed_4a0()->set_br3_rad_kmh_hr(br3_rad_kmh_hr(bytes, length));
  chassis->mutable_tayron()->mutable_wheel_speed_4a0()->set_br3_rad_kmh_hl(br3_rad_kmh_hl(bytes, length));
  chassis->mutable_tayron()->mutable_wheel_speed_4a0()->set_br3_fahtr_vl(br3_fahtr_vl(bytes, length));
  chassis->mutable_tayron()->mutable_wheel_speed_4a0()->set_br3_fahrtr_vr(br3_fahrtr_vr(bytes, length));
  chassis->mutable_tayron()->mutable_wheel_speed_4a0()->set_br3_fahrtr_hr(br3_fahrtr_hr(bytes, length));
  chassis->mutable_tayron()->mutable_wheel_speed_4a0()->set_br3_fahrtr_hl(br3_fahrtr_hl(bytes, length));
}

// config detail: {'name': 'br3_rad_kmh_vr', 'offset': 0.0, 'precision': 0.01, 'len': 15, 'is_signed_var': False, 'physical_range': '[0|326.39]', 'bit': 17, 'type': 'double', 'order': 'intel', 'physical_unit': 'Unit KiloMeterPerHour'}
double Wheelspeed4a0::br3_rad_kmh_vr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(1, 7);
  x <<= 7;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'name': 'br3_rad_kmh_vl', 'offset': 0.0, 'precision': 0.01, 'len': 15, 'is_signed_var': False, 'physical_range': '[0|326.39]', 'bit': 1, 'type': 'double', 'order': 'intel', 'physical_unit': 'Unit KiloMeterPerHour'}
double Wheelspeed4a0::br3_rad_kmh_vl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 0);
  int32_t t = t1.get_byte(1, 7);
  x <<= 7;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'name': 'br3_rad_kmh_hr', 'offset': 0.0, 'precision': 0.01, 'len': 15, 'is_signed_var': False, 'physical_range': '[0|326.39]', 'bit': 49, 'type': 'double', 'order': 'intel', 'physical_unit': 'Unit KiloMeterPerHour'}
double Wheelspeed4a0::br3_rad_kmh_hr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 7);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 6);
  int32_t t = t1.get_byte(1, 7);
  x <<= 7;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'name': 'br3_rad_kmh_hl', 'offset': 0.0, 'precision': 0.01, 'len': 15, 'is_signed_var': False, 'physical_range': '[0|326.39]', 'bit': 33, 'type': 'double', 'order': 'intel', 'physical_unit': 'Unit KiloMeterPerHour'}
double Wheelspeed4a0::br3_rad_kmh_hl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 4);
  int32_t t = t1.get_byte(1, 7);
  x <<= 7;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'name': 'br3_fahtr_vl', 'offset': 0.0, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 0, 'type': 'bool', 'order': 'intel', 'physical_unit': ''}
bool Wheelspeed4a0::br3_fahtr_vl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'name': 'br3_fahrtr_vr', 'offset': 0.0, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 16, 'type': 'bool', 'order': 'intel', 'physical_unit': ''}
bool Wheelspeed4a0::br3_fahrtr_vr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 2);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'name': 'br3_fahrtr_hr', 'offset': 0.0, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 48, 'type': 'bool', 'order': 'intel', 'physical_unit': ''}
bool Wheelspeed4a0::br3_fahrtr_hr(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 6);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'name': 'br3_fahrtr_hl', 'offset': 0.0, 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 32, 'type': 'bool', 'order': 'intel', 'physical_unit': ''}
bool Wheelspeed4a0::br3_fahrtr_hl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 4);
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}
}  // namespace tayron
}  // namespace canbus
}  // namespace apollo
