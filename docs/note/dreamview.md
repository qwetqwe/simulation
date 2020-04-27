## 如何启用Start Auto 按键？
Start Auto 按键需要planning 模块发出的engage_advice置为READY_TO_ENGAGE才可以使用。
点击Start Auto后，如果当前为人工模式，会发出apollo/control/pad　action start命令，激活自动模式；如果当前为自动模式，会发出reset命令进入手动模式。切换逻辑详见hmi_worker.cc的bool HMIWorker::Trigger(const HMIAction action)函数。

## dreamview所显示的障碍物信息来源？
障碍物显示既可以依赖于感知的topic也可以仅以来预测的topic

## 如何显示摄像头图像?
需要在global_flagfile.txt中配置长焦和短焦摄像头topic,FLAGS_image_long_topic和FLAGS_image_short_topic。其中长焦需要原始的Image格式话题，短焦需要压缩后的CompressedImage话题

## 如何显示点云?
需要在global_flagfile.txt配置点云topic FLAGS_pointcloud_topic

## 更换车辆
dreamview在右上角更换车辆，车辆需放在modules/calibration/data文件夹。更换车辆后dreamview会重新配置VehicleConfigHelper，读取车辆边界几何信息。

## 启动模块
在Modules controller中，按模块按钮会打开或关闭模块，这个按钮还可以监控模块状态，如果模块关闭按钮也会关闭。模块状态监控是靠monitor来完成的，monitor会发布/apollo/monitor/system_status 各个模块的状态信息

## 启用仿真时间
若利用回放数据作为启用模块的输入，需要在global_flagfile.txt中设置仿真时间标志位--use_sim_time=true