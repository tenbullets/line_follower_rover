#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <std_msgs/String.h>

cv_bridge::CvImagePtr cv_ptr;
ros::Publisher command_pub;
std::string command = "STOP";

char const * toChar(int num) {
  std::string s = std::to_string(num);
  char const * res = s.c_str(); 
  return res;
}

bool is_black(int val) {
  return val < 39;
}

bool is_white(int val) {
  return val > 147;
}

void plan(int left, int right) {
  ROS_INFO("%d %d", left, right);

  if (is_black(left) && is_black(right)) command = "GO";
  
  if (is_black(left) && !is_black(right)) {
    command = "LEFT";
    if (is_white(right)) command = "S_LEFT";
  }
  
  if (!is_black(left) && is_black(right)) {
    command = "RIGHT";
    if (is_white(left)) command = "S_RIGHT";
  }
    
  if(!is_black(left) && !is_black(right)) command = "BACK";
  
  std_msgs::String msg;
  msg.data = command;
  command_pub.publish(msg);
}

void imgCallBack(const sensor_msgs::ImageConstPtr& data) {
  
  try {
    cv_ptr = cv_bridge::toCvCopy(data, sensor_msgs::image_encodings::BGR8);
  } catch (cv_bridge::Exception& e) {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }

  cv::Mat bw_img;
  cv::cvtColor(cv_ptr->image, bw_img, cv::COLOR_BGR2GRAY);

  int lData = bw_img.at<uchar>(390, 265);
  int rData = bw_img.at<uchar>(390, 535);

  plan(lData, rData);
  
  // cv::line(bw_img, cv::Point(265, 450), cv::Point(535, 450), cv::Scalar(255, 255, 255), 15);

  cv::circle(bw_img, cv::Point(265, 390), 5, cv::Scalar(255, 255, 255), 10);
  cv::circle(bw_img, cv::Point(535, 390), 5, cv::Scalar(255, 255, 255), 10);

  cv::putText(bw_img,
            toChar(lData),
            cv::Point(40, 40),
            cv::FONT_HERSHEY_DUPLEX,
            0.6,
            CV_RGB(255, 255, 255),
            2);

  cv::putText(bw_img,
            toChar(rData),
            cv::Point(90, 40),
            cv::FONT_HERSHEY_DUPLEX,
            0.6,
            CV_RGB(255, 255, 255),
            2);

  cv::putText(bw_img,
            command.c_str(),
            cv::Point(40, 65),
            cv::FONT_HERSHEY_DUPLEX,
            0.6,
            CV_RGB(255, 255, 255),
            2);      

  cv::imshow("camera", bw_img);
  cv::waitKey(3);
}

int main(int argc, char** argv) {
  ROS_INFO("LAUNCH");

  ros::init(argc, argv, "planner_node");
  ros::NodeHandle nh;
  command_pub = nh.advertise<std_msgs::String>("motor_commands", 1);
  ros::Subscriber img_sub = nh.subscribe("/camera/image_raw", 1, imgCallBack);
  ros::spin();

  return 0;
}



