cmake_minimum_required(VERSION 3.0.2)
project(rover_pkg)

find_package(catkin REQUIRED COMPONENTS
        roscpp
        sensor_msgs
        std_msgs
        cv_bridge
        image_transport)

catkin_package()
find_package(catkin REQUIRED COMPONENTS
        ${PKG_DEPS}
        ${OpenCV_INCLUDE_DIRS})

find_package(OpenCV 4.2.0 REQUIRED)

include_directories(include ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

add_executable(motor_controller src/motor_controller.cpp)
target_link_libraries(motor_controller ${catkin_LIBRARIES})

add_executable(p_controller src/p_controller.cpp)
target_link_libraries(p_controller ${catkin_LIBRARIES})

