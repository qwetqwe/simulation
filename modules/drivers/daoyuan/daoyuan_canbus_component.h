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
 * @file
 */

#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <proj_api.h>
#include "cyber/cyber.h"
#include "cyber/component/timer_component.h"
#include "modules/common/math/quaternion.h"
#include "modules/common/monitor_log/monitor_log_buffer.h"
#include "modules/common/util/util.h"
#include "modules/drivers/canbus/can_client/can_client.h"
#include "modules/drivers/canbus/can_comm/can_receiver.h"
#include "modules/drivers/canbus/can_comm/message_manager.h"
#include "modules/drivers/canbus/proto/can_card_parameter.pb.h"
#include "modules/drivers/daoyuan/proto/daoyuan.pb.h"
#include "modules/drivers/daoyuan/proto/daoyuan_conf.pb.h"
#include "modules/drivers/daoyuan/daoyuan_message_manager.h"
#include "Eigen/Geometry"
#include "modules/localization/proto/localization.pb.h"
#include "modules/transform/transform_broadcaster.h"
/**
 * @namespace apollo::drivers
 * @brief apollo::drivers
 */
namespace apollo {
namespace drivers {
namespace daoyuan {

/**
 * @class DaoyuanCanbus
 *
 * @brief template of canbus-based sensor module main class (e.g., daoyuan).
 */

class DaoyuanCanbusComponent :  public apollo::cyber::TimerComponent {
 public:
  DaoyuanCanbusComponent();
  ~DaoyuanCanbusComponent();
  bool Init() override;
  bool Proc() override;
 private:
  bool Start();
  void Stop();
  void PublishPoseBroadcastTF(const apollo::localization::LocalizationEstimate& localization); 
  apollo::common::monitor::MonitorLogBuffer monitor_logger_buffer_;
  bool OnError(const std::string& error_msg);
  DaoyuanConf daoyuan_conf_;
  std::shared_ptr<apollo::drivers::canbus::CanClient> can_client_;
  apollo::drivers::canbus::CanReceiver<Daoyuan> can_receiver_;
  std::unique_ptr<DaoyuanMessageManager> sensor_message_manager_;
  std::shared_ptr<apollo::cyber::Writer<apollo::localization::LocalizationEstimate>> localization_writer_;
  std::shared_ptr<apollo::cyber::Writer<apollo::localization::LocalizationStatus>> status_writer_;
  std::string broadcast_tf_frame_id_;
  std::string broadcast_tf_child_frame_id_;
  std::unique_ptr<apollo::transform::TransformBroadcaster> tf2_broadcaster_;
  projPJ wgs84pj_source_;
  projPJ utm_target_;
  bool start_success_=false;
};

CYBER_REGISTER_COMPONENT(DaoyuanCanbusComponent)

}  // namespace daoyuan
}  // namespace drivers
}  // namespace apollo
