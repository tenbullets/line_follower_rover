#include <iostream>
#include <string>
#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"

ros::Publisher leftWheelPub;
ros::Publisher rightWheelPub;

void commandsCallback(const std_msgs::String::ConstPtr& msg) {
  float leftSpeed = 0;
  float rightSpeed = 0;

  std::string command = msg -> data;

  if (command == "GO") {
    ROS_INFO("GO");
    leftSpeed = -0.8;
    rightSpeed = -0.8;
  } else if (command == "BACK") {
    ROS_INFO("BACK");
    leftSpeed = 0.16;
    rightSpeed = 0.16;
  } else if (command == "LEFT") {
    ROS_INFO("LEFT");
    leftSpeed = -0.74;
    rightSpeed = -0.28;
  } else if (command == "RIGHT") {
    ROS_INFO("RIGHT");
    leftSpeed = -0.28;
    rightSpeed = -0.74;
  } else if (command == "S_RIGHT") {
    ROS_INFO("S_RIGHT");
    leftSpeed = -0.08;
    rightSpeed = -0.85;
  } else if (command == "S_LEFT") {
    ROS_INFO("S_LEFT");
    leftSpeed = -0.85;
    rightSpeed = -0.08;
  } else {
    ROS_INFO("STOP");
    leftSpeed = 0.0;  
    rightSpeed = 0.0;
  }

  std_msgs::Float64 msgLeft, msgRight;
  msgLeft.data = leftSpeed;
  msgRight.data = rightSpeed;

  leftWheelPub.publish(msgLeft);
  rightWheelPub.publish(msgRight);
}

int main(int argc, char **argv) {
  ROS_INFO("READY");
  
  ros::init(argc, argv, "motorController");
  ros::NodeHandle node;

  ros::Subscriber commandSub = node.subscribe("motor_commands", 1000, commandsCallback);

  leftWheelPub = node.advertise<std_msgs::Float64>("/left_wheel_controller/command", 1500);
  rightWheelPub = node.advertise<std_msgs::Float64>("/right_wheel_controller/command", 1500);

  ros::spin();
  return 0;
}
