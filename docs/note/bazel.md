## 如何对单个目标进行编译？
``` sh
bazel build //modules/tools/... //cyber/... 
```
可以对modules/tools目录所有目标和cyber目录的所有目标进行编译，但是会清空工作空间没覆盖到的编译后的文件。
