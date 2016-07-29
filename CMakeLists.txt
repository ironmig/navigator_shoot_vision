cmake_minimum_required(VERSION 2.8.3)
project(navigator_shoot_vision)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(vision src/main.cpp src/FrameProc.cpp src/ShapeFind.cpp)
target_link_libraries(vision ${catkin_LIBRARIES})
find_package( OpenCV REQUIRED )
target_link_libraries(vision ${OpenCV_LIBS} )
