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

#include "modules/drivers/daoyuan/protocol/status_506.h"
#include "modules/drivers/canbus/common/byte.h"

namespace apollo {
namespace drivers {
namespace daoyuan {
using ::apollo::drivers::canbus::Byte;
const int32_t Status506::ID = 0x506;

void Status506::Parse(const std::uint8_t *bytes, int32_t length,
                     Daoyuan *daoyuan_) const
{
    daoyuan_->set_gps_pos_status(pos_flag(bytes,length));
    daoyuan_->set_gps_heading_status(heading_flag(bytes,length));
    daoyuan_->set_car_status(car_status(bytes,length));
    daoyuan_->set_ins_status(ins_status(bytes,length));
    daoyuan_->set_num_sv(num_sv(bytes,length));
}
uint8_t Status506::pos_flag(const std::uint8_t *bytes,
                                  int32_t length) const
{
    Byte frame1(bytes+0);
    uint8_t t1 = frame1.get_byte(0,8);
    return t1;
}
                                  
uint8_t Status506::num_sv(const std::uint8_t *bytes,
                                  int32_t length) const
{
    Byte frame1(bytes+1);
    uint8_t t1 = frame1.get_byte(0,8);
    return t1;
}
uint8_t Status506::heading_flag(const std::uint8_t *bytes,
                                  int32_t length) const
{
    Byte frame1(bytes+2);
    uint8_t t1 = frame1.get_byte(0,8);
    return t1;
}
uint8_t Status506::car_status(const std::uint8_t *bytes,
                                  int32_t length) const
{
    Byte frame1(bytes+4);
    uint8_t t1 = frame1.get_byte(0,8);
    return t1;
}
uint8_t Status506::ins_status(const std::uint8_t *bytes,
                                  int32_t length) const
{
    Byte frame1(bytes+7);
    uint8_t t1 = frame1.get_byte(0,8);
    return t1;
}

} // namespace ctrek
} // namespace canbus
} // namespace apollo
