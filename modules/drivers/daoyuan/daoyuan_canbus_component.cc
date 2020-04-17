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

#include "modules/common/adapters/adapter_gflags.h"
#include "modules/drivers/canbus/can_client/can_client_factory.h"
#include "modules/drivers/canbus/proto/sensor_canbus_conf.pb.h"
#include "modules/drivers/daoyuan/proto/daoyuan.pb.h"
#include "modules/drivers/daoyuan/daoyuan_canbus_component.h"
#include "modules/drivers/daoyuan/daoyuan_message_manager.h"
#include <proj_api.h>
/**
 * @namespace apollo::drivers::daoyuan
 * @brief apollo::drivers
 */
namespace apollo {
namespace drivers {
namespace daoyuan {
constexpr double DEG_TO_RAD_LOCAL = M_PI / 180.0;
using apollo::common::ErrorCode;
using apollo::drivers::canbus::CanClientFactory;
using apollo::drivers::canbus::SensorCanbusConf;
using apollo::localization::LocalizationEstimate;
using apollo::localization::LocalizationStatus;
using apollo::localization::MeasureState;
DaoyuanCanbusComponent::DaoyuanCanbusComponent()
    : monitor_logger_buffer_(
          apollo::common::monitor::MonitorMessageItem::GNSS) {}
DaoyuanCanbusComponent::~DaoyuanCanbusComponent() {Stop(); }

bool DaoyuanCanbusComponent::Init() {
  if (!GetProtoConfig(&daoyuan_conf_)) {
    return OnError("Unable to load canbus conf file: ");
  }
  AINFO << "The canbus conf file is loaded: " << ConfigFilePath();
  ADEBUG << "Canbus_conf:" << daoyuan_conf_.ShortDebugString();
  tf2_broadcaster_.reset(new apollo::transform::TransformBroadcaster(node_));
  // Init can client
  auto can_factory = CanClientFactory::Instance();
  can_factory->RegisterCanClients();
  can_client_ = can_factory->CreateCANClient(
      daoyuan_conf_.can_card_parameter());
  if (!can_client_) {
    return OnError("Failed to create can client.");
  }
  AINFO << "Can client is successfully created.";
  localization_writer_=node_->CreateWriter<LocalizationEstimate>(daoyuan_conf_.localization_topic());
  status_writer_=node_->CreateWriter<LocalizationStatus>(daoyuan_conf_.localization_status_topic());
  broadcast_tf_frame_id_=daoyuan_conf_.broadcast_tf_frame_id();
  broadcast_tf_child_frame_id_=daoyuan_conf_.broadcast_tf_child_frame_id();
  sensor_message_manager_ = std::unique_ptr<DaoyuanMessageManager>(
      new DaoyuanMessageManager);
  if (sensor_message_manager_ == nullptr) {
    return OnError("Failed to create message manager.");
  }
  AINFO << "Sensor message manager is successfully created.";

  if (can_receiver_.Init(can_client_.get(), sensor_message_manager_.get(),
                         daoyuan_conf_.enable_receiver_log()) !=
      ErrorCode::OK) {
    return OnError("Failed to init can receiver.");
  }
  AINFO << "The can receiver is successfully initialized.";
  start_success_=Start();
  wgs84pj_source_ = pj_init_plus("+proj=latlong +ellps=WGS84");
  utm_target_ = pj_init_plus(daoyuan_conf_.proj4_text().c_str());

  return start_success_;
}

bool DaoyuanCanbusComponent::Start() {
  // 1. init and start the can card hardware
  if (can_client_->Start() != ErrorCode::OK) {
    return OnError("Failed to start can client");
  }
  AINFO << "Can client is started.";
  // 2. start receive first then send
  if (can_receiver_.Start() != ErrorCode::OK) {
    return OnError("Failed to start can receiver.");
  }
  AINFO << "Can receiver is started.";

  // last step: publish monitor messages
  monitor_logger_buffer_.INFO("Canbus is started.");

  return true;
}

void DaoyuanCanbusComponent::Stop() {
  if (start_success_) {
    can_receiver_.Stop();
    can_client_->Stop();
  }
}
bool DaoyuanCanbusComponent::Proc() {
  Daoyuan daoyuan;
  LocalizationEstimate localization;
  LocalizationStatus status;
  common::util::FillHeader("daoyuan", &localization); 
  common::util::FillHeader("daoyuan",&status);
  sensor_message_manager_->GetSensorData(&daoyuan);
  if (daoyuan.has_acc_front())  {
    localization.mutable_pose()->mutable_linear_acceleration_vrf()->set_x(daoyuan.acc_right());
    localization.mutable_pose()->mutable_linear_acceleration_vrf()->set_y(daoyuan.acc_front());
    localization.mutable_pose()->mutable_linear_acceleration_vrf()->set_z(daoyuan.acc_up());
  }
  if (daoyuan.has_pitch_rate())  {
    localization.mutable_pose()->mutable_angular_velocity_vrf()->set_x(daoyuan.pitch_rate());
    localization.mutable_pose()->mutable_angular_velocity_vrf()->set_y(daoyuan.roll_rate());
    localization.mutable_pose()->mutable_angular_velocity_vrf()->set_z(daoyuan.yaw_rate());
  }
  if (daoyuan.has_yaw())  {
    localization.mutable_pose()->set_heading(daoyuan.yaw());
    Eigen::Quaternion<double> qu = apollo::common::math::HeadingToQuaternion(daoyuan.yaw());
    localization.mutable_pose()->mutable_orientation()->set_qx(qu.x());
    localization.mutable_pose()->mutable_orientation()->set_qy(qu.y());
    localization.mutable_pose()->mutable_orientation()->set_qz(qu.z());
    localization.mutable_pose()->mutable_orientation()->set_qw(qu.w());
  }
  if (daoyuan.has_height())  {
    localization.mutable_pose()->mutable_position()->set_z(daoyuan.height());
    localization.set_measurement_time(localization.header().timestamp_sec());
    status.set_measurement_time(status.header().timestamp_sec());
  }
  if (daoyuan.has_lon())  {
    double x=daoyuan.lon()*DEG_TO_RAD_LOCAL;
    double y=daoyuan.lat()*DEG_TO_RAD_LOCAL;
    pj_transform(wgs84pj_source_, utm_target_, 1, 1, &x, &y, NULL);
    localization.mutable_pose()->mutable_position()->set_x(x);
    localization.mutable_pose()->mutable_position()->set_y(y);
  }
  if (daoyuan.has_north_spd()) {
    localization.mutable_pose()->mutable_linear_velocity()->set_x(daoyuan.east_spd());
    localization.mutable_pose()->mutable_linear_velocity()->set_y(daoyuan.north_spd());
    localization.mutable_pose()->mutable_linear_velocity()->set_z(daoyuan.up_spd());
  }
  if (daoyuan.has_ins_status()) {
    if (daoyuan.gps_pos_status()==50 && daoyuan.gps_heading_status()==50 &&
       daoyuan.car_status()==1 && daoyuan.ins_status()==2) {
         status.set_fusion_status(MeasureState::OK);
         status.set_state_message("all NARROW INT");
       }
    else {
         status.set_fusion_status(MeasureState::WARNNING);
         status.set_state_message("Current Localization Is Unstable");
         AWARN<<"pos status "<<daoyuan.gps_pos_status()<<"heading status "<<
              daoyuan.gps_heading_status()<<"car status "<<daoyuan.car_status()<<
              "ins status "<<daoyuan.ins_status();
    }
  } else {
      status.set_fusion_status(MeasureState::ERROR);
      status.set_state_message("no status signal");
      AERROR<<"NO STATUS SIGNAL";
      return false;
  }
  common::util::FillHeader("daoyuan", &localization); 
  common::util::FillHeader("daoyuan",&status);
  //AINFO<<"localization"<<localization.ShortDebugString();
  //AINFO<<"status"<<status.ShortDebugString();
  localization_writer_->Write(localization);
  status_writer_->Write(status);
  PublishPoseBroadcastTF(localization);
  return true;
}
void DaoyuanCanbusComponent::PublishPoseBroadcastTF(
    const LocalizationEstimate& localization) {
  // broadcast tf message
  apollo::transform::TransformStamped tf2_msg;

  auto mutable_head = tf2_msg.mutable_header();
  mutable_head->set_timestamp_sec(localization.header().timestamp_sec());
  mutable_head->set_frame_id(broadcast_tf_frame_id_);
  tf2_msg.set_child_frame_id(broadcast_tf_child_frame_id_);

  auto mutable_translation = tf2_msg.mutable_transform()->mutable_translation();
  mutable_translation->set_x(localization.pose().position().x());
  mutable_translation->set_y(localization.pose().position().y());
  mutable_translation->set_z(localization.pose().position().z());

  auto mutable_rotation = tf2_msg.mutable_transform()->mutable_rotation();
  mutable_rotation->set_qx(localization.pose().orientation().qx());
  mutable_rotation->set_qy(localization.pose().orientation().qy());
  mutable_rotation->set_qz(localization.pose().orientation().qz());
  mutable_rotation->set_qw(localization.pose().orientation().qw());

  tf2_broadcaster_->SendTransform(tf2_msg);
}
// Send the error to monitor and return it
bool DaoyuanCanbusComponent::OnError(const std::string& error_msg) {
  monitor_logger_buffer_.ERROR(error_msg);
  AERROR << error_msg;
  return false;
}



}  // namespace daoyuan
}  // namespace drivers
}  // namespace apollo
