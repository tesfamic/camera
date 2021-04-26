cmake_minimum_required(VERSION 2.8.3)
project(camera)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(PkgConfig REQUIRED)
find_package(OpenCV REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  rospy
  sensor_msgs
  std_msgs
)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)

pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0 gstreamer-app-1.0 gstreamer-video-1.0)
pkg_check_modules(TCAMLIB tcam)

include_directories( ${CMAKE_CURRENT_BINARY_DIR}  ${GSTREAMER_INCLUDE_DIRS} ${TCAM_INCLUDE_DIRS}  ${OpenCV_INCLUDE_DIRS} )

add_definitions(${GSTREAMER_CFLAGS_OTHER})  

catkin_package(
  INCLUDE_DIRS include
  #  LIBRARIES camera
  CATKIN_DEPENDS cv_bridge image_transport roscpp rospy sensor_msgs std_msgs
  DEPENDS OpenCV
)

include_directories(
  include
  include/camera
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  /usr/include/gstreamer-1.0
  /usr/include/glib-2.0
)

# add_executable(camera1 src/camera1.cpp src/tcamimage.cpp src/tcamcamera.cpp)
# add_executable(camera2 src/camera2.cpp src/tcamimage.cpp src/tcamcamera.cpp)
# add_executable(camera3 src/camera3.cpp src/tcamimage.cpp src/tcamcamera.cpp)
# add_executable(camera4 src/camera4.cpp src/tcamimage.cpp src/tcamcamera.cpp)

# add_executable(img_subscriber src/img_subscriber.cpp)

# target_link_libraries(camera1 ${OpenCV_LIBRARIES} ${catkin_LIBRARIES} ${TCAMLIB_LIBRARIES} ${GSTREAMER_LIBRARIES}  ${OpenCV_LIBS})
# target_link_libraries(camera2 ${OpenCV_LIBRARIES} ${catkin_LIBRARIES} ${TCAMLIB_LIBRARIES} ${GSTREAMER_LIBRARIES}  ${OpenCV_LIBS})
# target_link_libraries(camera3 ${OpenCV_LIBRARIES} ${catkin_LIBRARIES} ${TCAMLIB_LIBRARIES} ${GSTREAMER_LIBRARIES}  ${OpenCV_LIBS})
# target_link_libraries(camera4 ${OpenCV_LIBRARIES} ${catkin_LIBRARIES} ${TCAMLIB_LIBRARIES} ${GSTREAMER_LIBRARIES}  ${OpenCV_LIBS})


# target_link_libraries(img_subscriber ${OpenCV_LIBRARIES} ${catkin_LIBRARIES} ${TCAMLIB_LIBRARIES} ${GSTREAMER_LIBRARIES}  ${OpenCV_LIBS})



