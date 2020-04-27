## 如何检测各个模块的工作状态
通过HMI发布的/apollo/hmi/status消息知道目前处于哪个模式，有process_monitor中UpdateStatus函数来匹配启动模块命令和目前已经运行的进程字段是否匹配，若字段完全匹配则模块在运行状态。
```cpp
void ProcessMonitor::UpdateStatus(
    const std::vector<std::string>& running_processes,
    const apollo::dreamview::ProcessMonitorConfig& config,
    ComponentStatus* status) {
  status->clear_status();
  for (const std::string& command : running_processes) {
    bool all_keywords_matched = true;
    for (const std::string& keyword : config.command_keywords()) {
      if (command.find(keyword) == std::string::npos) {
        all_keywords_matched = false;
        break;
      }
    }
    if (all_keywords_matched) {
      // Process command keywords are all matched. The process is running.
      SummaryMonitor::EscalateStatus(ComponentStatus::OK, command, status);
      return;
    }
  }
  SummaryMonitor::EscalateStatus(ComponentStatus::FATAL, "not match", status);
}
```