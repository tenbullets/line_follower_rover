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

  if(command == "GO") 
  {
    ROS_INFO("GO");
    leftSpeed = -0.8;
    rightSpeed = -0.8;
  } else if(command == "BACK") 
  {
    std::cout << "BACK" << std::endl;
    leftSpeed = 0.5;
    rightSpeed = 0.5;
  } else if(command == "LEFT") 
  {
    std::cout << "LEFT" << std::endl;
    leftSpeed = -1.0;
    rightSpeed = -0.5;
  } else if(command == "RIGHT") 
  {
    std::cout << "RIGHT" << std::endl;
    leftSpeed = -0.5;
    rightSpeed = -1.0;
  } else 
  {
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
  std::cout << "work" << std::endl;
  
  ros::init(argc, argv, "motorController");
  ros::NodeHandle node;

  ros::Subscriber commandSub = node.subscribe("motor_commands", 1000, commandsCallback);

  leftWheelPub = node.advertise<std_msgs::Float64>("/left_wheel_controller/command", 1500);
  rightWheelPub = node.advertise<std_msgs::Float64>("/right_wheel_controller/command", 1500);

  ros::spin();
  return 0;
}
