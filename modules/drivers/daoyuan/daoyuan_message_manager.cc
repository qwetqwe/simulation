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
 * @file conti_radar_message_manager.h
 * @brief The class of ContiRadarMessageManager
 */

#include "modules/drivers/daoyuan/daoyuan_message_manager.h"
#include "modules/drivers/daoyuan/protocol/acc_500.h"
#include "modules/drivers/daoyuan/protocol/gyro_501.h"
#include "modules/drivers/daoyuan/protocol/heading_502.h"
#include "modules/drivers/daoyuan/protocol/height_503.h"
#include "modules/drivers/daoyuan/protocol/lonlat_504.h"
#include "modules/drivers/daoyuan/protocol/vel_505.h"
#include "modules/drivers/daoyuan/protocol/status_506.h"
namespace apollo {
namespace drivers {
namespace daoyuan {

DaoyuanMessageManager::DaoyuanMessageManager() {
  AddRecvProtocolData<Acc500, true>();
  AddRecvProtocolData<Gyro501, true>();
  AddRecvProtocolData<Heading502, true>();
  AddRecvProtocolData<Height503, true>();
  AddRecvProtocolData<Lonlat504, true>();
  AddRecvProtocolData<Status506, true>();
  AddRecvProtocolData<Vel505, true>();
}
DaoyuanMessageManager::~DaoyuanMessageManager() {}

}  // namespace conti_radar
}  // namespace drivers
}  // namespace apollo
