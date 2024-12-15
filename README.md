# line_follower_rover

## Установка

```
cd ~
mkdir -p catkin_ws/src
cd catkin_ws/src
git clone https://github.com/tenbullets/line_follower_rover.git
```
```
cd ~/catkin_ws/
rosdep update
rosdep install --from-paths src --ignore-src -r -y --rosdistro noetic
```
```
cd ~/catkin_ws
source /opt/ros/noetic/setup.bash
catkin build rover_pkg
```
```
sudo apt install ros-noetic-velocity-controllers
```

## Запуск

Каждый пак команд в новом терминале

Запускаем окружение с ровером:
```
source devel/setup.bash
roslaunch rover_pkg gazebo.launch
```
Запускаем motor_controller:
```
source devel/setup.bash
rosrun rover_pkg motor_controller
```
Запускаем move_controller:
```
source devel/setup.bash
rosrun rover_pkg move_controller
```