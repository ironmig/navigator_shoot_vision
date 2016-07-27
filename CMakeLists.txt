cmake_minimum_required(VERSION 2.8.3)
project(navigator_shoot_vision)

find_package(catkin REQUIRED COMPONENTS
  std_msgs
)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(vision src/main.cpp)
target_link_libraries(vision ${catkin_LIBRARIES})
add_dependencies(vision src/main_cpp)

