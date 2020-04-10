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

#include "modules/canbus/vehicle/tayron/protocol/mmotor_1_280.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace tayron {

using ::apollo::drivers::canbus::Byte;

Mmotor1280::Mmotor1280() {}
const int32_t Mmotor1280::ID = 0x280;

void Mmotor1280::Parse(const std::uint8_t* bytes, int32_t length,
                         ChassisDetail* chassis) const {
  chassis->mutable_tayron()->mutable_mmotor_1_280()->set_mo1_drehzahl(mo1_drehzahl(bytes, length));
}

// config detail: {'name': 'mo1_drehzahl', 'offset': 0.0, 'precision': 0.25, 'len': 16, 'is_signed_var': False, 'physical_range': '[0|16256]', 'bit': 16, 'type': 'double', 'order': 'intel', 'physical_unit': ''}
double Mmotor1280::mo1_drehzahl(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 3);
  int32_t x = t0.get_byte(0, 8);

  Byte t1(bytes + 2);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.250000;
  return ret;
}
}  // namespace tayron
}  // namespace canbus
}  // namespace apollo
