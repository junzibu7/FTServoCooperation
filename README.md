
# 舵机调度规划

## 主要文件说明

可以根据具体需求选择`ServoControl.launch.py`文件中的节点进行启动。节点，启动！

对主要可执行文件的介绍：
- `Single_Servogp_Control.cpp`：单个舵机的控制程序。主要功能包含调用`singleServoControl.cpp`库等。
- `Multi_Servogp_Control.cpp`：多个舵机的协同控制。主要功能包含调用`multiServoControl.cpp`库等。
- `base2servogroup.cpp`：构建base到servogroup的tf树。主要功能包含以tf树形式发布base到4个servogroup的向量等。
- `Target_Trajectory_Simulation.cpp`：无人机的轨迹模拟。主要功能包含以tf树形式发布多种无人机的预设轨迹以便利仿真实验等。

对主要库函数的介绍：
- `singleServoControl.cpp`：单个舵机的控制程序。主要功能包含：
  - 监听目标相对于相机的转换向量，得到其在图像坐标系的位置；
  - 发布目标的相关信息用以舵机协同控制；
  - 广播servogroupxx到camx的tf变换；
  - 订阅目标的控制输入，并控制舵机转到指定位置。
- `multiServoControl.cpp`
  - 订阅目标的相关信息；
  - 计算得到控制相关的增益矩阵和控制输入；
  - 发布目标的控制输入。

## 飞特舵机控制库

### 使用前初始化（待更新，可使用https://gitee.com/hx2020hx/ftservo-control）
- 对于一个飞特舵机控制板，其上会串联多个飞特舵机，在使用前先需要单独连接每个舵机，并且进行`id`的更新，修改`initial.launch`中的`id`的值，以符合你规定的id序列，注意，id尽量按照1，2，3，4，...进行标记，并且将当前的角度定义为初始角度。
- `initial.launch`的作用：
  1. 将舵机的当前角度设置为180deg，此角度为飞特舵机的基准角度
  2. 将初始的舵机编号设置为`modified_id`，注意，如果原来的舵机编号不是1，则这个initialize不会起作用，若如此，请修改`initialize.cpp`中`_servo.rename(1, modified_id);`的`1`至当前舵机的编号。
  
```
roslaunch ftservocontrol initial.launch
```

### 快速使用
1. 创建工作空间
```
cd ~
mkdir servo_ws
cd servo_ws
mkdir src
cd src
catkin_init_workspace
```
2. 将这个代码clone到你的工作空间src下
```
git clone https://gitee.com/hx2020hx/ftservo-control.git
```
3. 回到你的工作空间下，编译
```
cd ..
catkin_make -j1
source devel/setup.bash
```
4. 初始化舵机，注意此时只能连接一个*未初始化*的舵机
```
roslaunch ftservocontrol initial.launch
```
5. 测试舵机转动，注意此时只能连接刚刚初始化的舵机
新开一个终端
```
roscore
```
再在原来的终端里运行
```
rosrun ftservocontrol WritePos
```
6. 如果报错permission denied，检查是否有/dev/ttyUSB0这个接口
```
ls /dev/tty*
```
如果有，则运行
```
sudo chmod 777 /dev/ttyUSB0
```
如果没有则将initize.launch中的port改为你能找到的/dev/ttyUSBX
之后重新运行
```
roslaunch ftservocontrol initial.launch
```
### 使用方法
- 在项目的Cmakelist.txt中添加这个库`ftservocontrol`，并且`include`头文件
```
#include <ftservocontrol/FEETECHservo.h>
```
- 直接使用类ftservo，各个函数的功能可以看注释，提供了类似读取，写入，初始化等等的函数。
- 具体的example可见WritePos.cpp之中

