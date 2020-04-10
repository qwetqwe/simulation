## 1.离线运行camera感知障碍物
- 1.1 camera和transformer的接口为transform_wrapper.cc，该程序只会记录1s的/tf 转换关系，当回放数据时需要先启动transformer模块，启动camera模块，再回放数据。无法循环回放，因为程序当前时间戳找不到缓存中的转换关系时，程序会报错。
- 1.2 camera感知只能处理rgb8格式、bgr8格式，gray格式数据，不支持yuyv的格式数据，需要在driver里提前转换为rgb8格式数据
- 1.3 运行摄像头感知命令：
``` sh
mainboard -d modules/transform/dag/static_transform.dag 
mainboard -d modules/perception/production/dag/dag_streaming_perception_camera.dag
```
dag_streaming_perception_camera.dag所启动的fusion_camera模块输出的坐标为相对坐标，
