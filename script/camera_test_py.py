#!/usr/bin/env python
import rospy
import cv2
import numpy as np
import TIS
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeErrorc

def img_publisher():
    rospy.init_node('camera_node',anonymous=True)
    image_publisher = rospy.Publisher("/image",Image,queue_size=1)
    bridge = CvBridge()
    rate = rospy.Rate(40)

    Tis = TIS.TIS("17710016", 2048, 1536, 36, True)
    # the camera with serial number 10710286 uses a 640x480 video format at 30 fps and the image is converted to
    # RGBx, which is similar to RGB32.

    Tis.Start_pipeline()  # Start the pipeline so the camera streams

    # print('Press Esc to stop')
    # lastkey = 0
    # cv2.namedWindow('Window')  # Create an OpenCV output window
    # kernel = np.ones((5, 5), np.uint8)  # Create a Kernel for OpenCV erode function

    #while lastkey != 27:
    num_of_frames = 0
    while not rospy.is_shutdown():
        if Tis.Snap_image(1) is True:  # Snap an image with one second timeout
            image = Tis.Get_image()  # Get the image. It is a numpy array
            image = cv2.cvtColor(image,cv2.COLOR_BGR2RGB)
            #image = cv2.erode(image, kernel, iterations=5)  # Example OpenCV image processing
            num_of_frames += 1

            image_publisher.publish(bridge.cv2_to_imgmsg(image,"bgr8"))

            # cv2.imshow('Window', image)  # Display the result
            # cv2.waitKey(1)
        #lastkey = cv2.waitKey(10)
        print("frame #",num_of_frames)

    # Stop the pipeline and clean up
    Tis.Stop_pipeline()
    # cv2.destroyAllWindows()
    print('Program ended')

if __name__ == '__main__':
    try:
        img_publisher()
    except rospy.ROSInterruptException:
        pass