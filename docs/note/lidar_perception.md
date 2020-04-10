# 激光雷达障碍物感知
## Segmentation 分割算法
从分割算法的处理函数可以看到，首先对激光雷达点云进行预处理，然后进行ProcessCommon
```cpp
LidarProcessResult LidarObstacleSegmentation::Process(
    const LidarObstacleSegmentationOptions& options,
    const std::shared_ptr<apollo::drivers::PointCloud const>& message,
    LidarFrame* frame) {
  const auto& sensor_name = options.sensor_name;

  PERCEPTION_PERF_FUNCTION_WITH_INDICATOR(options.sensor_name);

  PERCEPTION_PERF_BLOCK_START();
  PointCloudPreprocessorOptions preprocessor_options;
  preprocessor_options.sensor2novatel_extrinsics =
      options.sensor2novatel_extrinsics;
  PERCEPTION_PERF_BLOCK_END_WITH_INDICATOR(sensor_name, "preprocess");
  if (cloud_preprocessor_.Preprocess(preprocessor_options, message, frame)) {
    return ProcessCommon(options, frame);
  }
  return LidarProcessResult(LidarErrorCode::PointCloudPreprocessorError,
                            "Failed to preprocess point cloud.");
}
``` 
### Preprecessor 
预处理主要做了过滤非正常值nan点云，过滤距离过远（阈值kPointInfThreshold）点云。过滤离车过近的点云（阈值box_backward_*）,过高的点云，并将激光雷达转换到世界坐标系下。
```cpp
bool PointCloudPreprocessor::Preprocess(
    const PointCloudPreprocessorOptions& options,
    const std::shared_ptr<apollo::drivers::PointCloud const>& message,
    LidarFrame* frame) const {
  if (frame == nullptr) {
    return false;
  }
  if (frame->cloud == nullptr) {
    frame->cloud = base::PointFCloudPool::Instance().Get();
  }
  if (frame->world_cloud == nullptr) {
    frame->world_cloud = base::PointDCloudPool::Instance().Get();
  }
  frame->cloud->set_timestamp(message->measurement_time());
  if (message->point_size() > 0) {
    frame->cloud->reserve(message->point_size());
    base::PointF point;
    for (int i = 0; i < message->point_size(); ++i) {
      const apollo::drivers::PointXYZIT& pt = message->point(i);
      if (filter_naninf_points_) {
        if (std::isnan(pt.x()) || std::isnan(pt.y()) || std::isnan(pt.z())) {
          continue;
        }
        if (fabs(pt.x()) > kPointInfThreshold ||
            fabs(pt.y()) > kPointInfThreshold ||
            fabs(pt.z()) > kPointInfThreshold) {
          continue;
        }
      }
      Eigen::Vector3d vec3d_lidar(pt.x(), pt.y(), pt.z());
      Eigen::Vector3d vec3d_novatel =
          options.sensor2novatel_extrinsics * vec3d_lidar;
      if (filter_nearby_box_points_ && vec3d_novatel[0] < box_forward_x_ &&
          vec3d_novatel[0] > box_backward_x_ &&
          vec3d_novatel[1] < box_forward_y_ &&
          vec3d_novatel[1] > box_backward_y_) {
        continue;
      }
      if (filter_high_z_points_ && pt.z() > z_threshold_) {
        continue;
      }
      point.x = pt.x();
      point.y = pt.y();
      point.z = pt.z();
      point.intensity = static_cast<float>(pt.intensity());
      frame->cloud->push_back(point, static_cast<double>(pt.timestamp()) * 1e-9,
                              FLT_MAX, i, 0);
    }
    TransformCloud(frame->cloud, frame->lidar2world_pose, frame->world_cloud);
  }
  return true;
}
```
ProcessCommon中首先对地图进行了更新，地图更新在MapManger::Update函数中
### 地图ROI更新
通过调用GetRoiHDMapStruct(point, roi_search_distance_,frame->hdmap_struct)函数可以得到ROI区域hdmap_struct。其中point为当前位置点，roi_search_distance_为搜索附近道路边界（road boundaries）和路口（junctions）的搜索范围。以roi区域以点形式表达
``` cpp
bool MapManager::Update(const MapManagerOptions& options, LidarFrame* frame) {
  if (!frame) {
    AINFO << "Frame is nullptr.";
    return false;
  }
  if (!(frame->hdmap_struct)) {
    frame->hdmap_struct.reset(new base::HdmapStruct);
  }
  if (!hdmap_input_) {
    AINFO << "Hdmap input is nullptr";
    return false;
  }
  if (update_pose_) {
    if (!QueryPose(&(frame->lidar2world_pose))) {
      AINFO << "Failed to query updated pose.";
    }
  }
  base::PointD point;
  point.x = frame->lidar2world_pose.translation()(0);
  point.y = frame->lidar2world_pose.translation()(1);
  point.z = frame->lidar2world_pose.translation()(2);
  if (!hdmap_input_->GetRoiHDMapStruct(point, roi_search_distance_,
                                       frame->hdmap_struct)) {
    frame->hdmap_struct->road_polygons.clear();
    frame->hdmap_struct->road_boundary.clear();
    frame->hdmap_struct->hole_polygons.clear();
    frame->hdmap_struct->junction_polygons.clear();
    AINFO << "Failed to get roi from hdmap.";
  }
  return true;
}
```
###分割