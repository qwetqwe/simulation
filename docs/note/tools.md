# Apollo常用工具链
## Perception
 - 发布空的预测消息 用以驱动planning模块运行 
     `python modules/tools/perception/empty_prediction.py `
 - 发布障碍物信息，障碍物数据以json形式保存。该脚本可以根据长宽高中心点位置自动计算polygon
     `cd modules/tools/perception/` 
     `bash garage_perception.bash`
 - 打印发布的感知消息
     `python modules/tools/perception/print_perception.py` 
## configurator
 - 方便修改各个模块pb.txt的配置文件的脚本，包括planning control canbus
  `python modules/tools/configurator/configurator.py`
## record
 - 提取record中lidar、camera、radar数据。其中record中channnel必须为CompressedImage。lidar、radar产生txt数据。camera产生jpg图片。配置文件在`parser_params.yaml`配置
  `neousys@in_dev_docker:/apollo/modules/tools/record_parse_save$ python record_parse_save.py`
 - 播放pb文件数据。可播放任意pb格式的文件数据，只能播放一个文件单帧数据。文件pb格式需要和topic匹配，具体匹配关系参见 `/apollo/modules/tools/common/message_manager.py`。
  `python replay_file.py /apollo/modules/planning/ttdata/sunnyvale_loop_test/4_localization.pb.txt --topic /apollo/localization/pose`
 - 将record中的channel为topic数据在start_time(s)持续时间为duration(s)的消息保存为txt
   * `python modules/tools/rosbag/dump_record.py --start_time 1 --duration 5  --topic /apollo/localization/pose apollo_rosbag/sensor_rgb.record data/dump`
## visualizer
### 离线障碍物视觉感知
  对图片集感知障碍物，输出感知结果图片、实时显示画面
`/apollo/bazel-bin/modules/perception/camera/tools/offline/offline_obstacle_pipeline --test_list /apollo/apollo_rosbag//apollo_rosbag_camera_6mm_front/file_list.txt --image_root /apollo/apollo_rosbag/apollo_rosbag_camera_6mm_front/ --sensor_name front_6mm --camera_fps 20 --config_file obstacle_offline.pt --image_ext .jpeg > out.txt 2>&1`
#### 参数说明：
- test_list:测试图片名字集合 `camera_name`/`image_name`格式
- image_root: 图片存放目录
- camera_fpb: 图片帧率
- sensor_name: 传感器名，多传感器以逗号间隔 `front_6mm,front_12mm`
- config_file 配置文件，需修改传感器名
### 离线障碍物点云感知
   对pcd文件感知障碍物，输出目标信息
`bash modules/perception/lidar/tools/run_offline_lidar_obstacle_perception.sh `
 apollo 内有pcl库，可以通过`pcl_viewer`命令查看pcd文件
 ## map
- pb、xml、bin间地图格式转换：
  * `./bazel-bin/modules/map/tools/bin_map_generator`
  * `./bazel-bin/modules/map/tools/bin2pb_map_generator`
  * `./bazel-bin/modules/map/tools/proto_map_generator`
- 四元数->欧拉角、航向角转换
  * `./bazel-bin/modules/map/tools/quaternion_euler --qw 1 --qx 0 --qy 0 --qz 0`
- 给地图坐标x,y添加一个偏置
  * `./bazel-bin/modules/map/tools/map_tools`
- 转换xy->sl坐标系，得到所在车道线信息
  * `./bazel-bin/modules/map/tools/map_xysl --map_dir /apollo/data/ --xy_to_sl --x 586179.44606769411 --y 4140996.1733102929`
- 转换sl->xy坐标系，得到所在车道线信息
  * `./bazel-bin/modules/map/tools/map_xysl --map_dir /apollo/data/ --sl_to_xy --lane 1268_1_-1 --s 3 --l 0` 
- 计算xy在车道线lane的投影坐标sl
  * `./bazel-bin/modules/map/tools/map_xysl --map_dir /apollo/data/ --xy_to_lane --lane 1268_1_-1 --x 586235.83691703307 --y 4141224.5352289011`
- 计算from_lane的 s,0点在to_lane的sl坐标
  * `./bazel-bin/modules/map/tools/map_xysl --map_dir /apollo/data/ --lane_to_lane --from_lane 1268_1_-1 --to_lane 1268_1_-2 --s 2`
- 查看lane_id 的车道线信息
   * ` ./bazel-bin/modules/map/tools/map_xysl --map_dir /apollo/data/ --lane 256_1_-1`
-  打印信号灯信息
   * `./bazel-bin/modules/map/tools/map_xysl --map_dir /apollo/data/ --signal_info 2232`
- 打印overlap
   * `./bazel-bin/modules/map/tools/map_xysl --map_dir /apollo/data/ --overlap overlap_6770`
- 显示地图道路
   * ` python modules/tools/mapshow/roadshow.py -m modules/map/data/sunnyvale_big_loop/base_map.bin `
- 显示地图车道线
   * `/apollo$ python modules/tools/mapshow/mapshow.py -m modules/map/data/sunnyvale_big_loop/sim_map.bin`
  ### routing map
- 由base.map生成routing_map
   * `./bazel-bin/modules/routing/topo_creator/topo_creator --base_map_path /apollo/data/base_map.txt --routing_map_path /apollo/data/routing_map.txt`
- 查看topo图。 可以查到某个lane的后继并在图中画出
   * `python modules/tools/routing/debug_topo.py modules/map/data/sunnyvale_loop/`
- 将routing_map.bin转换为txt格式
   * `./bazel-bin/modules/map/tools/bin2pb_graph_generator --map_file modules/map/data/sunnyvale_loop/routing_map.bin --output_dir /apollo/data/`
- 在网页中画出高精地图，需要提前配置环境py27bokeh
   * `python modules/tools/mapviewer/hdmapviwer.py -m map_path_and_file`

