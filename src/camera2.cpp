
#include <ros/ros.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "tcamimage.h"
//#include "opencv2/opencv.hpp"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace gsttcam;

///////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    ros::init(argc, argv, "camera2_node");
    ros::NodeHandle nh;
    
    image_transport::ImageTransport it(nh);
    image_transport::Publisher image_pub;     
    cv_bridge::CvImagePtr cv_ptr;

    image_pub = it.advertise("/camera2/image", 5);
    ros::Rate loop_rate(30);

    gst_init(&argc, &argv);

    cv::Mat OpenCVImage;// = cv::Mat();
    // Initialize our TcamCamera object "cam" with the serial number
    // of the camera, which is to be used in this program.
    TcamImage cam("17710016");//"17710016");//"27710206");
    //TcamCamera cam("00001234");
    // Set a color video format, resolution and frame rate
    cam.set_capture_format("BGRx",FrameSize{2048,1536}, FrameRate{30,1});//FrameSize{1920,1080}, FrameRate{36,1});
    // Comment following line, if no live video display is wanted.
    //cam.enable_video_display(gst_element_factory_make("ximagesink", NULL));
    auto expos = cam.get_property("Exposure Auto");
    // std::cout<<" exposure auto: "<<cam.get_property("Exposure Auto")<<"\n";
    // Start the camera
    cam.start();

    sleep(1);
    //printf("Start Snap\n");
    // Snap an Image with 60 ms timeout. Should be set accordingly to the
    // frame rate.
    int num_of_frames = 0;
    sensor_msgs::ImagePtr img_msg;
    cv::Mat image;
    while(nh.ok()){    
        if( cam.snapImage(1000) ) //1000 ms timout
        {
            // std::cout<<" exposure auto: "<<expos<<"\n";
            // On succes do something with the image data. Here we create
            // a cv::Mat and save the image
            //std::cout<<" byter per pix: "<<cam.getBytesPerPixel()<<std::endl;
            OpenCVImage.create(cam.getHeight(),cam.getWidth(),CV_8UC(cam.getBytesPerPixel()));
            memcpy( OpenCVImage.data, cam.getImageData(), cam.getImageDataSize());
            //cv::imwrite("test.jpg",OpenCVImage);
            cv::cvtColor(OpenCVImage,image,cv::COLOR_BGR2RGB);
            img_msg = cv_bridge::CvImage(std_msgs::Header(), "rgb8", image).toImageMsg();
            num_of_frames ++;
            //publish image
            image_pub.publish(img_msg);
            // cv::imshow("image",image);
            // cv::waitKey(1);
        }
        else
        {
            printf("Timeout at snapImage()\n");
        }
        std::cout<<"camera2-frame #:"<<num_of_frames<<std::endl;
        ros::spinOnce();
        loop_rate.sleep();
    }
    // printf("Press enter key to end program.");
    // // Simple implementation of "getch()", wait for enter key.
    // char dummyvalue[10];
    // scanf("%c",dummyvalue);

    cam.stop();
    std::cout<<"\n Image publisher closed."<<std::endl;
    return 0;
}