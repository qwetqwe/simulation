# Aopollo5.5_core
## 介绍
L4样车核心代码,修复了5.5 Cyber_visualizer,适配了传感器驱动，CANBUS协议
相比于完整源码，裁减了：
  * 所有jpg png图片（直接运行可能导致dreamview出问题）
  * 所有.pt、.caffemodel模型（可能导致感知出现问题）
  * third_party (缺少部分本地依赖) 
##依赖
third_party 内容保存于 https://gitee.com/qwetqwe/apollo_third_party
##安装教程
  1. 首先下载apollo5.5源代码，安装apollo官方教程完成docker的安装、NVIDIA驱动安装、镜像下载。
  2. 将本仓库源码覆盖官方源码
  3. 下载third_party源码，将third_part源码覆盖官方源码
  4. 安装apollo官方教程完成编译。

