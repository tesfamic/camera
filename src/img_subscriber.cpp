#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

//cv::VideoWriter video("/home/a3/Videos/calib.avi",cv::VideoWriter::fourcc('M','J','P','G'),10, cv::Size(2048,1536));

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  cv::Mat img_received;
  try{
      img_received = cv_bridge::toCvShare(msg, "bgr8")->image;
      //video.write(img_received);
      cv::imshow("Received image",img_received );
      cv::waitKey(1);
  }catch (cv_bridge::Exception& e){
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;
  //   cv::namedWindow("view");
  //   cv::startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("camera/image", 1, imageCallback);
  //while(nh.ok()){
  ros::spin();
  //}
  
  //cv::destroyWindow("view");
  std::cout<<"\n Subscriber closed."<<std::endl;

  return 0;
}