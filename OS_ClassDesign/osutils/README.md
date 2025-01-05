# osutils

#### 介绍
此项目为[pintos](http://gitee.com/ctguhzy/pintos)项目的附加项目，提供了pintos工具链(Tool Chain)的源码包及编译脚本；另外此项目中还包含bochs虚拟机源码包及其编译脚本。
按下述步骤操作可以获得pintos项目所需的工具链和虚拟机。你也可以直接从[OSToolChain](http://gitee.com/ctguhzy/OSToolChain)中获得以在Ubuntu 16.04和Ubuntu 18.04中直接运行的工具链程序集和bochs虚拟机。

#### 编译安装

1. 安装依赖包

sudo apt-get install libncurses-dev

sudo apt-get install libx11-dev

sudo apt install libxrandr-dev

2. 运行工具链(Tool Chain)编译脚本编译安装工具链(需装whoami换成你的用户名)

./toolchain-build.sh --prefix /home/`whoami`/OSToolChain /home/`whoami`/OSToolChain

3. 编译安装Bochs虚拟机

./bochs-2.6.2-build.sh /home/`whoami`/OSToolChain


#### 相关项目

* [pintos](http://gitee.com/ctguhzy/pintos) 一个教学用的32位操作系统

* [osutils](http://gitee.com/ctguhzy/osutils) pintos系统所需的工具链源码包及编译脚本

* [OSToolChain](http://gitee.com/ctguhzy/OSToolChain) 已编译好可直接在Ubuntu 16.04和Ubuntu 18.04下使用的工具链程序集和bochs虚拟机程序 

