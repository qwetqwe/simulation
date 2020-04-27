## 标定表制作
参见/home/neousys/apollo5.5/docs/howto/how_to_update_vehicle_calibration_cn.md
标定表数据要对齐，每一个速度既要有加速度也要有减速度指令数据
## 配置文件
control_test_duration: -1.0  测试模式，持续时间，启动测试模式大于0
enable_csv_debug: false
enable_speed_station_preview: false 是否采用预瞄速度唯一
is_control_test_mode: false
use_preview_speed_for_table: false  查表中使用预瞄速度还是当前速度
enable_input_timestamp_check: false
max_localization_miss_num: 20
max_planning_miss_num: 20
max_acceleration_when_stopped: 0.01  接近停车过程的最大减速度，若需求减速度小于该值，速度低于最低速度精度，则输出减速度和速度为0
max_path_remain_when_stopped: 0.3  接近停车过程停车距离小于该值，则采用standstill减速度减速
steer_angle_rate: 200.0  转向速度
enable_gain_scheduler: true 横向控制权重增益用于告诉转向，通过查表lat_err_gain_scheduler和heading_err_gain_scheduler得到
set_steer_limit: true 根据最大的横向加速度限制转向角度

enable_slope_offset: false
control_period: 0.01
trajectory_period: 0.1
chassis_period: 0.01
localization_period: 0.01  判断定位消息时间戳漏了多少个消息
max_status_interval_sec: 0.1
max_planning_interval_sec: 0.2
max_planning_delay_threshold: 4.0
action: STOP
soft_estop_brake: 50.0 设置estop
active_controllers: LAT_CONTROLLER
active_controllers: LON_CONTROLLER
max_steering_percentage_allowed: 100
query_relative_time: 0.8   用于查询最近点的偏后时间
minimum_speed_resolution: 0.2
minimum_speed_protection: 0.1 避免更新LQR矩阵时速度为0
lat_controller_conf {
  ts: 0.01
  preview_window: 0
  cf: 155493.663
  cr: 155493.663
  mass_fl: 55   
  mass_fr: 55
  mass_rl: 65
  mass_rr: 65
  eps: 0.01
  matrix_q: 0.05
  matrix_q: 0.0
  matrix_q: 1.0
  matrix_q: 0.0
  reverse_matrix_q: 0.05
  reverse_matrix_q: 0.0
  reverse_matrix_q: 1.0
  reverse_matrix_q: 0.0
  cutoff_freq: 10
  mean_filter_window_size: 10
  max_iteration: 150
  max_lateral_acceleration: 5.0
  lat_err_gain_scheduler {
    scheduler {
      speed: 2.0
      ratio: 1.0
    }
    scheduler {
      speed: 3.0
      ratio: 0.6
    }
    scheduler {
      speed: 4.0
      ratio: 0.2
    }
    scheduler {
      speed: 5.0
      ratio: 0.1
    }
    scheduler {
      speed: 6.0
      ratio: 0.05
    }
  }
  heading_err_gain_scheduler {
    scheduler {
      speed: 4.0
      ratio: 1.0
    }
    scheduler {
      speed: 8.0
      ratio: 0.6
    }
    scheduler {
      speed: 12.0
      ratio: 0.4
    }
    scheduler {
      speed: 20.0
      ratio: 0.2
    }
    scheduler {
      speed: 25.0
      ratio: 0.1
    }
  }
  reverse_leadlag_conf {
    innerstate_saturation_level: 3000.0
    alpha: 1.0
    beta: 1.0
    tau: 0.0
  }
  enable_reverse_leadlag_compensation: true
  enable_look_ahead_back_control: true
  lookahead_station: 1.4224
  lookback_station: 2.8448
}
lon_controller_conf {
  ts: 0.01
  brake_minimum_action: 0.0
  throttle_minimum_action: 0
  speed_controller_input_limit: 2
  station_error_limit: 2
  preview_window: 20.0
  standstill_acceleration: -4.0
  station_pid_conf {
    integrator_enable: true
    integrator_saturation_level: 0.3
    kp: 0.5
    ki: 0
    kd: 0.0
  }
  low_speed_pid_conf {
    integrator_enable: true
    integrator_saturation_level: 0.3
    kp: 0.5
    ki: 3
    kd: 0.0
  }
  high_speed_pid_conf {
    integrator_enable: true
    integrator_saturation_level: 0.3
    kp: 0.3
    ki: 3
    kd: 0.0
  }
  switch_speed: 5
  reverse_station_pid_conf {
    integrator_enable: true
    integrator_saturation_level: 0.5
    kp: 0.4
    ki: 0.1
    kd: 0.0
  }
  reverse_speed_pid_conf {
    integrator_enable: true
    integrator_saturation_level: 0.5
    kp: 2.0
    ki: 0.3
    kd: 0.0
  }
  pitch_angle_filter_conf {
    cutoff_freq: 5
  }
  reverse_station_leadlag_conf {
    innerstate_saturation_level: 1000.0
    alpha: 1.0
    beta: 1.0
    tau: 0.0
  }
  reverse_speed_leadlag_conf {
    innerstate_saturation_level: 1000.0
    alpha: 1.0
    beta: 1.0
    tau: 0.0
  }
  calibration_table {
    calibration {
      speed: 0.2
      acceleration: -0.01
      command: -1.0
    }
    calibration {
      speed: 0.2
      acceleration: 0.0
      command: -6.0
    }
    calibration {
      speed: 0.2
      acceleration: 0.87
      command: 30.0
    }
    calibration {
      speed: 0.2
      acceleration: 0.9
      command: 33.0
    }
    calibration {
      speed: 0.2
      acceleration: 1.0
      command: 37.0
    }
    calibration {
      speed: 0.2
      acceleration: 1.09
      command: 39.0
    }
    calibration {
      speed: 0.2
      acceleration: 1.17
      command: 55.0
    }
    calibration {
      speed: 0.2
      acceleration: 1.21
      command: 48.0
    }
    calibration {
      speed: 0.2
      acceleration: 1.23
      command: 50.0
    }
    calibration {
      speed: 0.2
      acceleration: 1.25
      command: 42.0
    }
    calibration {
      speed: 0.2
      acceleration: 1.27
      command: 44.0
    }
    calibration {
      speed: 0.2
      acceleration: 1.37
      command: 50.0
    }
    calibration {
      speed: 0.2
      acceleration: 1.49
      command: 45.0
    }
    calibration {
      speed: 0.4
      acceleration: -0.34
      command: -1.0
    }
    calibration {
      speed: 0.4
      acceleration: -0.02
      command: -2.0
    }
    calibration {
      speed: 0.4
      acceleration: 0.0
      command: -6.5
    }
    calibration {
      speed: 0.4
      acceleration: 0.9
      command: 30.0
    }
    calibration {
      speed: 0.4
      acceleration: 0.93
      command: 33.0
    }
    calibration {
      speed: 0.4
      acceleration: 1.03
      command: 37.0
    }
    calibration {
      speed: 0.4
      acceleration: 1.12
      command: 39.0
    }
    calibration {
      speed: 0.4
      acceleration: 1.26
      command: 44.5
    }
    calibration {
      speed: 0.4
      acceleration: 1.3
      command: 48.5
    }
    calibration {
      speed: 0.4
      acceleration: 1.31
      command: 43.0
    }
    calibration {
      speed: 0.4
      acceleration: 1.35
      command: 47.0
    }
    calibration {
      speed: 0.4
      acceleration: 1.4
      command: 55.0
    }
    calibration {
      speed: 0.4
      acceleration: 1.51
      command: 45.0
    }
    calibration {
      speed: 0.4
      acceleration: 1.56
      command: 46.0
    }
    calibration {
      speed: 0.4
      acceleration: 1.66
      command: 50.0
    }
    calibration {
      speed: 0.6
      acceleration: -2.64
      command: -8.0
    }
    calibration {
      speed: 0.6
      acceleration: -2.31
      command: -10.0
    }
    calibration {
      speed: 0.6
      acceleration: -2.25
      command: -6.0
    }
    calibration {
      speed: 0.6
      acceleration: -2.23
      command: -6.0
    }
    calibration {
      speed: 0.6
      acceleration: -2.13
      command: -9.0
    }
    calibration {
      speed: 0.6
      acceleration: -2.06
      command: -4.0
    }
    calibration {
      speed: 0.6
      acceleration: -1.96
      command: -3.0
    }
    calibration {
      speed: 0.6
      acceleration: -1.76
      command: -2.0
    }
    calibration {
      speed: 0.6
      acceleration: -1.67
      command: -1.0
    }
    calibration {
      speed: 0.6
      acceleration: 0.91
      command: 30.0
    }
    calibration {
      speed: 0.6
      acceleration: 0.96
      command: 33.0
    }
    calibration {
      speed: 0.6
      acceleration: 1.09
      command: 37.0
    }
    calibration {
      speed: 0.6
      acceleration: 1.13
      command: 39.0
    }
    calibration {
      speed: 0.6
      acceleration: 1.27
      command: 41.0
    }
    calibration {
      speed: 0.6
      acceleration: 1.34
      command: 43.0
    }
    calibration {
      speed: 0.6
      acceleration: 1.37
      command: 47.0
    }
    calibration {
      speed: 0.6
      acceleration: 1.39
      command: 48.5
    }
    calibration {
      speed: 0.6
      acceleration: 1.43
      command: 55.0
    }
    calibration {
      speed: 0.6
      acceleration: 1.44
      command: 48.0
    }
    calibration {
      speed: 0.6
      acceleration: 1.55
      command: 49.0
    }
    calibration {
      speed: 0.6
      acceleration: 1.6
      command: 46.0
    }
    calibration {
      speed: 0.6
      acceleration: 1.67
      command: 45.0
    }
    calibration {
      speed: 0.6
      acceleration: 1.69
      command: 50.0
    }
    calibration {
      speed: 0.8
      acceleration: -4.42
      command: -10.0
    }
    calibration {
      speed: 0.8
      acceleration: -4.13
      command: -8.0
    }
    calibration {
      speed: 0.8
      acceleration: -3.99
      command: -9.0
    }
    calibration {
      speed: 0.8
      acceleration: -3.72
      command: -7.0
    }
    calibration {
      speed: 0.8
      acceleration: -3.47
      command: -6.0
    }
    calibration {
      speed: 0.8
      acceleration: -3.3
      command: -5.0
    }
    calibration {
      speed: 0.8
      acceleration: -2.93
      command: -4.0
    }
    calibration {
      speed: 0.8
      acceleration: -2.67
      command: -3.0
    }
    calibration {
      speed: 0.8
      acceleration: -2.14
      command: -2.0
    }
    calibration {
      speed: 0.8
      acceleration: -1.82
      command: -1.0
    }
    calibration {
      speed: 0.8
      acceleration: 0.92
      command: 30.0
    }
    calibration {
      speed: 0.8
      acceleration: 1.03
      command: 33.0
    }
    calibration {
      speed: 0.8
      acceleration: 1.14
      command: 37.0
    }
    calibration {
      speed: 0.8
      acceleration: 1.15
      command: 39.0
    }
    calibration {
      speed: 0.8
      acceleration: 1.28
      command: 41.0
    }
    calibration {
      speed: 0.8
      acceleration: 1.36
      command: 43.0
    }
    calibration {
      speed: 0.8
      acceleration: 1.39
      command: 47.0
    }
    calibration {
      speed: 0.8
      acceleration: 1.43
      command: 44.0
    }
    calibration {
      speed: 0.8
      acceleration: 1.46
      command: 55.0
    }
    calibration {
      speed: 0.8
      acceleration: 1.49
      command: 48.0
    }
    calibration {
      speed: 0.8
      acceleration: 1.54
      command: 53.0
    }
    calibration {
      speed: 0.8
      acceleration: 1.63
      command: 46.0
    }
    calibration {
      speed: 0.8
      acceleration: 1.64
      command: 49.0
    }
    calibration {
      speed: 0.8
      acceleration: 1.71
      command: 45.0
    }
    calibration {
      speed: 0.8
      acceleration: 1.72
      command: 50.0
    }
    calibration {
      speed: 1.0
      acceleration: -5.06
      command: -10.0
    }
    calibration {
      speed: 1.0
      acceleration: -4.68
      command: -8.0
    }
    calibration {
      speed: 1.0
      acceleration: -4.64
      command: -9.0
    }
    calibration {
      speed: 1.0
      acceleration: -4.13
      command: -7.0
    }
    calibration {
      speed: 1.0
      acceleration: -3.82
      command: -6.0
    }
    calibration {
      speed: 1.0
      acceleration: -3.54
      command: -5.0
    }
    calibration {
      speed: 1.0
      acceleration: -3.12
      command: -4.0
    }
    calibration {
      speed: 1.0
      acceleration: -2.78
      command: -3.0
    }
    calibration {
      speed: 1.0
      acceleration: -2.13
      command: -2.0
    }
    calibration {
      speed: 1.0
      acceleration: -1.77
      command: -1.0
    }
    calibration {
      speed: 1.0
      acceleration: 1.0
      command: 30.0
    }
    calibration {
      speed: 1.0
      acceleration: 1.08
      command: 33.0
    }
    calibration {
      speed: 1.0
      acceleration: 1.17
      command: 37.0
    }
    calibration {
      speed: 1.0
      acceleration: 1.18
      command: 39.0
    }
    calibration {
      speed: 1.0
      acceleration: 1.35
      command: 41.0
    }
    calibration {
      speed: 1.0
      acceleration: 1.41
      command: 47.0
    }
    calibration {
      speed: 1.0
      acceleration: 1.42
      command: 43.0
    }
    calibration {
      speed: 1.0
      acceleration: 1.47
      command: 44.0
    }
    calibration {
      speed: 1.0
      acceleration: 1.5
      command: 55.0
    }
    calibration {
      speed: 1.0
      acceleration: 1.54
      command: 48.0
    }
    calibration {
      speed: 1.0
      acceleration: 1.65
      command: 53.0
    }
    calibration {
      speed: 1.0
      acceleration: 1.71
      command: 46.0
    }
    calibration {
      speed: 1.0
      acceleration: 1.73
      command: 47.0
    }
    calibration {
      speed: 1.0
      acceleration: 1.84
      command: 50.0
    }
    calibration {
      speed: 1.2
      acceleration: -5.26
      command: -10.0
    }
    calibration {
      speed: 1.2
      acceleration: -4.8
      command: -8.0
    }
    calibration {
      speed: 1.2
      acceleration: -4.76
      command: -9.0
    }
    calibration {
      speed: 1.2
      acceleration: -4.22
      command: -7.0
    }
    calibration {
      speed: 1.2
      acceleration: -3.89
      command: -6.0
    }
    calibration {
      speed: 1.2
      acceleration: -3.56
      command: -5.0
    }
    calibration {
      speed: 1.2
      acceleration: -3.12
      command: -4.0
    }
    calibration {
      speed: 1.2
      acceleration: -2.74
      command: -3.0
    }
    calibration {
      speed: 1.2
      acceleration: -2.02
      command: -2.0
    }
    calibration {
      speed: 1.2
      acceleration: -1.66
      command: -1.0
    }
    calibration {
      speed: 1.2
      acceleration: 1.03
      command: 30.0
    }
    calibration {
      speed: 1.2
      acceleration: 1.13
      command: 33.0
    }
    calibration {
      speed: 1.2
      acceleration: 1.21
      command: 39.0
    }
    calibration {
      speed: 1.2
      acceleration: 1.22
      command: 37.0
    }
    calibration {
      speed: 1.2
      acceleration: 1.39
      command: 41.0
    }
    calibration {
      speed: 1.2
      acceleration: 1.47
      command: 43.0
    }
    calibration {
      speed: 1.2
      acceleration: 1.55
      command: 44.0
    }
    calibration {
      speed: 1.2
      acceleration: 1.56
      command: 48.0
    }
    calibration {
      speed: 1.2
      acceleration: 1.7
      command: 55.0
    }
    calibration {
      speed: 1.2
      acceleration: 1.73
      command: 46.5
    }
    calibration {
      speed: 1.2
      acceleration: 1.75
      command: 47.0
    }
    calibration {
      speed: 1.2
      acceleration: 1.76
      command: 53.0
    }
    calibration {
      speed: 1.2
      acceleration: 1.89
      command: 50.0
    }
    calibration {
      speed: 1.4
      acceleration: -5.29
      command: -10.0
    }
    calibration {
      speed: 1.4
      acceleration: -4.8
      command: -8.0
    }
    calibration {
      speed: 1.4
      acceleration: -4.79
      command: -9.0
    }
    calibration {
      speed: 1.4
      acceleration: -4.17
      command: -7.0
    }
    calibration {
      speed: 1.4
      acceleration: -3.86
      command: -6.0
    }
    calibration {
      speed: 1.4
      acceleration: -3.51
      command: -5.0
    }
    calibration {
      speed: 1.4
      acceleration: -3.07
      command: -4.0
    }
    calibration {
      speed: 1.4
      acceleration: -2.66
      command: -3.0
    }
    calibration {
      speed: 1.4
      acceleration: -1.94
      command: -2.0
    }
    calibration {
      speed: 1.4
      acceleration: -1.58
      command: -1.0
    }
    calibration {
      speed: 1.4
      acceleration: 1.06
      command: 30.0
    }
    calibration {
      speed: 1.4
      acceleration: 1.16
      command: 33.0
    }
    calibration {
      speed: 1.4
      acceleration: 1.24
      command: 39.0
    }
    calibration {
      speed: 1.4
      acceleration: 1.25
      command: 37.0
    }
    calibration {
      speed: 1.4
      acceleration: 1.42
      command: 41.0
    }
    calibration {
      speed: 1.4
      acceleration: 1.51
      command: 43.0
    }
    calibration {
      speed: 1.4
      acceleration: 1.62
      command: 44.0
    }
    calibration {
      speed: 1.4
      acceleration: 1.71
      command: 48.0
    }
    calibration {
      speed: 1.4
      acceleration: 1.75
      command: 55.0
    }
    calibration {
      speed: 1.4
      acceleration: 1.77
      command: 47.0
    }
    calibration {
      speed: 1.4
      acceleration: 1.78
      command: 49.0
    }
    calibration {
      speed: 1.4
      acceleration: 1.79
      command: 45.0
    }
    calibration {
      speed: 1.4
      acceleration: 1.83
      command: 46.0
    }
    calibration {
      speed: 1.4
      acceleration: 1.85
      command: 53.0
    }
    calibration {
      speed: 1.4
      acceleration: 1.92
      command: 50.0
    }
    calibration {
      speed: 1.6
      acceleration: -5.23
      command: -10.0
    }
    calibration {
      speed: 1.6
      acceleration: -4.75
      command: -9.0
    }
    calibration {
      speed: 1.6
      acceleration: -4.73
      command: -8.0
    }
    calibration {
      speed: 1.6
      acceleration: -4.1
      command: -7.0
    }
    calibration {
      speed: 1.6
      acceleration: -3.8
      command: -6.0
    }
    calibration {
      speed: 1.6
      acceleration: -3.43
      command: -5.0
    }
    calibration {
      speed: 1.6
      acceleration: -2.97
      command: -4.0
    }
    calibration {
      speed: 1.6
      acceleration: -2.58
      command: -3.0
    }
    calibration {
      speed: 1.6
      acceleration: -1.9
      command: -2.0
    }
    calibration {
      speed: 1.6
      acceleration: -1.55
      command: -1.0
    }
    calibration {
      speed: 1.6
      acceleration: 1.07
      command: 30.0
    }
    calibration {
      speed: 1.6
      acceleration: 1.22
      command: 33.0
    }
    calibration {
      speed: 1.6
      acceleration: 1.27
      command: 37.0
    }
    calibration {
      speed: 1.6
      acceleration: 1.28
      command: 39.0
    }
    calibration {
      speed: 1.6
      acceleration: 1.44
      command: 41.0
    }
    calibration {
      speed: 1.6
      acceleration: 1.56
      command: 43.0
    }
    calibration {
      speed: 1.6
      acceleration: 1.69
      command: 44.0
    }
    calibration {
      speed: 1.6
      acceleration: 1.77
      command: 48.0
    }
    calibration {
      speed: 1.6
      acceleration: 1.8
      command: 55.0
    }
    calibration {
      speed: 1.6
      acceleration: 1.88
      command: 46.5
    }
    calibration {
      speed: 1.6
      acceleration: 1.91
      command: 49.0
    }
    calibration {
      speed: 1.6
      acceleration: 1.93
      command: 45.0
    }
    calibration {
      speed: 1.6
      acceleration: 1.97
      command: 50.0
    }
    calibration {
      speed: 1.6
      acceleration: 2.0
      command: 53.0
    }
    calibration {
      speed: 1.8
      acceleration: -5.15
      command: -10.0
    }
    calibration {
      speed: 1.8
      acceleration: -4.7
      command: -8.0
    }
    calibration {
      speed: 1.8
      acceleration: -4.68
      command: -9.0
    }
    calibration {
      speed: 1.8
      acceleration: -3.98
      command: -7.0
    }
    calibration {
      speed: 1.8
      acceleration: -3.7
      command: -6.0
    }
    calibration {
      speed: 1.8
      acceleration: -3.32
      command: -5.0
    }
    calibration {
      speed: 1.8
      acceleration: -2.87
      command: -4.0
    }
    calibration {
      speed: 1.8
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 1.8
      acceleration: -1.87
      command: -2.0
    }
    calibration {
      speed: 1.8
      acceleration: -1.55
      command: -1.0
    }
    calibration {
      speed: 1.8
      acceleration: 1.07
      command: 30.0
    }
    calibration {
      speed: 1.8
      acceleration: 1.25
      command: 33.0
    }
    calibration {
      speed: 1.8
      acceleration: 1.28
      command: 37.0
    }
    calibration {
      speed: 1.8
      acceleration: 1.3
      command: 39.0
    }
    calibration {
      speed: 1.8
      acceleration: 1.48
      command: 41.0
    }
    calibration {
      speed: 1.8
      acceleration: 1.59
      command: 43.0
    }
    calibration {
      speed: 1.8
      acceleration: 1.77
      command: 44.0
    }
    calibration {
      speed: 1.8
      acceleration: 1.83
      command: 48.0
    }
    calibration {
      speed: 1.8
      acceleration: 1.96
      command: 49.0
    }
    calibration {
      speed: 1.8
      acceleration: 1.97
      command: 46.0
    }
    calibration {
      speed: 1.8
      acceleration: 1.98
      command: 55.0
    }
    calibration {
      speed: 1.8
      acceleration: 2.09
      command: 53.0
    }
    calibration {
      speed: 1.8
      acceleration: 2.1
      command: 50.0
    }
    calibration {
      speed: 2.0
      acceleration: -5.07
      command: -10.0
    }
    calibration {
      speed: 2.0
      acceleration: -4.55
      command: -8.0
    }
    calibration {
      speed: 2.0
      acceleration: -4.52
      command: -9.0
    }
    calibration {
      speed: 2.0
      acceleration: -3.89
      command: -7.0
    }
    calibration {
      speed: 2.0
      acceleration: -3.6
      command: -6.0
    }
    calibration {
      speed: 2.0
      acceleration: -3.23
      command: -5.0
    }
    calibration {
      speed: 2.0
      acceleration: -2.81
      command: -4.0
    }
    calibration {
      speed: 2.0
      acceleration: -2.46
      command: -3.0
    }
    calibration {
      speed: 2.0
      acceleration: -1.89
      command: -2.0
    }
    calibration {
      speed: 2.0
      acceleration: -1.58
      command: -1.0
    }
    calibration {
      speed: 2.0
      acceleration: 1.06
      command: 30.0
    }
    calibration {
      speed: 2.0
      acceleration: 1.28
      command: 33.0
    }
    calibration {
      speed: 2.0
      acceleration: 1.29
      command: 37.0
    }
    calibration {
      speed: 2.0
      acceleration: 1.35
      command: 39.0
    }
    calibration {
      speed: 2.0
      acceleration: 1.51
      command: 41.0
    }
    calibration {
      speed: 2.0
      acceleration: 1.62
      command: 43.0
    }
    calibration {
      speed: 2.0
      acceleration: 1.83
      command: 44.0
    }
    calibration {
      speed: 2.0
      acceleration: 1.94
      command: 48.0
    }
    calibration {
      speed: 2.0
      acceleration: 2.01
      command: 46.0
    }
    calibration {
      speed: 2.0
      acceleration: 2.03
      command: 55.0
    }
    calibration {
      speed: 2.0
      acceleration: 2.04
      command: 49.0
    }
    calibration {
      speed: 2.0
      acceleration: 2.06
      command: 47.0
    }
    calibration {
      speed: 2.0
      acceleration: 2.07
      command: 45.0
    }
    calibration {
      speed: 2.0
      acceleration: 2.21
      command: 53.0
    }
    calibration {
      speed: 2.0
      acceleration: 2.23
      command: 50.0
    }
    calibration {
      speed: 2.2
      acceleration: -4.93
      command: -10.0
    }
    calibration {
      speed: 2.2
      acceleration: -4.45
      command: -9.0
    }
    calibration {
      speed: 2.2
      acceleration: -4.43
      command: -8.0
    }
    calibration {
      speed: 2.2
      acceleration: -3.84
      command: -7.0
    }
    calibration {
      speed: 2.2
      acceleration: -3.54
      command: -6.0
    }
    calibration {
      speed: 2.2
      acceleration: -3.17
      command: -5.0
    }
    calibration {
      speed: 2.2
      acceleration: -2.77
      command: -4.0
    }
    calibration {
      speed: 2.2
      acceleration: -2.45
      command: -3.0
    }
    calibration {
      speed: 2.2
      acceleration: -1.92
      command: -2.0
    }
    calibration {
      speed: 2.2
      acceleration: -1.6
      command: -1.0
    }
    calibration {
      speed: 2.2
      acceleration: 1.05
      command: 30.0
    }
    calibration {
      speed: 2.2
      acceleration: 1.28
      command: 37.0
    }
    calibration {
      speed: 2.2
      acceleration: 1.31
      command: 33.0
    }
    calibration {
      speed: 2.2
      acceleration: 1.39
      command: 39.0
    }
    calibration {
      speed: 2.2
      acceleration: 1.54
      command: 41.0
    }
    calibration {
      speed: 2.2
      acceleration: 1.66
      command: 43.0
    }
    calibration {
      speed: 2.2
      acceleration: 1.89
      command: 44.0
    }
    calibration {
      speed: 2.2
      acceleration: 2.04
      command: 48.0
    }
    calibration {
      speed: 2.2
      acceleration: 2.08
      command: 46.0
    }
    calibration {
      speed: 2.2
      acceleration: 2.11
      command: 47.0
    }
    calibration {
      speed: 2.2
      acceleration: 2.15
      command: 47.0
    }
    calibration {
      speed: 2.2
      acceleration: 2.19
      command: 55.0
    }
    calibration {
      speed: 2.2
      acceleration: 2.27
      command: 50.0
    }
    calibration {
      speed: 2.2
      acceleration: 2.32
      command: 53.0
    }
    calibration {
      speed: 2.4
      acceleration: -4.81
      command: -10.0
    }
    calibration {
      speed: 2.4
      acceleration: -4.39
      command: -8.0
    }
    calibration {
      speed: 2.4
      acceleration: -4.38
      command: -9.0
    }
    calibration {
      speed: 2.4
      acceleration: -3.73
      command: -7.0
    }
    calibration {
      speed: 2.4
      acceleration: -3.48
      command: -6.0
    }
    calibration {
      speed: 2.4
      acceleration: -3.12
      command: -5.0
    }
    calibration {
      speed: 2.4
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 2.4
      acceleration: -2.45
      command: -3.0
    }
    calibration {
      speed: 2.4
      acceleration: -1.94
      command: -2.0
    }
    calibration {
      speed: 2.4
      acceleration: -1.62
      command: -1.0
    }
    calibration {
      speed: 2.4
      acceleration: 1.04
      command: 30.0
    }
    calibration {
      speed: 2.4
      acceleration: 1.28
      command: 37.0
    }
    calibration {
      speed: 2.4
      acceleration: 1.33
      command: 33.0
    }
    calibration {
      speed: 2.4
      acceleration: 1.44
      command: 39.0
    }
    calibration {
      speed: 2.4
      acceleration: 1.57
      command: 41.0
    }
    calibration {
      speed: 2.4
      acceleration: 1.7
      command: 43.0
    }
    calibration {
      speed: 2.4
      acceleration: 1.93
      command: 44.0
    }
    calibration {
      speed: 2.4
      acceleration: 2.06
      command: 48.0
    }
    calibration {
      speed: 2.4
      acceleration: 2.12
      command: 46.0
    }
    calibration {
      speed: 2.4
      acceleration: 2.18
      command: 45.0
    }
    calibration {
      speed: 2.4
      acceleration: 2.22
      command: 48.0
    }
    calibration {
      speed: 2.4
      acceleration: 2.25
      command: 55.0
    }
    calibration {
      speed: 2.4
      acceleration: 2.38
      command: 50.0
    }
    calibration {
      speed: 2.4
      acceleration: 2.42
      command: 53.0
    }
    calibration {
      speed: 2.6
      acceleration: -4.74
      command: -10.0
    }
    calibration {
      speed: 2.6
      acceleration: -4.3
      command: -8.0
    }
    calibration {
      speed: 2.6
      acceleration: -4.28
      command: -9.0
    }
    calibration {
      speed: 2.6
      acceleration: -3.68
      command: -7.0
    }
    calibration {
      speed: 2.6
      acceleration: -3.44
      command: -6.0
    }
    calibration {
      speed: 2.6
      acceleration: -3.09
      command: -5.0
    }
    calibration {
      speed: 2.6
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 2.6
      acceleration: -2.46
      command: -3.0
    }
    calibration {
      speed: 2.6
      acceleration: -1.97
      command: -2.0
    }
    calibration {
      speed: 2.6
      acceleration: -1.63
      command: -1.0
    }
    calibration {
      speed: 2.6
      acceleration: 1.03
      command: 30.0
    }
    calibration {
      speed: 2.6
      acceleration: 1.28
      command: 37.0
    }
    calibration {
      speed: 2.6
      acceleration: 1.35
      command: 33.0
    }
    calibration {
      speed: 2.6
      acceleration: 1.48
      command: 39.0
    }
    calibration {
      speed: 2.6
      acceleration: 1.6
      command: 41.0
    }
    calibration {
      speed: 2.6
      acceleration: 1.73
      command: 43.0
    }
    calibration {
      speed: 2.6
      acceleration: 1.97
      command: 44.0
    }
    calibration {
      speed: 2.6
      acceleration: 2.15
      command: 48.0
    }
    calibration {
      speed: 2.6
      acceleration: 2.16
      command: 46.0
    }
    calibration {
      speed: 2.6
      acceleration: 2.22
      command: 45.0
    }
    calibration {
      speed: 2.6
      acceleration: 2.27
      command: 49.0
    }
    calibration {
      speed: 2.6
      acceleration: 2.28
      command: 47.0
    }
    calibration {
      speed: 2.6
      acceleration: 2.37
      command: 55.0
    }
    calibration {
      speed: 2.6
      acceleration: 2.41
      command: 50.0
    }
    calibration {
      speed: 2.6
      acceleration: 2.51
      command: 53.0
    }
    calibration {
      speed: 2.8
      acceleration: -4.64
      command: -10.0
    }
    calibration {
      speed: 2.8
      acceleration: -4.23
      command: -8.0
    }
    calibration {
      speed: 2.8
      acceleration: -4.21
      command: -9.0
    }
    calibration {
      speed: 2.8
      acceleration: -3.65
      command: -7.0
    }
    calibration {
      speed: 2.8
      acceleration: -3.42
      command: -6.0
    }
    calibration {
      speed: 2.8
      acceleration: -3.08
      command: -5.0
    }
    calibration {
      speed: 2.8
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 2.8
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 2.8
      acceleration: -2.0
      command: -2.0
    }
    calibration {
      speed: 2.8
      acceleration: -1.63
      command: -1.0
    }
    calibration {
      speed: 2.8
      acceleration: 1.02
      command: 30.0
    }
    calibration {
      speed: 2.8
      acceleration: 1.28
      command: 37.0
    }
    calibration {
      speed: 2.8
      acceleration: 1.37
      command: 33.0
    }
    calibration {
      speed: 2.8
      acceleration: 1.51
      command: 39.0
    }
    calibration {
      speed: 2.8
      acceleration: 1.63
      command: 41.0
    }
    calibration {
      speed: 2.8
      acceleration: 1.75
      command: 43.0
    }
    calibration {
      speed: 2.8
      acceleration: 2.0
      command: 44.0
    }
    calibration {
      speed: 2.8
      acceleration: 2.16
      command: 48.0
    }
    calibration {
      speed: 2.8
      acceleration: 2.18
      command: 46.0
    }
    calibration {
      speed: 2.8
      acceleration: 2.25
      command: 45.0
    }
    calibration {
      speed: 2.8
      acceleration: 2.3
      command: 49.0
    }
    calibration {
      speed: 2.8
      acceleration: 2.35
      command: 47.0
    }
    calibration {
      speed: 2.8
      acceleration: 2.47
      command: 55.0
    }
    calibration {
      speed: 2.8
      acceleration: 2.5
      command: 50.0
    }
    calibration {
      speed: 2.8
      acceleration: 2.61
      command: 53.0
    }
    calibration {
      speed: 3.0
      acceleration: -4.56
      command: -10.0
    }
    calibration {
      speed: 3.0
      acceleration: -4.18
      command: -8.0
    }
    calibration {
      speed: 3.0
      acceleration: -4.17
      command: -9.0
    }
    calibration {
      speed: 3.0
      acceleration: -3.63
      command: -7.0
    }
    calibration {
      speed: 3.0
      acceleration: -3.41
      command: -6.0
    }
    calibration {
      speed: 3.0
      acceleration: -3.08
      command: -5.0
    }
    calibration {
      speed: 3.0
      acceleration: -2.78
      command: -4.0
    }
    calibration {
      speed: 3.0
      acceleration: -2.52
      command: -3.0
    }
    calibration {
      speed: 3.0
      acceleration: -2.01
      command: -2.0
    }
    calibration {
      speed: 3.0
      acceleration: -1.63
      command: -1.0
    }
    calibration {
      speed: 3.0
      acceleration: 1.0
      command: 30.0
    }
    calibration {
      speed: 3.0
      acceleration: 1.27
      command: 37.0
    }
    calibration {
      speed: 3.0
      acceleration: 1.38
      command: 33.0
    }
    calibration {
      speed: 3.0
      acceleration: 1.54
      command: 39.0
    }
    calibration {
      speed: 3.0
      acceleration: 1.65
      command: 41.0
    }
    calibration {
      speed: 3.0
      acceleration: 1.79
      command: 43.0
    }
    calibration {
      speed: 3.0
      acceleration: 2.02
      command: 44.0
    }
    calibration {
      speed: 3.0
      acceleration: 2.2
      command: 48.0
    }
    calibration {
      speed: 3.0
      acceleration: 2.21
      command: 46.0
    }
    calibration {
      speed: 3.0
      acceleration: 2.26
      command: 45.0
    }
    calibration {
      speed: 3.0
      acceleration: 2.38
      command: 49.0
    }
    calibration {
      speed: 3.0
      acceleration: 2.4
      command: 47.0
    }
    calibration {
      speed: 3.0
      acceleration: 2.52
      command: 55.0
    }
    calibration {
      speed: 3.0
      acceleration: 2.54
      command: 50.0
    }
    calibration {
      speed: 3.0
      acceleration: 2.68
      command: 53.0
    }
    calibration {
      speed: 3.2
      acceleration: -4.53
      command: -10.0
    }
    calibration {
      speed: 3.2
      acceleration: -4.14
      command: -8.0
    }
    calibration {
      speed: 3.2
      acceleration: -4.1
      command: -9.0
    }
    calibration {
      speed: 3.2
      acceleration: -3.62
      command: -7.0
    }
    calibration {
      speed: 3.2
      acceleration: -3.41
      command: -6.0
    }
    calibration {
      speed: 3.2
      acceleration: -3.11
      command: -5.0
    }
    calibration {
      speed: 3.2
      acceleration: -2.81
      command: -4.0
    }
    calibration {
      speed: 3.2
      acceleration: -2.55
      command: -3.0
    }
    calibration {
      speed: 3.2
      acceleration: -2.01
      command: -2.0
    }
    calibration {
      speed: 3.2
      acceleration: -1.62
      command: -1.0
    }
    calibration {
      speed: 3.2
      acceleration: 0.98
      command: 30.0
    }
    calibration {
      speed: 3.2
      acceleration: 1.27
      command: 37.0
    }
    calibration {
      speed: 3.2
      acceleration: 1.39
      command: 33.0
    }
    calibration {
      speed: 3.2
      acceleration: 1.56
      command: 39.0
    }
    calibration {
      speed: 3.2
      acceleration: 1.68
      command: 41.0
    }
    calibration {
      speed: 3.2
      acceleration: 1.82
      command: 43.0
    }
    calibration {
      speed: 3.2
      acceleration: 2.04
      command: 44.0
    }
    calibration {
      speed: 3.2
      acceleration: 2.23
      command: 46.0
    }
    calibration {
      speed: 3.2
      acceleration: 2.25
      command: 48.0
    }
    calibration {
      speed: 3.2
      acceleration: 2.28
      command: 45.0
    }
    calibration {
      speed: 3.2
      acceleration: 2.4
      command: 49.0
    }
    calibration {
      speed: 3.2
      acceleration: 2.45
      command: 47.0
    }
    calibration {
      speed: 3.2
      acceleration: 2.59
      command: 50.0
    }
    calibration {
      speed: 3.2
      acceleration: 2.6
      command: 55.0
    }
    calibration {
      speed: 3.2
      acceleration: 2.75
      command: 53.0
    }
    calibration {
      speed: 3.4
      acceleration: -4.47
      command: -10.0
    }
    calibration {
      speed: 3.4
      acceleration: -4.13
      command: -8.0
    }
    calibration {
      speed: 3.4
      acceleration: -4.09
      command: -9.0
    }
    calibration {
      speed: 3.4
      acceleration: -3.63
      command: -7.0
    }
    calibration {
      speed: 3.4
      acceleration: -3.43
      command: -6.0
    }
    calibration {
      speed: 3.4
      acceleration: -3.12
      command: -5.0
    }
    calibration {
      speed: 3.4
      acceleration: -2.84
      command: -4.0
    }
    calibration {
      speed: 3.4
      acceleration: -2.57
      command: -3.0
    }
    calibration {
      speed: 3.4
      acceleration: -2.01
      command: -2.0
    }
    calibration {
      speed: 3.4
      acceleration: -1.62
      command: -1.0
    }
    calibration {
      speed: 3.4
      acceleration: 0.96
      command: 30.0
    }
    calibration {
      speed: 3.4
      acceleration: 1.27
      command: 37.0
    }
    calibration {
      speed: 3.4
      acceleration: 1.39
      command: 33.0
    }
    calibration {
      speed: 3.4
      acceleration: 1.58
      command: 39.0
    }
    calibration {
      speed: 3.4
      acceleration: 1.69
      command: 41.0
    }
    calibration {
      speed: 3.4
      acceleration: 1.84
      command: 43.0
    }
    calibration {
      speed: 3.4
      acceleration: 2.05
      command: 44.0
    }
    calibration {
      speed: 3.4
      acceleration: 2.26
      command: 46.0
    }
    calibration {
      speed: 3.4
      acceleration: 2.27
      command: 48.0
    }
    calibration {
      speed: 3.4
      acceleration: 2.29
      command: 45.0
    }
    calibration {
      speed: 3.4
      acceleration: 2.44
      command: 49.0
    }
    calibration {
      speed: 3.4
      acceleration: 2.49
      command: 47.0
    }
    calibration {
      speed: 3.4
      acceleration: 2.64
      command: 50.0
    }
    calibration {
      speed: 3.4
      acceleration: 2.68
      command: 55.0
    }
    calibration {
      speed: 3.4
      acceleration: 2.8
      command: 53.0
    }
    calibration {
      speed: 3.6
      acceleration: -4.45
      command: -10.0
    }
    calibration {
      speed: 3.6
      acceleration: -4.12
      command: -8.0
    }
    calibration {
      speed: 3.6
      acceleration: -4.07
      command: -9.0
    }
    calibration {
      speed: 3.6
      acceleration: -3.65
      command: -7.0
    }
    calibration {
      speed: 3.6
      acceleration: -3.45
      command: -6.0
    }
    calibration {
      speed: 3.6
      acceleration: -3.15
      command: -5.0
    }
    calibration {
      speed: 3.6
      acceleration: -2.85
      command: -4.0
    }
    calibration {
      speed: 3.6
      acceleration: -2.58
      command: -3.0
    }
    calibration {
      speed: 3.6
      acceleration: -2.01
      command: -2.0
    }
    calibration {
      speed: 3.6
      acceleration: -1.61
      command: -1.0
    }
    calibration {
      speed: 3.6
      acceleration: 0.94
      command: 30.0
    }
    calibration {
      speed: 3.6
      acceleration: 1.27
      command: 37.0
    }
    calibration {
      speed: 3.6
      acceleration: 1.38
      command: 33.0
    }
    calibration {
      speed: 3.6
      acceleration: 1.59
      command: 39.0
    }
    calibration {
      speed: 3.6
      acceleration: 1.71
      command: 41.0
    }
    calibration {
      speed: 3.6
      acceleration: 1.86
      command: 43.0
    }
    calibration {
      speed: 3.6
      acceleration: 2.06
      command: 44.0
    }
    calibration {
      speed: 3.6
      acceleration: 2.28
      command: 46.0
    }
    calibration {
      speed: 3.6
      acceleration: 2.29
      command: 48.0
    }
    calibration {
      speed: 3.6
      acceleration: 2.31
      command: 45.0
    }
    calibration {
      speed: 3.6
      acceleration: 2.47
      command: 49.0
    }
    calibration {
      speed: 3.6
      acceleration: 2.52
      command: 47.0
    }
    calibration {
      speed: 3.6
      acceleration: 2.68
      command: 50.0
    }
    calibration {
      speed: 3.6
      acceleration: 2.73
      command: 55.0
    }
    calibration {
      speed: 3.6
      acceleration: 2.87
      command: 53.0
    }
    calibration {
      speed: 3.8
      acceleration: -4.43
      command: -10.0
    }
    calibration {
      speed: 3.8
      acceleration: -4.12
      command: -8.0
    }
    calibration {
      speed: 3.8
      acceleration: -4.06
      command: -9.0
    }
    calibration {
      speed: 3.8
      acceleration: -3.68
      command: -7.0
    }
    calibration {
      speed: 3.8
      acceleration: -3.47
      command: -6.0
    }
    calibration {
      speed: 3.8
      acceleration: -3.18
      command: -5.0
    }
    calibration {
      speed: 3.8
      acceleration: -2.88
      command: -4.0
    }
    calibration {
      speed: 3.8
      acceleration: -2.58
      command: -3.0
    }
    calibration {
      speed: 3.8
      acceleration: -2.0
      command: -2.0
    }
    calibration {
      speed: 3.8
      acceleration: -1.61
      command: -1.0
    }
    calibration {
      speed: 3.8
      acceleration: 0.92
      command: 30.0
    }
    calibration {
      speed: 3.8
      acceleration: 1.27
      command: 37.0
    }
    calibration {
      speed: 3.8
      acceleration: 1.38
      command: 33.0
    }
    calibration {
      speed: 3.8
      acceleration: 1.61
      command: 39.0
    }
    calibration {
      speed: 3.8
      acceleration: 1.72
      command: 41.0
    }
    calibration {
      speed: 3.8
      acceleration: 1.88
      command: 43.0
    }
    calibration {
      speed: 3.8
      acceleration: 2.07
      command: 44.0
    }
    calibration {
      speed: 3.8
      acceleration: 2.29
      command: 46.0
    }
    calibration {
      speed: 3.8
      acceleration: 2.31
      command: 46.5
    }
    calibration {
      speed: 3.8
      acceleration: 2.51
      command: 49.0
    }
    calibration {
      speed: 3.8
      acceleration: 2.54
      command: 47.0
    }
    calibration {
      speed: 3.8
      acceleration: 2.72
      command: 50.0
    }
    calibration {
      speed: 3.8
      acceleration: 2.79
      command: 55.0
    }
    calibration {
      speed: 3.8
      acceleration: 2.92
      command: 53.0
    }
    calibration {
      speed: 4.0
      acceleration: -4.43
      command: -10.0
    }
    calibration {
      speed: 4.0
      acceleration: -4.13
      command: -8.0
    }
    calibration {
      speed: 4.0
      acceleration: -4.07
      command: -9.0
    }
    calibration {
      speed: 4.0
      acceleration: -3.7
      command: -7.0
    }
    calibration {
      speed: 4.0
      acceleration: -3.5
      command: -6.0
    }
    calibration {
      speed: 4.0
      acceleration: -3.2
      command: -5.0
    }
    calibration {
      speed: 4.0
      acceleration: -2.88
      command: -4.0
    }
    calibration {
      speed: 4.0
      acceleration: -2.58
      command: -3.0
    }
    calibration {
      speed: 4.0
      acceleration: -2.0
      command: -2.0
    }
    calibration {
      speed: 4.0
      acceleration: -1.6
      command: -1.0
    }
    calibration {
      speed: 4.0
      acceleration: 0.9
      command: 30.0
    }
    calibration {
      speed: 4.0
      acceleration: 1.27
      command: 37.0
    }
    calibration {
      speed: 4.0
      acceleration: 1.38
      command: 33.0
    }
    calibration {
      speed: 4.0
      acceleration: 1.62
      command: 39.0
    }
    calibration {
      speed: 4.0
      acceleration: 1.73
      command: 41.0
    }
    calibration {
      speed: 4.0
      acceleration: 1.89
      command: 43.0
    }
    calibration {
      speed: 4.0
      acceleration: 2.08
      command: 44.0
    }
    calibration {
      speed: 4.0
      acceleration: 2.3
      command: 46.0
    }
    calibration {
      speed: 4.0
      acceleration: 2.32
      command: 45.0
    }
    calibration {
      speed: 4.0
      acceleration: 2.33
      command: 48.0
    }
    calibration {
      speed: 4.0
      acceleration: 2.54
      command: 49.0
    }
    calibration {
      speed: 4.0
      acceleration: 2.56
      command: 47.0
    }
    calibration {
      speed: 4.0
      acceleration: 2.75
      command: 50.0
    }
    calibration {
      speed: 4.0
      acceleration: 2.84
      command: 55.0
    }
    calibration {
      speed: 4.0
      acceleration: 2.97
      command: 53.0
    }
    calibration {
      speed: 4.2
      acceleration: -4.43
      command: -10.0
    }
    calibration {
      speed: 4.2
      acceleration: -4.14
      command: -8.0
    }
    calibration {
      speed: 4.2
      acceleration: -4.08
      command: -9.0
    }
    calibration {
      speed: 4.2
      acceleration: -3.72
      command: -7.0
    }
    calibration {
      speed: 4.2
      acceleration: -3.52
      command: -6.0
    }
    calibration {
      speed: 4.2
      acceleration: -3.21
      command: -5.0
    }
    calibration {
      speed: 4.2
      acceleration: -2.89
      command: -4.0
    }
    calibration {
      speed: 4.2
      acceleration: -2.57
      command: -3.0
    }
    calibration {
      speed: 4.2
      acceleration: -2.0
      command: -2.0
    }
    calibration {
      speed: 4.2
      acceleration: -1.6
      command: -1.0
    }
    calibration {
      speed: 4.2
      acceleration: 0.87
      command: 30.0
    }
    calibration {
      speed: 4.2
      acceleration: 1.27
      command: 37.0
    }
    calibration {
      speed: 4.2
      acceleration: 1.38
      command: 33.0
    }
    calibration {
      speed: 4.2
      acceleration: 1.63
      command: 39.0
    }
    calibration {
      speed: 4.2
      acceleration: 1.73
      command: 41.0
    }
    calibration {
      speed: 4.2
      acceleration: 1.9
      command: 43.0
    }
    calibration {
      speed: 4.2
      acceleration: 2.09
      command: 44.0
    }
    calibration {
      speed: 4.2
      acceleration: 2.32
      command: 46.0
    }
    calibration {
      speed: 4.2
      acceleration: 2.33
      command: 45.0
    }
    calibration {
      speed: 4.2
      acceleration: 2.35
      command: 48.0
    }
    calibration {
      speed: 4.2
      acceleration: 2.57
      command: 49.0
    }
    calibration {
      speed: 4.2
      acceleration: 2.58
      command: 47.0
    }
    calibration {
      speed: 4.2
      acceleration: 2.77
      command: 50.0
    }
    calibration {
      speed: 4.2
      acceleration: 2.9
      command: 55.0
    }
    calibration {
      speed: 4.2
      acceleration: 3.01
      command: 53.0
    }
    calibration {
      speed: 4.4
      acceleration: -4.45
      command: -10.0
    }
    calibration {
      speed: 4.4
      acceleration: -4.15
      command: -8.0
    }
    calibration {
      speed: 4.4
      acceleration: -4.1
      command: -9.0
    }
    calibration {
      speed: 4.4
      acceleration: -3.76
      command: -7.0
    }
    calibration {
      speed: 4.4
      acceleration: -3.54
      command: -6.0
    }
    calibration {
      speed: 4.4
      acceleration: -3.23
      command: -5.0
    }
    calibration {
      speed: 4.4
      acceleration: -2.88
      command: -4.0
    }
    calibration {
      speed: 4.4
      acceleration: -2.55
      command: -3.0
    }
    calibration {
      speed: 4.4
      acceleration: -2.0
      command: -2.0
    }
    calibration {
      speed: 4.4
      acceleration: -1.6
      command: -1.0
    }
    calibration {
      speed: 4.4
      acceleration: 0.84
      command: 30.0
    }
    calibration {
      speed: 4.4
      acceleration: 1.26
      command: 37.0
    }
    calibration {
      speed: 4.4
      acceleration: 1.38
      command: 33.0
    }
    calibration {
      speed: 4.4
      acceleration: 1.64
      command: 39.0
    }
    calibration {
      speed: 4.4
      acceleration: 1.74
      command: 41.0
    }
    calibration {
      speed: 4.4
      acceleration: 1.91
      command: 43.0
    }
    calibration {
      speed: 4.4
      acceleration: 2.09
      command: 44.0
    }
    calibration {
      speed: 4.4
      acceleration: 2.34
      command: 45.5
    }
    calibration {
      speed: 4.4
      acceleration: 2.36
      command: 48.0
    }
    calibration {
      speed: 4.4
      acceleration: 2.59
      command: 47.0
    }
    calibration {
      speed: 4.4
      acceleration: 2.6
      command: 49.0
    }
    calibration {
      speed: 4.4
      acceleration: 2.79
      command: 50.0
    }
    calibration {
      speed: 4.4
      acceleration: 2.95
      command: 55.0
    }
    calibration {
      speed: 4.4
      acceleration: 3.05
      command: 53.0
    }
    calibration {
      speed: 4.6
      acceleration: -4.47
      command: -10.0
    }
    calibration {
      speed: 4.6
      acceleration: -4.17
      command: -8.0
    }
    calibration {
      speed: 4.6
      acceleration: -4.12
      command: -9.0
    }
    calibration {
      speed: 4.6
      acceleration: -3.77
      command: -7.0
    }
    calibration {
      speed: 4.6
      acceleration: -3.55
      command: -6.0
    }
    calibration {
      speed: 4.6
      acceleration: -3.23
      command: -5.0
    }
    calibration {
      speed: 4.6
      acceleration: -2.88
      command: -4.0
    }
    calibration {
      speed: 4.6
      acceleration: -2.54
      command: -3.0
    }
    calibration {
      speed: 4.6
      acceleration: -2.0
      command: -2.0
    }
    calibration {
      speed: 4.6
      acceleration: -1.6
      command: -1.0
    }
    calibration {
      speed: 4.6
      acceleration: 0.8
      command: 30.0
    }
    calibration {
      speed: 4.6
      acceleration: 1.26
      command: 37.0
    }
    calibration {
      speed: 4.6
      acceleration: 1.39
      command: 33.0
    }
    calibration {
      speed: 4.6
      acceleration: 1.64
      command: 39.0
    }
    calibration {
      speed: 4.6
      acceleration: 1.74
      command: 41.0
    }
    calibration {
      speed: 4.6
      acceleration: 1.91
      command: 43.0
    }
    calibration {
      speed: 4.6
      acceleration: 2.1
      command: 44.0
    }
    calibration {
      speed: 4.6
      acceleration: 2.35
      command: 46.0
    }
    calibration {
      speed: 4.6
      acceleration: 2.36
      command: 45.0
    }
    calibration {
      speed: 4.6
      acceleration: 2.38
      command: 48.0
    }
    calibration {
      speed: 4.6
      acceleration: 2.61
      command: 47.0
    }
    calibration {
      speed: 4.6
      acceleration: 2.62
      command: 49.0
    }
    calibration {
      speed: 4.6
      acceleration: 2.82
      command: 50.0
    }
    calibration {
      speed: 4.6
      acceleration: 2.99
      command: 55.0
    }
    calibration {
      speed: 4.6
      acceleration: 3.09
      command: 53.0
    }
    calibration {
      speed: 4.8
      acceleration: -4.49
      command: -10.0
    }
    calibration {
      speed: 4.8
      acceleration: -4.19
      command: -8.0
    }
    calibration {
      speed: 4.8
      acceleration: -4.14
      command: -9.0
    }
    calibration {
      speed: 4.8
      acceleration: -3.79
      command: -7.0
    }
    calibration {
      speed: 4.8
      acceleration: -3.56
      command: -6.0
    }
    calibration {
      speed: 4.8
      acceleration: -3.23
      command: -5.0
    }
    calibration {
      speed: 4.8
      acceleration: -2.87
      command: -4.0
    }
    calibration {
      speed: 4.8
      acceleration: -2.53
      command: -3.0
    }
    calibration {
      speed: 4.8
      acceleration: -2.0
      command: -2.0
    }
    calibration {
      speed: 4.8
      acceleration: -1.6
      command: -1.0
    }
    calibration {
      speed: 4.8
      acceleration: 0.78
      command: 30.0
    }
    calibration {
      speed: 4.8
      acceleration: 1.25
      command: 37.0
    }
    calibration {
      speed: 4.8
      acceleration: 1.39
      command: 33.0
    }
    calibration {
      speed: 4.8
      acceleration: 1.64
      command: 39.0
    }
    calibration {
      speed: 4.8
      acceleration: 1.74
      command: 41.0
    }
    calibration {
      speed: 4.8
      acceleration: 1.92
      command: 43.0
    }
    calibration {
      speed: 4.8
      acceleration: 2.11
      command: 44.0
    }
    calibration {
      speed: 4.8
      acceleration: 2.37
      command: 46.0
    }
    calibration {
      speed: 4.8
      acceleration: 2.38
      command: 45.0
    }
    calibration {
      speed: 4.8
      acceleration: 2.41
      command: 48.0
    }
    calibration {
      speed: 4.8
      acceleration: 2.62
      command: 47.0
    }
    calibration {
      speed: 4.8
      acceleration: 2.65
      command: 49.0
    }
    calibration {
      speed: 4.8
      acceleration: 2.84
      command: 50.0
    }
    calibration {
      speed: 4.8
      acceleration: 3.03
      command: 55.0
    }
    calibration {
      speed: 4.8
      acceleration: 3.13
      command: 53.0
    }
    calibration {
      speed: 5.0
      acceleration: -4.52
      command: -10.0
    }
    calibration {
      speed: 5.0
      acceleration: -4.22
      command: -8.0
    }
    calibration {
      speed: 5.0
      acceleration: -4.16
      command: -9.0
    }
    calibration {
      speed: 5.0
      acceleration: -3.8
      command: -7.0
    }
    calibration {
      speed: 5.0
      acceleration: -3.57
      command: -6.0
    }
    calibration {
      speed: 5.0
      acceleration: -3.23
      command: -5.0
    }
    calibration {
      speed: 5.0
      acceleration: -2.84
      command: -4.0
    }
    calibration {
      speed: 5.0
      acceleration: -2.52
      command: -3.0
    }
    calibration {
      speed: 5.0
      acceleration: -2.0
      command: -2.0
    }
    calibration {
      speed: 5.0
      acceleration: -1.61
      command: -1.0
    }
    calibration {
      speed: 5.0
      acceleration: 0.77
      command: 30.0
    }
    calibration {
      speed: 5.0
      acceleration: 1.23
      command: 37.0
    }
    calibration {
      speed: 5.0
      acceleration: 1.4
      command: 33.0
    }
    calibration {
      speed: 5.0
      acceleration: 1.63
      command: 39.0
    }
    calibration {
      speed: 5.0
      acceleration: 1.73
      command: 41.0
    }
    calibration {
      speed: 5.0
      acceleration: 1.92
      command: 43.0
    }
    calibration {
      speed: 5.0
      acceleration: 2.12
      command: 44.0
    }
    calibration {
      speed: 5.0
      acceleration: 2.39
      command: 45.5
    }
    calibration {
      speed: 5.0
      acceleration: 2.43
      command: 48.0
    }
    calibration {
      speed: 5.0
      acceleration: 2.63
      command: 47.0
    }
    calibration {
      speed: 5.0
      acceleration: 2.67
      command: 49.0
    }
    calibration {
      speed: 5.0
      acceleration: 2.85
      command: 50.0
    }
    calibration {
      speed: 5.0
      acceleration: 3.06
      command: 55.0
    }
    calibration {
      speed: 5.0
      acceleration: 3.17
      command: 53.0
    }
    calibration {
      speed: 5.2
      acceleration: -4.55
      command: -10.0
    }
    calibration {
      speed: 5.2
      acceleration: -4.23
      command: -8.0
    }
    calibration {
      speed: 5.2
      acceleration: -4.18
      command: -9.0
    }
    calibration {
      speed: 5.2
      acceleration: -3.8
      command: -7.0
    }
    calibration {
      speed: 5.2
      acceleration: -3.57
      command: -6.0
    }
    calibration {
      speed: 5.2
      acceleration: -3.23
      command: -5.0
    }
    calibration {
      speed: 5.2
      acceleration: -2.83
      command: -4.0
    }
    calibration {
      speed: 5.2
      acceleration: -2.51
      command: -3.0
    }
    calibration {
      speed: 5.2
      acceleration: -2.0
      command: -2.0
    }
    calibration {
      speed: 5.2
      acceleration: -1.62
      command: -1.0
    }
    calibration {
      speed: 5.2
      acceleration: 0.77
      command: 30.0
    }
    calibration {
      speed: 5.2
      acceleration: 1.21
      command: 37.0
    }
    calibration {
      speed: 5.2
      acceleration: 1.4
      command: 33.0
    }
    calibration {
      speed: 5.2
      acceleration: 1.61
      command: 39.0
    }
    calibration {
      speed: 5.2
      acceleration: 1.72
      command: 41.0
    }
    calibration {
      speed: 5.2
      acceleration: 1.92
      command: 43.0
    }
    calibration {
      speed: 5.2
      acceleration: 2.13
      command: 44.0
    }
    calibration {
      speed: 5.2
      acceleration: 2.4
      command: 45.5
    }
    calibration {
      speed: 5.2
      acceleration: 2.44
      command: 48.0
    }
    calibration {
      speed: 5.2
      acceleration: 2.63
      command: 47.0
    }
    calibration {
      speed: 5.2
      acceleration: 2.7
      command: 49.0
    }
    calibration {
      speed: 5.2
      acceleration: 2.88
      command: 50.0
    }
    calibration {
      speed: 5.2
      acceleration: 3.09
      command: 55.0
    }
    calibration {
      speed: 5.2
      acceleration: 3.21
      command: 53.0
    }
    calibration {
      speed: 5.4
      acceleration: -4.57
      command: -10.0
    }
    calibration {
      speed: 5.4
      acceleration: -4.24
      command: -8.0
    }
    calibration {
      speed: 5.4
      acceleration: -4.2
      command: -9.0
    }
    calibration {
      speed: 5.4
      acceleration: -3.8
      command: -7.0
    }
    calibration {
      speed: 5.4
      acceleration: -3.57
      command: -6.0
    }
    calibration {
      speed: 5.4
      acceleration: -3.21
      command: -5.0
    }
    calibration {
      speed: 5.4
      acceleration: -2.81
      command: -4.0
    }
    calibration {
      speed: 5.4
      acceleration: -2.51
      command: -3.0
    }
    calibration {
      speed: 5.4
      acceleration: -2.0
      command: -2.0
    }
    calibration {
      speed: 5.4
      acceleration: -1.63
      command: -1.0
    }
    calibration {
      speed: 5.4
      acceleration: 0.73
      command: 30.0
    }
    calibration {
      speed: 5.4
      acceleration: 1.19
      command: 37.0
    }
    calibration {
      speed: 5.4
      acceleration: 1.4
      command: 33.0
    }
    calibration {
      speed: 5.4
      acceleration: 1.59
      command: 39.0
    }
    calibration {
      speed: 5.4
      acceleration: 1.71
      command: 41.0
    }
    calibration {
      speed: 5.4
      acceleration: 1.92
      command: 43.0
    }
    calibration {
      speed: 5.4
      acceleration: 2.14
      command: 44.0
    }
    calibration {
      speed: 5.4
      acceleration: 2.41
      command: 45.0
    }
    calibration {
      speed: 5.4
      acceleration: 2.42
      command: 46.0
    }
    calibration {
      speed: 5.4
      acceleration: 2.46
      command: 48.0
    }
    calibration {
      speed: 5.4
      acceleration: 2.64
      command: 47.0
    }
    calibration {
      speed: 5.4
      acceleration: 2.72
      command: 49.0
    }
    calibration {
      speed: 5.4
      acceleration: 2.9
      command: 50.0
    }
    calibration {
      speed: 5.4
      acceleration: 3.12
      command: 55.0
    }
    calibration {
      speed: 5.4
      acceleration: 3.25
      command: 53.0
    }
    calibration {
      speed: 5.6
      acceleration: -4.6
      command: -10.0
    }
    calibration {
      speed: 5.6
      acceleration: -4.25
      command: -8.0
    }
    calibration {
      speed: 5.6
      acceleration: -4.21
      command: -9.0
    }
    calibration {
      speed: 5.6
      acceleration: -3.8
      command: -7.0
    }
    calibration {
      speed: 5.6
      acceleration: -3.56
      command: -6.0
    }
    calibration {
      speed: 5.6
      acceleration: -3.21
      command: -5.0
    }
    calibration {
      speed: 5.6
      acceleration: -2.79
      command: -4.0
    }
    calibration {
      speed: 5.6
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 5.6
      acceleration: -2.0
      command: -2.0
    }
    calibration {
      speed: 5.6
      acceleration: -1.64
      command: -1.0
    }
    calibration {
      speed: 5.6
      acceleration: 0.66
      command: 30.0
    }
    calibration {
      speed: 5.6
      acceleration: 1.16
      command: 37.0
    }
    calibration {
      speed: 5.6
      acceleration: 1.39
      command: 33.0
    }
    calibration {
      speed: 5.6
      acceleration: 1.56
      command: 39.0
    }
    calibration {
      speed: 5.6
      acceleration: 1.7
      command: 41.0
    }
    calibration {
      speed: 5.6
      acceleration: 1.93
      command: 43.0
    }
    calibration {
      speed: 5.6
      acceleration: 2.15
      command: 44.0
    }
    calibration {
      speed: 5.6
      acceleration: 2.42
      command: 45.0
    }
    calibration {
      speed: 5.6
      acceleration: 2.43
      command: 46.0
    }
    calibration {
      speed: 5.6
      acceleration: 2.49
      command: 48.0
    }
    calibration {
      speed: 5.6
      acceleration: 2.65
      command: 47.0
    }
    calibration {
      speed: 5.6
      acceleration: 2.74
      command: 49.0
    }
    calibration {
      speed: 5.6
      acceleration: 2.91
      command: 50.0
    }
    calibration {
      speed: 5.6
      acceleration: 3.15
      command: 55.0
    }
    calibration {
      speed: 5.6
      acceleration: 3.28
      command: 53.0
    }
    calibration {
      speed: 5.8
      acceleration: -4.62
      command: -10.0
    }
    calibration {
      speed: 5.8
      acceleration: -4.25
      command: -8.0
    }
    calibration {
      speed: 5.8
      acceleration: -4.22
      command: -9.0
    }
    calibration {
      speed: 5.8
      acceleration: -3.79
      command: -7.0
    }
    calibration {
      speed: 5.8
      acceleration: -3.55
      command: -6.0
    }
    calibration {
      speed: 5.8
      acceleration: -3.2
      command: -5.0
    }
    calibration {
      speed: 5.8
      acceleration: -2.77
      command: -4.0
    }
    calibration {
      speed: 5.8
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 5.8
      acceleration: -2.0
      command: -2.0
    }
    calibration {
      speed: 5.8
      acceleration: -1.65
      command: -1.0
    }
    calibration {
      speed: 5.8
      acceleration: 0.58
      command: 30.0
    }
    calibration {
      speed: 5.8
      acceleration: 1.13
      command: 37.0
    }
    calibration {
      speed: 5.8
      acceleration: 1.38
      command: 33.0
    }
    calibration {
      speed: 5.8
      acceleration: 1.53
      command: 39.0
    }
    calibration {
      speed: 5.8
      acceleration: 1.68
      command: 41.0
    }
    calibration {
      speed: 5.8
      acceleration: 1.93
      command: 43.0
    }
    calibration {
      speed: 5.8
      acceleration: 2.15
      command: 44.0
    }
    calibration {
      speed: 5.8
      acceleration: 2.42
      command: 45.0
    }
    calibration {
      speed: 5.8
      acceleration: 2.43
      command: 46.0
    }
    calibration {
      speed: 5.8
      acceleration: 2.5
      command: 48.0
    }
    calibration {
      speed: 5.8
      acceleration: 2.66
      command: 47.0
    }
    calibration {
      speed: 5.8
      acceleration: 2.76
      command: 49.0
    }
    calibration {
      speed: 5.8
      acceleration: 2.94
      command: 50.0
    }
    calibration {
      speed: 5.8
      acceleration: 3.17
      command: 55.0
    }
    calibration {
      speed: 5.8
      acceleration: 3.32
      command: 53.0
    }
    calibration {
      speed: 6.0
      acceleration: -4.64
      command: -10.0
    }
    calibration {
      speed: 6.0
      acceleration: -4.24
      command: -8.0
    }
    calibration {
      speed: 6.0
      acceleration: -4.23
      command: -9.0
    }
    calibration {
      speed: 6.0
      acceleration: -3.78
      command: -7.0
    }
    calibration {
      speed: 6.0
      acceleration: -3.54
      command: -6.0
    }
    calibration {
      speed: 6.0
      acceleration: -3.18
      command: -5.0
    }
    calibration {
      speed: 6.0
      acceleration: -2.76
      command: -4.0
    }
    calibration {
      speed: 6.0
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 6.0
      acceleration: -2.0
      command: -2.0
    }
    calibration {
      speed: 6.0
      acceleration: -1.66
      command: -1.0
    }
    calibration {
      speed: 6.0
      acceleration: 0.56
      command: 30.0
    }
    calibration {
      speed: 6.0
      acceleration: 1.1
      command: 37.0
    }
    calibration {
      speed: 6.0
      acceleration: 1.36
      command: 33.0
    }
    calibration {
      speed: 6.0
      acceleration: 1.51
      command: 39.0
    }
    calibration {
      speed: 6.0
      acceleration: 1.66
      command: 41.0
    }
    calibration {
      speed: 6.0
      acceleration: 1.92
      command: 43.0
    }
    calibration {
      speed: 6.0
      acceleration: 2.15
      command: 44.0
    }
    calibration {
      speed: 6.0
      acceleration: 2.42
      command: 45.0
    }
    calibration {
      speed: 6.0
      acceleration: 2.44
      command: 46.0
    }
    calibration {
      speed: 6.0
      acceleration: 2.52
      command: 48.0
    }
    calibration {
      speed: 6.0
      acceleration: 2.66
      command: 47.0
    }
    calibration {
      speed: 6.0
      acceleration: 2.77
      command: 49.0
    }
    calibration {
      speed: 6.0
      acceleration: 2.95
      command: 50.0
    }
    calibration {
      speed: 6.0
      acceleration: 3.2
      command: 55.0
    }
    calibration {
      speed: 6.0
      acceleration: 3.35
      command: 53.0
    }
    calibration {
      speed: 6.2
      acceleration: -4.66
      command: -10.0
    }
    calibration {
      speed: 6.2
      acceleration: -4.24
      command: -8.0
    }
    calibration {
      speed: 6.2
      acceleration: -4.23
      command: -9.0
    }
    calibration {
      speed: 6.2
      acceleration: -3.76
      command: -7.0
    }
    calibration {
      speed: 6.2
      acceleration: -3.53
      command: -6.0
    }
    calibration {
      speed: 6.2
      acceleration: -3.17
      command: -5.0
    }
    calibration {
      speed: 6.2
      acceleration: -2.76
      command: -4.0
    }
    calibration {
      speed: 6.2
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 6.2
      acceleration: -2.0
      command: -2.0
    }
    calibration {
      speed: 6.2
      acceleration: -1.66
      command: -1.0
    }
    calibration {
      speed: 6.2
      acceleration: 0.57
      command: 30.0
    }
    calibration {
      speed: 6.2
      acceleration: 1.07
      command: 37.0
    }
    calibration {
      speed: 6.2
      acceleration: 1.34
      command: 33.0
    }
    calibration {
      speed: 6.2
      acceleration: 1.49
      command: 39.0
    }
    calibration {
      speed: 6.2
      acceleration: 1.64
      command: 41.0
    }
    calibration {
      speed: 6.2
      acceleration: 1.92
      command: 43.0
    }
    calibration {
      speed: 6.2
      acceleration: 2.15
      command: 44.0
    }
    calibration {
      speed: 6.2
      acceleration: 2.41
      command: 45.0
    }
    calibration {
      speed: 6.2
      acceleration: 2.44
      command: 46.0
    }
    calibration {
      speed: 6.2
      acceleration: 2.53
      command: 48.0
    }
    calibration {
      speed: 6.2
      acceleration: 2.67
      command: 47.0
    }
    calibration {
      speed: 6.2
      acceleration: 2.78
      command: 49.0
    }
    calibration {
      speed: 6.2
      acceleration: 2.96
      command: 50.0
    }
    calibration {
      speed: 6.2
      acceleration: 3.22
      command: 55.0
    }
    calibration {
      speed: 6.2
      acceleration: 3.4
      command: 53.0
    }
    calibration {
      speed: 6.4
      acceleration: -4.67
      command: -10.0
    }
    calibration {
      speed: 6.4
      acceleration: -4.23
      command: -8.5
    }
    calibration {
      speed: 6.4
      acceleration: -3.76
      command: -7.0
    }
    calibration {
      speed: 6.4
      acceleration: -3.51
      command: -6.0
    }
    calibration {
      speed: 6.4
      acceleration: -3.16
      command: -5.0
    }
    calibration {
      speed: 6.4
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 6.4
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 6.4
      acceleration: -2.0
      command: -2.0
    }
    calibration {
      speed: 6.4
      acceleration: -1.66
      command: -1.0
    }
    calibration {
      speed: 6.4
      acceleration: 0.58
      command: 30.0
    }
    calibration {
      speed: 6.4
      acceleration: 1.06
      command: 37.0
    }
    calibration {
      speed: 6.4
      acceleration: 1.31
      command: 33.0
    }
    calibration {
      speed: 6.4
      acceleration: 1.48
      command: 39.0
    }
    calibration {
      speed: 6.4
      acceleration: 1.61
      command: 41.0
    }
    calibration {
      speed: 6.4
      acceleration: 1.91
      command: 43.0
    }
    calibration {
      speed: 6.4
      acceleration: 2.14
      command: 44.0
    }
    calibration {
      speed: 6.4
      acceleration: 2.4
      command: 45.0
    }
    calibration {
      speed: 6.4
      acceleration: 2.44
      command: 46.0
    }
    calibration {
      speed: 6.4
      acceleration: 2.54
      command: 48.0
    }
    calibration {
      speed: 6.4
      acceleration: 2.67
      command: 47.0
    }
    calibration {
      speed: 6.4
      acceleration: 2.8
      command: 49.0
    }
    calibration {
      speed: 6.4
      acceleration: 2.97
      command: 50.0
    }
    calibration {
      speed: 6.4
      acceleration: 3.24
      command: 55.0
    }
    calibration {
      speed: 6.4
      acceleration: 3.42
      command: 53.0
    }
    calibration {
      speed: 6.6
      acceleration: -4.68
      command: -10.0
    }
    calibration {
      speed: 6.6
      acceleration: -4.22
      command: -9.0
    }
    calibration {
      speed: 6.6
      acceleration: -4.21
      command: -8.0
    }
    calibration {
      speed: 6.6
      acceleration: -3.73
      command: -7.0
    }
    calibration {
      speed: 6.6
      acceleration: -3.5
      command: -6.0
    }
    calibration {
      speed: 6.6
      acceleration: -3.15
      command: -5.0
    }
    calibration {
      speed: 6.6
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 6.6
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 6.6
      acceleration: -1.99
      command: -2.0
    }
    calibration {
      speed: 6.6
      acceleration: -1.65
      command: -1.0
    }
    calibration {
      speed: 6.6
      acceleration: 0.58
      command: 30.0
    }
    calibration {
      speed: 6.6
      acceleration: 1.07
      command: 37.0
    }
    calibration {
      speed: 6.6
      acceleration: 1.29
      command: 33.0
    }
    calibration {
      speed: 6.6
      acceleration: 1.47
      command: 39.0
    }
    calibration {
      speed: 6.6
      acceleration: 1.59
      command: 41.0
    }
    calibration {
      speed: 6.6
      acceleration: 1.89
      command: 43.0
    }
    calibration {
      speed: 6.6
      acceleration: 2.13
      command: 44.0
    }
    calibration {
      speed: 6.6
      acceleration: 2.39
      command: 45.0
    }
    calibration {
      speed: 6.6
      acceleration: 2.44
      command: 46.0
    }
    calibration {
      speed: 6.6
      acceleration: 2.55
      command: 48.0
    }
    calibration {
      speed: 6.6
      acceleration: 2.68
      command: 47.0
    }
    calibration {
      speed: 6.6
      acceleration: 2.81
      command: 49.0
    }
    calibration {
      speed: 6.6
      acceleration: 2.98
      command: 50.0
    }
    calibration {
      speed: 6.6
      acceleration: 3.27
      command: 55.0
    }
    calibration {
      speed: 6.6
      acceleration: 3.46
      command: 53.0
    }
    calibration {
      speed: 6.8
      acceleration: -4.68
      command: -10.0
    }
    calibration {
      speed: 6.8
      acceleration: -4.22
      command: -9.0
    }
    calibration {
      speed: 6.8
      acceleration: -4.19
      command: -8.0
    }
    calibration {
      speed: 6.8
      acceleration: -3.71
      command: -7.0
    }
    calibration {
      speed: 6.8
      acceleration: -3.49
      command: -6.0
    }
    calibration {
      speed: 6.8
      acceleration: -3.14
      command: -5.0
    }
    calibration {
      speed: 6.8
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 6.8
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 6.8
      acceleration: -1.99
      command: -2.0
    }
    calibration {
      speed: 6.8
      acceleration: -1.65
      command: -1.0
    }
    calibration {
      speed: 6.8
      acceleration: 0.59
      command: 30.0
    }
    calibration {
      speed: 6.8
      acceleration: 1.08
      command: 37.0
    }
    calibration {
      speed: 6.8
      acceleration: 1.26
      command: 33.0
    }
    calibration {
      speed: 6.8
      acceleration: 1.47
      command: 39.0
    }
    calibration {
      speed: 6.8
      acceleration: 1.57
      command: 41.0
    }
    calibration {
      speed: 6.8
      acceleration: 1.88
      command: 43.0
    }
    calibration {
      speed: 6.8
      acceleration: 2.11
      command: 44.0
    }
    calibration {
      speed: 6.8
      acceleration: 2.36
      command: 45.0
    }
    calibration {
      speed: 6.8
      acceleration: 2.44
      command: 46.0
    }
    calibration {
      speed: 6.8
      acceleration: 2.55
      command: 48.0
    }
    calibration {
      speed: 6.8
      acceleration: 2.68
      command: 47.0
    }
    calibration {
      speed: 6.8
      acceleration: 2.81
      command: 49.0
    }
    calibration {
      speed: 6.8
      acceleration: 2.99
      command: 50.0
    }
    calibration {
      speed: 6.8
      acceleration: 3.28
      command: 55.0
    }
    calibration {
      speed: 6.8
      acceleration: 3.49
      command: 53.0
    }
    calibration {
      speed: 7.0
      acceleration: -4.68
      command: -10.0
    }
    calibration {
      speed: 7.0
      acceleration: -4.21
      command: -9.0
    }
    calibration {
      speed: 7.0
      acceleration: -4.18
      command: -8.0
    }
    calibration {
      speed: 7.0
      acceleration: -3.7
      command: -7.0
    }
    calibration {
      speed: 7.0
      acceleration: -3.49
      command: -6.0
    }
    calibration {
      speed: 7.0
      acceleration: -3.14
      command: -5.0
    }
    calibration {
      speed: 7.0
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 7.0
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 7.0
      acceleration: -1.98
      command: -2.0
    }
    calibration {
      speed: 7.0
      acceleration: -1.64
      command: -1.0
    }
    calibration {
      speed: 7.0
      acceleration: 0.6
      command: 30.0
    }
    calibration {
      speed: 7.0
      acceleration: 1.1
      command: 37.0
    }
    calibration {
      speed: 7.0
      acceleration: 1.25
      command: 33.0
    }
    calibration {
      speed: 7.0
      acceleration: 1.47
      command: 39.0
    }
    calibration {
      speed: 7.0
      acceleration: 1.57
      command: 41.0
    }
    calibration {
      speed: 7.0
      acceleration: 1.86
      command: 43.0
    }
    calibration {
      speed: 7.0
      acceleration: 2.09
      command: 44.0
    }
    calibration {
      speed: 7.0
      acceleration: 2.34
      command: 45.0
    }
    calibration {
      speed: 7.0
      acceleration: 2.43
      command: 46.0
    }
    calibration {
      speed: 7.0
      acceleration: 2.54
      command: 48.0
    }
    calibration {
      speed: 7.0
      acceleration: 2.68
      command: 47.0
    }
    calibration {
      speed: 7.0
      acceleration: 2.82
      command: 49.0
    }
    calibration {
      speed: 7.0
      acceleration: 2.99
      command: 50.0
    }
    calibration {
      speed: 7.0
      acceleration: 3.31
      command: 55.0
    }
    calibration {
      speed: 7.0
      acceleration: 3.52
      command: 53.0
    }
    calibration {
      speed: 7.2
      acceleration: -4.68
      command: -10.0
    }
    calibration {
      speed: 7.2
      acceleration: -4.2
      command: -9.0
    }
    calibration {
      speed: 7.2
      acceleration: -4.16
      command: -8.0
    }
    calibration {
      speed: 7.2
      acceleration: -3.69
      command: -7.0
    }
    calibration {
      speed: 7.2
      acceleration: -3.48
      command: -6.0
    }
    calibration {
      speed: 7.2
      acceleration: -3.14
      command: -5.0
    }
    calibration {
      speed: 7.2
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 7.2
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 7.2
      acceleration: -1.98
      command: -2.0
    }
    calibration {
      speed: 7.2
      acceleration: -1.63
      command: -1.0
    }
    calibration {
      speed: 7.2
      acceleration: 0.63
      command: 30.0
    }
    calibration {
      speed: 7.2
      acceleration: 1.11
      command: 37.0
    }
    calibration {
      speed: 7.2
      acceleration: 1.23
      command: 33.0
    }
    calibration {
      speed: 7.2
      acceleration: 1.47
      command: 39.0
    }
    calibration {
      speed: 7.2
      acceleration: 1.57
      command: 41.0
    }
    calibration {
      speed: 7.2
      acceleration: 1.83
      command: 43.0
    }
    calibration {
      speed: 7.2
      acceleration: 2.06
      command: 44.0
    }
    calibration {
      speed: 7.2
      acceleration: 2.3
      command: 45.0
    }
    calibration {
      speed: 7.2
      acceleration: 2.42
      command: 46.0
    }
    calibration {
      speed: 7.2
      acceleration: 2.54
      command: 48.0
    }
    calibration {
      speed: 7.2
      acceleration: 2.68
      command: 47.0
    }
    calibration {
      speed: 7.2
      acceleration: 2.82
      command: 49.0
    }
    calibration {
      speed: 7.2
      acceleration: 2.99
      command: 50.0
    }
    calibration {
      speed: 7.2
      acceleration: 3.33
      command: 55.0
    }
    calibration {
      speed: 7.2
      acceleration: 3.56
      command: 53.0
    }
    calibration {
      speed: 7.4
      acceleration: -4.67
      command: -10.0
    }
    calibration {
      speed: 7.4
      acceleration: -4.19
      command: -9.0
    }
    calibration {
      speed: 7.4
      acceleration: -4.15
      command: -8.0
    }
    calibration {
      speed: 7.4
      acceleration: -3.68
      command: -7.0
    }
    calibration {
      speed: 7.4
      acceleration: -3.47
      command: -6.0
    }
    calibration {
      speed: 7.4
      acceleration: -3.13
      command: -5.0
    }
    calibration {
      speed: 7.4
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 7.4
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 7.4
      acceleration: -1.97
      command: -2.0
    }
    calibration {
      speed: 7.4
      acceleration: -1.62
      command: -1.0
    }
    calibration {
      speed: 7.4
      acceleration: 0.68
      command: 30.0
    }
    calibration {
      speed: 7.4
      acceleration: 1.12
      command: 37.0
    }
    calibration {
      speed: 7.4
      acceleration: 1.22
      command: 33.0
    }
    calibration {
      speed: 7.4
      acceleration: 1.47
      command: 39.0
    }
    calibration {
      speed: 7.4
      acceleration: 1.57
      command: 41.0
    }
    calibration {
      speed: 7.4
      acceleration: 1.81
      command: 43.0
    }
    calibration {
      speed: 7.4
      acceleration: 2.04
      command: 44.0
    }
    calibration {
      speed: 7.4
      acceleration: 2.27
      command: 45.0
    }
    calibration {
      speed: 7.4
      acceleration: 2.41
      command: 46.0
    }
    calibration {
      speed: 7.4
      acceleration: 2.53
      command: 48.0
    }
    calibration {
      speed: 7.4
      acceleration: 2.67
      command: 47.0
    }
    calibration {
      speed: 7.4
      acceleration: 2.82
      command: 49.0
    }
    calibration {
      speed: 7.4
      acceleration: 2.99
      command: 50.0
    }
    calibration {
      speed: 7.4
      acceleration: 3.34
      command: 55.0
    }
    calibration {
      speed: 7.4
      acceleration: 3.58
      command: 53.0
    }
    calibration {
      speed: 7.6
      acceleration: -4.66
      command: -10.0
    }
    calibration {
      speed: 7.6
      acceleration: -4.18
      command: -9.0
    }
    calibration {
      speed: 7.6
      acceleration: -4.13
      command: -8.0
    }
    calibration {
      speed: 7.6
      acceleration: -3.67
      command: -7.0
    }
    calibration {
      speed: 7.6
      acceleration: -3.47
      command: -6.0
    }
    calibration {
      speed: 7.6
      acceleration: -3.13
      command: -5.0
    }
    calibration {
      speed: 7.6
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 7.6
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 7.6
      acceleration: -1.97
      command: -2.0
    }
    calibration {
      speed: 7.6
      acceleration: -1.62
      command: -1.0
    }
    calibration {
      speed: 7.6
      acceleration: 0.71
      command: 30.0
    }
    calibration {
      speed: 7.6
      acceleration: 1.12
      command: 37.0
    }
    calibration {
      speed: 7.6
      acceleration: 1.21
      command: 33.0
    }
    calibration {
      speed: 7.6
      acceleration: 1.47
      command: 39.0
    }
    calibration {
      speed: 7.6
      acceleration: 1.58
      command: 41.0
    }
    calibration {
      speed: 7.6
      acceleration: 1.79
      command: 43.0
    }
    calibration {
      speed: 7.6
      acceleration: 2.01
      command: 44.0
    }
    calibration {
      speed: 7.6
      acceleration: 2.24
      command: 45.0
    }
    calibration {
      speed: 7.6
      acceleration: 2.4
      command: 46.0
    }
    calibration {
      speed: 7.6
      acceleration: 2.52
      command: 48.0
    }
    calibration {
      speed: 7.6
      acceleration: 2.67
      command: 47.0
    }
    calibration {
      speed: 7.6
      acceleration: 2.81
      command: 49.0
    }
    calibration {
      speed: 7.6
      acceleration: 2.99
      command: 50.0
    }
    calibration {
      speed: 7.6
      acceleration: 3.36
      command: 55.0
    }
    calibration {
      speed: 7.6
      acceleration: 3.6
      command: 53.0
    }
    calibration {
      speed: 7.8
      acceleration: -4.65
      command: -10.0
    }
    calibration {
      speed: 7.8
      acceleration: -4.17
      command: -9.0
    }
    calibration {
      speed: 7.8
      acceleration: -4.11
      command: -8.0
    }
    calibration {
      speed: 7.8
      acceleration: -3.66
      command: -7.0
    }
    calibration {
      speed: 7.8
      acceleration: -3.47
      command: -6.0
    }
    calibration {
      speed: 7.8
      acceleration: -3.13
      command: -5.0
    }
    calibration {
      speed: 7.8
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 7.8
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 7.8
      acceleration: -1.96
      command: -2.0
    }
    calibration {
      speed: 7.8
      acceleration: -1.63
      command: -1.0
    }
    calibration {
      speed: 7.8
      acceleration: 0.7
      command: 30.0
    }
    calibration {
      speed: 7.8
      acceleration: 1.12
      command: 37.0
    }
    calibration {
      speed: 7.8
      acceleration: 1.18
      command: 33.0
    }
    calibration {
      speed: 7.8
      acceleration: 1.47
      command: 39.0
    }
    calibration {
      speed: 7.8
      acceleration: 1.59
      command: 41.0
    }
    calibration {
      speed: 7.8
      acceleration: 1.77
      command: 43.0
    }
    calibration {
      speed: 7.8
      acceleration: 1.99
      command: 44.0
    }
    calibration {
      speed: 7.8
      acceleration: 2.21
      command: 45.0
    }
    calibration {
      speed: 7.8
      acceleration: 2.39
      command: 46.0
    }
    calibration {
      speed: 7.8
      acceleration: 2.51
      command: 48.0
    }
    calibration {
      speed: 7.8
      acceleration: 2.65
      command: 47.0
    }
    calibration {
      speed: 7.8
      acceleration: 2.8
      command: 49.0
    }
    calibration {
      speed: 7.8
      acceleration: 2.98
      command: 50.0
    }
    calibration {
      speed: 7.8
      acceleration: 3.38
      command: 55.0
    }
    calibration {
      speed: 7.8
      acceleration: 3.63
      command: 53.0
    }
    calibration {
      speed: 8.0
      acceleration: -4.64
      command: -10.0
    }
    calibration {
      speed: 8.0
      acceleration: -4.17
      command: -9.0
    }
    calibration {
      speed: 8.0
      acceleration: -4.11
      command: -8.0
    }
    calibration {
      speed: 8.0
      acceleration: -3.66
      command: -7.0
    }
    calibration {
      speed: 8.0
      acceleration: -3.47
      command: -6.0
    }
    calibration {
      speed: 8.0
      acceleration: -3.13
      command: -5.0
    }
    calibration {
      speed: 8.0
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 8.0
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 8.0
      acceleration: -1.96
      command: -2.0
    }
    calibration {
      speed: 8.0
      acceleration: -1.64
      command: -1.0
    }
    calibration {
      speed: 8.0
      acceleration: 0.66
      command: 30.0
    }
    calibration {
      speed: 8.0
      acceleration: 1.11
      command: 37.0
    }
    calibration {
      speed: 8.0
      acceleration: 1.14
      command: 33.0
    }
    calibration {
      speed: 8.0
      acceleration: 1.46
      command: 39.0
    }
    calibration {
      speed: 8.0
      acceleration: 1.59
      command: 41.0
    }
    calibration {
      speed: 8.0
      acceleration: 1.76
      command: 43.0
    }
    calibration {
      speed: 8.0
      acceleration: 1.96
      command: 44.0
    }
    calibration {
      speed: 8.0
      acceleration: 2.18
      command: 45.0
    }
    calibration {
      speed: 8.0
      acceleration: 2.37
      command: 46.0
    }
    calibration {
      speed: 8.0
      acceleration: 2.5
      command: 48.0
    }
    calibration {
      speed: 8.0
      acceleration: 2.63
      command: 47.0
    }
    calibration {
      speed: 8.0
      acceleration: 2.79
      command: 49.0
    }
    calibration {
      speed: 8.0
      acceleration: 2.97
      command: 50.0
    }
    calibration {
      speed: 8.0
      acceleration: 3.39
      command: 55.0
    }
    calibration {
      speed: 8.0
      acceleration: 3.64
      command: 53.0
    }
    calibration {
      speed: 8.2
      acceleration: -4.63
      command: -10.0
    }
    calibration {
      speed: 8.2
      acceleration: -4.16
      command: -9.0
    }
    calibration {
      speed: 8.2
      acceleration: -4.09
      command: -8.0
    }
    calibration {
      speed: 8.2
      acceleration: -3.66
      command: -7.0
    }
    calibration {
      speed: 8.2
      acceleration: -3.47
      command: -6.0
    }
    calibration {
      speed: 8.2
      acceleration: -3.13
      command: -5.0
    }
    calibration {
      speed: 8.2
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 8.2
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 8.2
      acceleration: -1.96
      command: -2.0
    }
    calibration {
      speed: 8.2
      acceleration: -1.65
      command: -1.0
    }
    calibration {
      speed: 8.2
      acceleration: 0.64
      command: 30.0
    }
    calibration {
      speed: 8.2
      acceleration: 1.09
      command: 33.0
    }
    calibration {
      speed: 8.2
      acceleration: 1.11
      command: 37.0
    }
    calibration {
      speed: 8.2
      acceleration: 1.45
      command: 39.0
    }
    calibration {
      speed: 8.2
      acceleration: 1.6
      command: 41.0
    }
    calibration {
      speed: 8.2
      acceleration: 1.75
      command: 43.0
    }
    calibration {
      speed: 8.2
      acceleration: 1.95
      command: 44.0
    }
    calibration {
      speed: 8.2
      acceleration: 2.14
      command: 45.0
    }
    calibration {
      speed: 8.2
      acceleration: 2.35
      command: 46.0
    }
    calibration {
      speed: 8.2
      acceleration: 2.49
      command: 48.0
    }
    calibration {
      speed: 8.2
      acceleration: 2.61
      command: 47.0
    }
    calibration {
      speed: 8.2
      acceleration: 2.78
      command: 49.0
    }
    calibration {
      speed: 8.2
      acceleration: 2.96
      command: 50.0
    }
    calibration {
      speed: 8.2
      acceleration: 3.41
      command: 55.0
    }
    calibration {
      speed: 8.2
      acceleration: 3.65
      command: 53.0
    }
    calibration {
      speed: 8.4
      acceleration: -4.62
      command: -10.0
    }
    calibration {
      speed: 8.4
      acceleration: -4.16
      command: -9.0
    }
    calibration {
      speed: 8.4
      acceleration: -4.08
      command: -8.0
    }
    calibration {
      speed: 8.4
      acceleration: -3.66
      command: -7.0
    }
    calibration {
      speed: 8.4
      acceleration: -3.47
      command: -6.0
    }
    calibration {
      speed: 8.4
      acceleration: -3.14
      command: -5.0
    }
    calibration {
      speed: 8.4
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 8.4
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 8.4
      acceleration: -1.96
      command: -2.0
    }
    calibration {
      speed: 8.4
      acceleration: -1.67
      command: -1.0
    }
    calibration {
      speed: 8.4
      acceleration: 0.72
      command: 30.0
    }
    calibration {
      speed: 8.4
      acceleration: 1.03
      command: 33.0
    }
    calibration {
      speed: 8.4
      acceleration: 1.12
      command: 37.0
    }
    calibration {
      speed: 8.4
      acceleration: 1.45
      command: 39.0
    }
    calibration {
      speed: 8.4
      acceleration: 1.59
      command: 41.0
    }
    calibration {
      speed: 8.4
      acceleration: 1.74
      command: 43.0
    }
    calibration {
      speed: 8.4
      acceleration: 1.94
      command: 44.0
    }
    calibration {
      speed: 8.4
      acceleration: 2.12
      command: 45.0
    }
    calibration {
      speed: 8.4
      acceleration: 2.34
      command: 46.0
    }
    calibration {
      speed: 8.4
      acceleration: 2.49
      command: 48.0
    }
    calibration {
      speed: 8.4
      acceleration: 2.59
      command: 47.0
    }
    calibration {
      speed: 8.4
      acceleration: 2.78
      command: 49.0
    }
    calibration {
      speed: 8.4
      acceleration: 2.95
      command: 50.0
    }
    calibration {
      speed: 8.4
      acceleration: 3.42
      command: 55.0
    }
    calibration {
      speed: 8.4
      acceleration: 3.66
      command: 53.0
    }
    calibration {
      speed: 8.6
      acceleration: -4.6
      command: -10.0
    }
    calibration {
      speed: 8.6
      acceleration: -4.15
      command: -9.0
    }
    calibration {
      speed: 8.6
      acceleration: -4.08
      command: -8.0
    }
    calibration {
      speed: 8.6
      acceleration: -3.66
      command: -7.0
    }
    calibration {
      speed: 8.6
      acceleration: -3.47
      command: -6.0
    }
    calibration {
      speed: 8.6
      acceleration: -3.13
      command: -5.0
    }
    calibration {
      speed: 8.6
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 8.6
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 8.6
      acceleration: -1.96
      command: -2.0
    }
    calibration {
      speed: 8.6
      acceleration: -1.69
      command: -1.0
    }
    calibration {
      speed: 8.6
      acceleration: 0.7
      command: 30.0
    }
    calibration {
      speed: 8.6
      acceleration: 0.99
      command: 33.0
    }
    calibration {
      speed: 8.6
      acceleration: 1.13
      command: 37.0
    }
    calibration {
      speed: 8.6
      acceleration: 1.44
      command: 39.0
    }
    calibration {
      speed: 8.6
      acceleration: 1.57
      command: 41.0
    }
    calibration {
      speed: 8.6
      acceleration: 1.74
      command: 43.0
    }
    calibration {
      speed: 8.6
      acceleration: 1.94
      command: 44.0
    }
    calibration {
      speed: 8.6
      acceleration: 2.1
      command: 45.0
    }
    calibration {
      speed: 8.6
      acceleration: 2.33
      command: 46.0
    }
    calibration {
      speed: 8.6
      acceleration: 2.48
      command: 48.0
    }
    calibration {
      speed: 8.6
      acceleration: 2.57
      command: 47.0
    }
    calibration {
      speed: 8.6
      acceleration: 2.76
      command: 49.0
    }
    calibration {
      speed: 8.6
      acceleration: 2.94
      command: 50.0
    }
    calibration {
      speed: 8.6
      acceleration: 3.44
      command: 55.0
    }
    calibration {
      speed: 8.6
      acceleration: 3.66
      command: 53.0
    }
    calibration {
      speed: 8.8
      acceleration: -4.59
      command: -10.0
    }
    calibration {
      speed: 8.8
      acceleration: -4.16
      command: -9.0
    }
    calibration {
      speed: 8.8
      acceleration: -4.07
      command: -8.0
    }
    calibration {
      speed: 8.8
      acceleration: -3.66
      command: -7.0
    }
    calibration {
      speed: 8.8
      acceleration: -3.47
      command: -6.0
    }
    calibration {
      speed: 8.8
      acceleration: -3.13
      command: -5.0
    }
    calibration {
      speed: 8.8
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 8.8
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 8.8
      acceleration: -1.97
      command: -2.0
    }
    calibration {
      speed: 8.8
      acceleration: -1.7
      command: -1.0
    }
    calibration {
      speed: 8.8
      acceleration: 0.79
      command: 30.0
    }
    calibration {
      speed: 8.8
      acceleration: 0.99
      command: 33.0
    }
    calibration {
      speed: 8.8
      acceleration: 1.14
      command: 37.0
    }
    calibration {
      speed: 8.8
      acceleration: 1.43
      command: 39.0
    }
    calibration {
      speed: 8.8
      acceleration: 1.56
      command: 41.0
    }
    calibration {
      speed: 8.8
      acceleration: 1.74
      command: 43.0
    }
    calibration {
      speed: 8.8
      acceleration: 1.94
      command: 44.0
    }
    calibration {
      speed: 8.8
      acceleration: 2.09
      command: 45.0
    }
    calibration {
      speed: 8.8
      acceleration: 2.32
      command: 46.0
    }
    calibration {
      speed: 8.8
      acceleration: 2.48
      command: 48.0
    }
    calibration {
      speed: 8.8
      acceleration: 2.56
      command: 47.0
    }
    calibration {
      speed: 8.8
      acceleration: 2.76
      command: 49.0
    }
    calibration {
      speed: 8.8
      acceleration: 2.93
      command: 50.0
    }
    calibration {
      speed: 8.8
      acceleration: 3.45
      command: 55.0
    }
    calibration {
      speed: 8.8
      acceleration: 3.66
      command: 53.0
    }
    calibration {
      speed: 9.0
      acceleration: -4.58
      command: -10.0
    }
    calibration {
      speed: 9.0
      acceleration: -4.16
      command: -9.0
    }
    calibration {
      speed: 9.0
      acceleration: -4.07
      command: -8.0
    }
    calibration {
      speed: 9.0
      acceleration: -3.66
      command: -7.0
    }
    calibration {
      speed: 9.0
      acceleration: -3.46
      command: -6.0
    }
    calibration {
      speed: 9.0
      acceleration: -3.13
      command: -5.0
    }
    calibration {
      speed: 9.0
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 9.0
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 9.0
      acceleration: -1.98
      command: -2.0
    }
    calibration {
      speed: 9.0
      acceleration: -1.72
      command: -1.0
    }
    calibration {
      speed: 9.0
      acceleration: 0.83
      command: 30.0
    }
    calibration {
      speed: 9.0
      acceleration: 0.99
      command: 33.0
    }
    calibration {
      speed: 9.0
      acceleration: 1.15
      command: 37.0
    }
    calibration {
      speed: 9.0
      acceleration: 1.42
      command: 39.0
    }
    calibration {
      speed: 9.0
      acceleration: 1.53
      command: 41.0
    }
    calibration {
      speed: 9.0
      acceleration: 1.74
      command: 43.0
    }
    calibration {
      speed: 9.0
      acceleration: 1.94
      command: 44.0
    }
    calibration {
      speed: 9.0
      acceleration: 2.08
      command: 45.0
    }
    calibration {
      speed: 9.0
      acceleration: 2.31
      command: 46.0
    }
    calibration {
      speed: 9.0
      acceleration: 2.47
      command: 48.0
    }
    calibration {
      speed: 9.0
      acceleration: 2.53
      command: 47.0
    }
    calibration {
      speed: 9.0
      acceleration: 2.75
      command: 49.0
    }
    calibration {
      speed: 9.0
      acceleration: 2.92
      command: 50.0
    }
    calibration {
      speed: 9.0
      acceleration: 3.46
      command: 55.0
    }
    calibration {
      speed: 9.0
      acceleration: 3.66
      command: 53.0
    }
    calibration {
      speed: 9.2
      acceleration: -4.58
      command: -10.0
    }
    calibration {
      speed: 9.2
      acceleration: -4.16
      command: -9.0
    }
    calibration {
      speed: 9.2
      acceleration: -4.07
      command: -8.0
    }
    calibration {
      speed: 9.2
      acceleration: -3.67
      command: -7.0
    }
    calibration {
      speed: 9.2
      acceleration: -3.46
      command: -6.0
    }
    calibration {
      speed: 9.2
      acceleration: -3.13
      command: -5.0
    }
    calibration {
      speed: 9.2
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 9.2
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 9.2
      acceleration: -1.98
      command: -2.0
    }
    calibration {
      speed: 9.2
      acceleration: -1.72
      command: -1.0
    }
    calibration {
      speed: 9.2
      acceleration: 0.79
      command: 30.0
    }
    calibration {
      speed: 9.2
      acceleration: 0.99
      command: 33.0
    }
    calibration {
      speed: 9.2
      acceleration: 1.16
      command: 37.0
    }
    calibration {
      speed: 9.2
      acceleration: 1.4
      command: 39.0
    }
    calibration {
      speed: 9.2
      acceleration: 1.5
      command: 41.0
    }
    calibration {
      speed: 9.2
      acceleration: 1.73
      command: 43.0
    }
    calibration {
      speed: 9.2
      acceleration: 1.94
      command: 44.0
    }
    calibration {
      speed: 9.2
      acceleration: 2.07
      command: 45.0
    }
    calibration {
      speed: 9.2
      acceleration: 2.3
      command: 46.0
    }
    calibration {
      speed: 9.2
      acceleration: 2.47
      command: 48.0
    }
    calibration {
      speed: 9.2
      acceleration: 2.51
      command: 47.0
    }
    calibration {
      speed: 9.2
      acceleration: 2.75
      command: 49.0
    }
    calibration {
      speed: 9.2
      acceleration: 2.92
      command: 50.0
    }
    calibration {
      speed: 9.2
      acceleration: 3.46
      command: 55.0
    }
    calibration {
      speed: 9.2
      acceleration: 3.65
      command: 53.0
    }
    calibration {
      speed: 9.4
      acceleration: -4.57
      command: -10.0
    }
    calibration {
      speed: 9.4
      acceleration: -4.17
      command: -9.0
    }
    calibration {
      speed: 9.4
      acceleration: -4.07
      command: -8.0
    }
    calibration {
      speed: 9.4
      acceleration: -3.67
      command: -7.0
    }
    calibration {
      speed: 9.4
      acceleration: -3.46
      command: -6.0
    }
    calibration {
      speed: 9.4
      acceleration: -3.13
      command: -5.0
    }
    calibration {
      speed: 9.4
      acceleration: -2.75
      command: -4.0
    }
    calibration {
      speed: 9.4
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 9.4
      acceleration: -1.98
      command: -2.0
    }
    calibration {
      speed: 9.4
      acceleration: -1.72
      command: -1.0
    }
    calibration {
      speed: 9.4
      acceleration: 0.75
      command: 30.0
    }
    calibration {
      speed: 9.4
      acceleration: 0.91
      command: 33.0
    }
    calibration {
      speed: 9.4
      acceleration: 1.17
      command: 37.0
    }
    calibration {
      speed: 9.4
      acceleration: 1.38
      command: 39.0
    }
    calibration {
      speed: 9.4
      acceleration: 1.47
      command: 41.0
    }
    calibration {
      speed: 9.4
      acceleration: 1.73
      command: 43.0
    }
    calibration {
      speed: 9.4
      acceleration: 1.94
      command: 44.0
    }
    calibration {
      speed: 9.4
      acceleration: 2.06
      command: 45.0
    }
    calibration {
      speed: 9.4
      acceleration: 2.29
      command: 46.0
    }
    calibration {
      speed: 9.4
      acceleration: 2.47
      command: 48.0
    }
    calibration {
      speed: 9.4
      acceleration: 2.49
      command: 47.0
    }
    calibration {
      speed: 9.4
      acceleration: 2.74
      command: 49.0
    }
    calibration {
      speed: 9.4
      acceleration: 2.91
      command: 50.0
    }
    calibration {
      speed: 9.4
      acceleration: 3.47
      command: 55.0
    }
    calibration {
      speed: 9.4
      acceleration: 3.63
      command: 53.0
    }
    calibration {
      speed: 9.6
      acceleration: -4.56
      command: -10.0
    }
    calibration {
      speed: 9.6
      acceleration: -4.18
      command: -9.0
    }
    calibration {
      speed: 9.6
      acceleration: -4.08
      command: -8.0
    }
    calibration {
      speed: 9.6
      acceleration: -3.67
      command: -7.0
    }
    calibration {
      speed: 9.6
      acceleration: -3.45
      command: -6.0
    }
    calibration {
      speed: 9.6
      acceleration: -3.12
      command: -5.0
    }
    calibration {
      speed: 9.6
      acceleration: -2.76
      command: -4.0
    }
    calibration {
      speed: 9.6
      acceleration: -2.51
      command: -3.0
    }
    calibration {
      speed: 9.6
      acceleration: -1.98
      command: -2.0
    }
    calibration {
      speed: 9.6
      acceleration: -1.72
      command: -1.0
    }
    calibration {
      speed: 9.6
      acceleration: 0.73
      command: 33.0
    }
    calibration {
      speed: 9.6
      acceleration: 0.75
      command: 30.0
    }
    calibration {
      speed: 9.6
      acceleration: 1.17
      command: 37.0
    }
    calibration {
      speed: 9.6
      acceleration: 1.32
      command: 39.0
    }
    calibration {
      speed: 9.6
      acceleration: 1.44
      command: 41.0
    }
    calibration {
      speed: 9.6
      acceleration: 1.71
      command: 43.0
    }
    calibration {
      speed: 9.6
      acceleration: 1.94
      command: 44.0
    }
    calibration {
      speed: 9.6
      acceleration: 2.05
      command: 45.0
    }
    calibration {
      speed: 9.6
      acceleration: 2.29
      command: 46.0
    }
    calibration {
      speed: 9.6
      acceleration: 2.47
      command: 47.5
    }
    calibration {
      speed: 9.6
      acceleration: 2.74
      command: 49.0
    }
    calibration {
      speed: 9.6
      acceleration: 2.91
      command: 50.0
    }
    calibration {
      speed: 9.6
      acceleration: 3.47
      command: 55.0
    }
    calibration {
      speed: 9.6
      acceleration: 3.62
      command: 53.0
    }
    calibration {
      speed: 9.8
      acceleration: -4.55
      command: -10.0
    }
    calibration {
      speed: 9.8
      acceleration: -4.18
      command: -9.0
    }
    calibration {
      speed: 9.8
      acceleration: -4.08
      command: -8.0
    }
    calibration {
      speed: 9.8
      acceleration: -3.67
      command: -7.0
    }
    calibration {
      speed: 9.8
      acceleration: -3.45
      command: -6.0
    }
    calibration {
      speed: 9.8
      acceleration: -3.12
      command: -5.0
    }
    calibration {
      speed: 9.8
      acceleration: -2.76
      command: -4.0
    }
    calibration {
      speed: 9.8
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 9.8
      acceleration: -1.98
      command: -2.0
    }
    calibration {
      speed: 9.8
      acceleration: -1.71
      command: -1.0
    }
    calibration {
      speed: 9.8
      acceleration: 0.58
      command: 33.0
    }
    calibration {
      speed: 9.8
      acceleration: 0.76
      command: 30.0
    }
    calibration {
      speed: 9.8
      acceleration: 1.16
      command: 37.0
    }
    calibration {
      speed: 9.8
      acceleration: 1.27
      command: 39.0
    }
    calibration {
      speed: 9.8
      acceleration: 1.42
      command: 41.0
    }
    calibration {
      speed: 9.8
      acceleration: 1.68
      command: 43.0
    }
    calibration {
      speed: 9.8
      acceleration: 1.93
      command: 44.0
    }
    calibration {
      speed: 9.8
      acceleration: 2.03
      command: 45.0
    }
    calibration {
      speed: 9.8
      acceleration: 2.29
      command: 46.0
    }
    calibration {
      speed: 9.8
      acceleration: 2.46
      command: 47.0
    }
    calibration {
      speed: 9.8
      acceleration: 2.47
      command: 48.0
    }
    calibration {
      speed: 9.8
      acceleration: 2.75
      command: 49.0
    }
    calibration {
      speed: 9.8
      acceleration: 2.9
      command: 50.0
    }
    calibration {
      speed: 9.8
      acceleration: 3.47
      command: 55.0
    }
    calibration {
      speed: 9.8
      acceleration: 3.6
      command: 53.0
    }
    calibration {
      speed: 10.0
      acceleration: -4.55
      command: -10.0
    }
    calibration {
      speed: 10.0
      acceleration: -4.19
      command: -9.0
    }
    calibration {
      speed: 10.0
      acceleration: -4.08
      command: -8.0
    }
    calibration {
      speed: 10.0
      acceleration: -3.67
      command: -7.0
    }
    calibration {
      speed: 10.0
      acceleration: -3.44
      command: -6.0
    }
    calibration {
      speed: 10.0
      acceleration: -3.12
      command: -5.0
    }
    calibration {
      speed: 10.0
      acceleration: -2.77
      command: -4.0
    }
    calibration {
      speed: 10.0
      acceleration: -2.5
      command: -3.0
    }
    calibration {
      speed: 10.0
      acceleration: -1.98
      command: -2.0
    }
    calibration {
      speed: 10.0
      acceleration: -1.7
      command: -1.0
    }
    calibration {
      speed: 10.0
      acceleration: 0.56
      command: 33.0
    }
    calibration {
      speed: 10.0
      acceleration: 0.78
      command: 30.0
    }
    calibration {
      speed: 10.0
      acceleration: 1.14
      command: 37.0
    }
    calibration {
      speed: 10.0
      acceleration: 1.18
      command: 39.0
    }
    calibration {
      speed: 10.0
      acceleration: 1.41
      command: 41.0
    }
    calibration {
      speed: 10.0
      acceleration: 1.65
      command: 43.0
    }
    calibration {
      speed: 10.0
      acceleration: 1.92
      command: 44.0
    }
    calibration {
      speed: 10.0
      acceleration: 2.0
      command: 45.0
    }
    calibration {
      speed: 10.0
      acceleration: 2.29
      command: 46.0
    }
    calibration {
      speed: 10.0
      acceleration: 2.45
      command: 47.0
    }
    calibration {
      speed: 10.0
      acceleration: 2.47
      command: 48.0
    }
    calibration {
      speed: 10.0
      acceleration: 2.75
      command: 49.0
    }
    calibration {
      speed: 10.0
      acceleration: 2.9
      command: 50.0
    }
    calibration {
      speed: 10.0
      acceleration: 3.47
      command: 55.0
    }
    calibration {
      speed: 10.0
      acceleration: 3.59
      command: 53.0
    }
  }
  enable_reverse_leadlag_compensation: false
}
trajectory_period: 0.1
chassis_period: 0.01
localization_period: 0.01
minimum_speed_resolution: 0.2
mpc_controller_conf {
  ts: 0.01
  cf: 155494.663
  cr: 155494.663
  mass_fl: 520
  mass_fr: 520
  mass_rl: 520
  mass_rr: 520
  eps: 0.01
  matrix_q: 3.0
  matrix_q: 0.0
  matrix_q: 35.0
  matrix_q: 0.0
  matrix_q: 50.0
  matrix_q: 10.0
  matrix_r: 3.25
  matrix_r: 1.0
  cutoff_freq: 10
  mean_filter_window_size: 10
  max_iteration: 150
  max_lateral_acceleration: 5.0
  standstill_acceleration: -0.3
  brake_minimum_action: 0.0
  throttle_minimum_action: 0.0
  lat_err_gain_scheduler {
    scheduler {
      speed: 2.5
      ratio: 1.0
    }
    scheduler {
      speed: 5.0
      ratio: 1.0
    }
    scheduler {
      speed: 10.0
      ratio: 0.4
    }
    scheduler {
      speed: 15.0
      ratio: 0.3
    }
    scheduler {
      speed: 20.0
      ratio: 0.2
    }
    scheduler {
      speed: 25.0
      ratio: 0.1
    }
  }
  heading_err_gain_scheduler {
    scheduler {
      speed: 2.5
      ratio: 1.0
    }
    scheduler {
      speed: 5.0
      ratio: 1.0
    }
    scheduler {
      speed: 10.0
      ratio: 0.5
    }
    scheduler {
      speed: 15.0
      ratio: 0.4
    }
    scheduler {
      speed: 20.0
      ratio: 0.35
    }
    scheduler {
      speed: 25.0
      ratio: 0.35
    }
  }
  steer_weight_gain_scheduler {
    scheduler {
      speed: 2.5
      ratio: 1.0
    }
    scheduler {
      speed: 5.0
      ratio: 1.0
    }
    scheduler {
      speed: 10.0
      ratio: 1.1
    }
    scheduler {
      speed: 15.0
      ratio: 1.1
    }
    scheduler {
      speed: 20.0
      ratio: 1.35
    }
    scheduler {
      speed: 25.0
      ratio: 1.55
    }
  }
  feedforwardterm_gain_scheduler {
    scheduler {
      speed: 2.5
      ratio: 0.7
    }
    scheduler {
      speed: 5.0
      ratio: 0.05
    }
    scheduler {
      speed: 10.0
      ratio: 0.0
    }
    scheduler {
      speed: 15.0
      ratio: 0.0
    }
    scheduler {
      speed: 20.0
      ratio: 0.0
    }
    scheduler {
      speed: 25.0
      ratio: 0.0
    }
  }
  enable_mpc_feedforward_compensation: false
}