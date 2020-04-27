## 运动补偿模块严重拖慢运行速度
运动补偿中eigen运算`Eigen::Translation3d ti(t * translation); p = ti * p;` 会严重拖慢运行速度，经测试10w点数量级单帧数据运算需要150~200ms，所以无法启动运动补偿
``` c++  
for (auto& point : msg->point()) {
    float x_scalar = point.x();
    if (std::isnan(x_scalar)) {
    //  AERROR << "nan point do not need motion compensation";
      continue;
    } 

    float y_scalar = point.y();
    float z_scalar = point.z();
    Eigen::Vector3d p(x_scalar, y_scalar, z_scalar);

    uint64_t tp = point.timestamp();
    double t = static_cast<double>(timestamp_max - tp) * f;
    
    Eigen::Translation3d ti(t * translation);
    p = ti * p;
    
    auto* point_new = msg_compensated->add_point();
    point_new->set_intensity(point.intensity());
    point_new->set_timestamp(point.timestamp());
    point_new->set_x(static_cast<float>(p.x()));
    point_new->set_y(static_cast<float>(p.y()));
    point_new->set_z(static_cast<float>(p.z()));
  }
}
```