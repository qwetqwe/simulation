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

/**
 * @file brake_321.h
 * @brief the class of GYRO501 (for ctrek vehicle)
 */

#ifndef MODULES_CANBUS_VEHICLE_ctrek_PROTOCOL_GYRO_501_H_
#define MODULES_CANBUS_VEHICLE_ctrek_PROTOCOL_GYRO_501_H_

#include "modules/drivers/canbus/can_comm/protocol_data.h"
#include "modules/drivers/daoyuan/proto/daoyuan.pb.h"

/**
 * @namespace apollo::canbus::ctrek
 * @brief apollo::canbus::ctrek
 */
namespace apollo {
namespace drivers {
namespace daoyuan {
/**
 * @class GYRO501
 *
 * @brief one of the protocol data of ctrek vehicle
 */
class Gyro501 : public ::apollo::drivers::canbus::ProtocolData<Daoyuan> {
 public:
  static const int32_t ID;

  /*
   * @brief parse received data
   * @param bytes a pointer to the input bytes
   * @param length the length of the input bytes
   * @param timestamp the timestamp of input data
   * @param chassis_detail the parsed chassis_detail
   */
  virtual void Parse(const std::uint8_t *bytes, int32_t length,
                     Daoyuan *daoyuan_) const;

 private:
  
  double gyro_front(const std::uint8_t *bytes,
                                  int32_t length) const;
  double gyro_right(const std::uint8_t *bytes,
                                  int32_t length) const;
  double gyro_down(const std::uint8_t *bytes,
                                  int32_t length) const;                               
};

}  // namespace ctrek
}  // namespace canbus
}  // namespace apollo

#endif  // MODULES_CANBUS_ctrek_PROTOCOL_ACC_501_H_
