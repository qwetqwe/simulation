## =delete 的用法
  用=delete修饰的函数将不能被调用，是禁止c++自动产生默认构造函数的方法，比如：
```cpp 
class Timer {
 public:
  Timer() : start_time_(0), end_time_(0) {}

  // no-thread safe.
  void Start();

  // return the elapsed time,
  // also output msg and time in glog.
  // automatically start a new timer.
  // no-thread safe.
  uint64_t End(const std::string &msg);

  Timer(const Timer &) = delete;
  Timer &operator=(const Timer &) = delete;

 private:
  // in ms.
  uint64_t start_time_;
  uint64_t end_time_;
};
```
Timer 类不能被拷贝，于是对Timer的构造函数和=符号均用delete禁用了