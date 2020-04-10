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
#include <poll.h>
#include "cyber/component/timer_component.h"
#include "cyber/cyber.h"
#include "modules/common/adapters/adapter_gflags.h"
#include "modules/common/util/message_util.h"
#include "modules/prediction/proto/prediction_obstacle.pb.h"
#include "modules/localization/proto/localization.pb.h"
#include <Eigen/Core>
#include<Eigen/Geometry>
#include <Eigen/Eigen>
#include <iostream>
namespace apollo {
namespace prediction {
typedef std::shared_ptr<apollo::localization::LocalizationEstimate> LocalizationMsgType;
using apollo::localization::LocalizationEstimate;
/**
 * class FakePredictionComponent
 * This class generates fake prediction messages. The prediction message only
 * has valid headers.
 *
 * This tool is used to trigger modules that depends on prediction message.
 */
class FakePredictionComponent : public apollo::cyber::TimerComponent {
 public:
  bool Init() override {
    prediction_writer_ =
        node_->CreateWriter<PredictionObstacles>(FLAGS_prediction_topic);
    std::function<void(const LocalizationMsgType &)> localization_callback =
      std::bind(&FakePredictionComponent::OnLocalization, this, std::placeholders::_1);
    auto localization_reader =
      node_->CreateReader("/apollo/localization/pose", localization_callback);
    return true;
  }
  void OnLocalization(const LocalizationMsgType &message)
  {
    AINFO<<"GET LOCALIZATION";
    localization_=*message;
  }
  void GetKeyBoardColorInput() {
    int8_t revent = 0;  // short
    struct pollfd fd = {STDIN_FILENO, POLLIN, revent};
    switch (poll(&fd, 1, 100)) {
      case -1:
        AERROR << "Failed to read keybapoard";
        break;
      case 0:
        break;
      default:
        char ch = 'x';
        std::cin >> ch;
        if (ch == 'c') {
            open_=!open_;
        }
        break;
    }
}
  bool Proc() override {
    PredictionObstacles prediction;
    Eigen::Affine3f trans;
    Eigen::Translation3f translation(localization_.pose().position().x() ,
                                    localization_.pose().position().y(),localization_.pose().position().z());
    Eigen::Quaternionf quater(localization_.pose().orientation().qw(),localization_.pose().orientation().qx(),
                                localization_.pose().orientation().qy(),localization_.pose().orientation().qz());
    Eigen::Vector3f v3fs,v3fd;
    trans=translation*quater.toRotationMatrix();
    //trans.pretranslate(translation);
    //trans.rotate(quater);
    if (!apollo::cyber::common::GetProtoFromFile("/apollo/modules/tools/prediction/fake_prediction/prediction_obstacles.pb.txt",
                                               &prediction)) {
    AERROR << "failed to load file: /apollo/modules/tools/prediction/fake_prediction/prediction_obstacles.pb.txt";
    return -1;
  }    
    common::util::FillHeader("fake_prediction", &prediction);
    //GetKeyBoardColorInput();
    if (!open_){
      prediction_writer_->Write(prediction);
      return true;
    }
    for (int i=0;i<prediction.prediction_obstacle_size();i++)
    {
      v3fs[0]=prediction.prediction_obstacle(i).perception_obstacle().position().x();
      v3fs[1]=prediction.prediction_obstacle(i).perception_obstacle().position().y();
      v3fs[2]=prediction.prediction_obstacle(i).perception_obstacle().position().z();
      v3fd=trans.inverse()*v3fs;
      // std::cout<<"V3Fs "<<v3fs<<std::endl;
      // std::cout<<"trans linear"<<trans.linear()<<std::endl;
      // std::cout<<"trans translation"<<trans.translation()<<std::endl;
      prediction.mutable_prediction_obstacle(i)->mutable_perception_obstacle()->mutable_position()->set_x(v3fd[1]);
      prediction.mutable_prediction_obstacle(i)->mutable_perception_obstacle()->mutable_position()->set_y(v3fd[0]);
      prediction.mutable_prediction_obstacle(i)->mutable_perception_obstacle()->mutable_position()->set_z(v3fd[2]); 
      auto* polygon_pt = prediction.mutable_prediction_obstacle(i)->mutable_perception_obstacle()->add_polygon_point();  
      polygon_pt->set_x(v3fd[1]-0.5);
      polygon_pt->set_y(v3fd[0]-0.5);
      polygon_pt->set_z(0);
      polygon_pt = prediction.mutable_prediction_obstacle(i)->mutable_perception_obstacle()->add_polygon_point();  
      polygon_pt->set_x(v3fd[1]-0.5);
      polygon_pt->set_y(v3fd[0]+0.5);
      polygon_pt->set_z(0);
      polygon_pt = prediction.mutable_prediction_obstacle(i)->mutable_perception_obstacle()->add_polygon_point();  
      polygon_pt->set_x(v3fd[1]+0.5);
      polygon_pt->set_y(v3fd[0]+0.5);
      polygon_pt->set_z(0);
      polygon_pt = prediction.mutable_prediction_obstacle(i)->mutable_perception_obstacle()->add_polygon_point();  
      polygon_pt->set_x(v3fd[1]+0.5);
      polygon_pt->set_y(v3fd[0]-0.5);
      polygon_pt->set_z(0);

    }
    prediction_writer_->Write(prediction);
    return true;
  }

 private:
  std::shared_ptr<apollo::cyber::Writer<PredictionObstacles>>
      prediction_writer_;
  bool open_ = false;
  apollo::localization::LocalizationEstimate localization_;
};
CYBER_REGISTER_COMPONENT(FakePredictionComponent);

}  // namespace prediction
}  // namespace apollo
