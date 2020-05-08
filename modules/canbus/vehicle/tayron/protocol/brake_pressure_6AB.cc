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

#include "modules/canbus/vehicle/tayron/protocol/brake_pressure_6AB.h"

#include "glog/logging.h"

#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace tayron {

using ::apollo::drivers::canbus::Byte;

Brakepressure6AB::Brakepressure6AB() {}
const int32_t Brakepressure6AB::ID = 0x6AB;

void Brakepressure6AB::Parse(const std::uint8_t* bytes, int32_t length,
                         ChassisDetail* chassis) const {
  chassis->mutable_tayron()->mutable_brake_report_321()->set_pu_pressure(pu_pressure(bytes, length));
  
}

// config detail: {'name': 'pu_pressure', 'offset': 0.0, 'precision': 0.1, 'len': 12, 'is_signed_var': True, 'physical_range': '[0|409.5]', 'bit': 40, 'type': 'double', 'order': 'intel', 'physical_unit': 'bar'}
double Brakepressure6AB::pu_pressure(const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 5);
  int32_t x = t0.get_byte(0, 4);

  Byte t1(bytes + 6);
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 20;
  x >>= 20;

  double ret = x * 0.100000;
  return ret;
}

}  // namespace tayron
}  // namespace canbus
}  // namespace apollo
