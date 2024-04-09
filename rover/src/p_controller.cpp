#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// bool isBlack(int val) {
//     return val < 20;
// }

// void actionFunc()

int main(int argc, char **argv) {
    std::cout << "Hey" << std::endl;

    ros::init(argc, argv, "my_planner_node");

    ros::NodeHandle nh_;
    image_transport::ImageTransport it_ (nh_);
    
    // image_transport::Subscriber image_sub_ = it_.subscribe("/camera/image_raw", 1, , imgCallBack);

    ros::spin();

    return 0;
}