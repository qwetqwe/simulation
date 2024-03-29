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
 * @file daoyuan_message_manager.h
 * @brief The class of DaoyuanMessageManager
 */
#pragma once

#include <memory>

#include "cyber/cyber.h"
#include "modules/drivers/canbus/can_client/can_client_factory.h"
#include "modules/drivers/canbus/can_comm/message_manager.h"
#include "modules/drivers/daoyuan/proto/daoyuan.pb.h"

namespace apollo {
namespace drivers {
namespace daoyuan {

class DaoyuanMessageManager
    : public apollo::drivers::canbus::MessageManager<Daoyuan> {
 public:
  DaoyuanMessageManager();
  virtual ~DaoyuanMessageManager();
};

}  // namespace daoyuan
}  // namespace drivers
}  // namespace apollo
