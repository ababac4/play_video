Qt 5.12.11 x86 mingw32编译器

./cryptopp/ 就是常用的include 路径

该库的使用不用添加动态库的引用库

调试程序使用 debug版本dll
发布程序使用 Release版本dll

release版本dll 无法输出 调试信息

为了开发方便可以放入qt的库环境中 ,例如C:\Qt\Qt5.12.11\5.12.11\mingw73_32\bin