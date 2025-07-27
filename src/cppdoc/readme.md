## CppDoc 模块

### 介绍

CppDoc 可以用来为您的hpp和cpp文件生成对应的文档。同时支持本地化模块 `i18n/i18n.hpp`。

### 用法

在要生成文档的文件内的函数声明的上一行添加注释，格式为：

```cpp
//$[函数描述] #1[第1个参数描述] #2[第2个参数描述] ... #n
```

如果没有参数就不用写后面的内容。

同时为了避免CppDoc抽风，还可以用 `//*` 和 `//**` 分别作为跳过区域的开始标记和结束标记，CppDoc不会尝试生成在跳过区域中的代码。

最后在 `server_main.cpp` 中调用 `CppDoc().gendoc_auto([文件地址])` 即可，别忘了添加头文件 `#include "cppdoc/cppdoc.hpp"`。也可以调用 `CppDoc().gendoc([文件地址],[i18n])` 获得本地化后的文档。

### 更多

更多细节请看 `cppdoc/cppdoc.hpp.md` 和本模块的头文件和源文件。注意 `cppdoc/cppdoc.cpp` 中 `skipon()` 和 `skipoff()` 的报错是误报，可以正常编译通过。