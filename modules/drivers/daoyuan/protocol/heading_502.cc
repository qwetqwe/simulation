/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
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

#include "modules/drivers/daoyuan/protocol/heading_502.h"
#include "modules/drivers/canbus/common/byte.h"
#include <cmath>
namespace apollo {
namespace drivers {
namespace daoyuan {
using ::apollo::drivers::canbus::Byte;
double NormalizeAngle(const double angle) {
  const double new_angle = fmod(angle + M_PI, M_PI * 2.0);
  return (new_angle < 0 ? new_angle + M_PI * 2.0 : new_angle) - M_PI;
}

const int32_t Heading502::ID = 0x502;

void Heading502::Parse(const std::uint8_t *bytes, int32_t length,
                     Daoyuan *daoyuan_) const
{
    daoyuan_->set_yaw(NormalizeAngle(-heading(bytes,length)+M_PI/2));
    daoyuan_->set_roll(roll(bytes,length));
    daoyuan_->set_pitch(pitch(bytes,length));
}

double Heading502::heading(const std::uint8_t *bytes, int32_t length) const
{
    Byte frame_low(bytes + 5);
    uint8_t low = frame_low.get_byte(0,8);
    Byte frame_high(bytes + 4);
    uint8_t high = frame_high.get_byte(0,8);
    uint32_t val = (high<<8) | low;
    return (val*0.010986-360)/180*M_PI;
}
double Heading502::pitch(const std::uint8_t *bytes, int32_t length) const
{
    Byte frame_low(bytes + 1);
    uint8_t low = frame_low.get_byte(0,8);
    Byte frame_high(bytes + 0);
    uint8_t high = frame_high.get_byte(0,8);
    uint32_t val = (high<<8) | low;
    return (val*0.010986-360)/180*M_PI;
}
double Heading502::roll(const std::uint8_t *bytes, int32_t length) const
{
    Byte frame_low(bytes + 3);
    uint8_t low = frame_low.get_byte(0,8);
    Byte frame_high(bytes + 2);
    uint8_t high = frame_high.get_byte(0,8);
    uint32_t val = (high<<8) | low;
    return (val*0.010986-360)/180*M_PI;
}





} // namespace ctrek
} // namespace canbus
} // namespace apollo
