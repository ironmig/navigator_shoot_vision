cmake_minimum_required(VERSION 2.8.3)
project(navigator_shoot_vision)
 
 


find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  std_srvs
  message_generation 
  sensor_msgs
  cv_bridge
  image_transport
  geometry_msgs
)
add_message_files(
  FILES
  Symbol.msg
  Symbols.msg
)
add_service_files(
	FILES
	GetShape.srv
)

generate_messages(
	DEPENDENCIES 
	  std_msgs 
    geometry_msgs
)

catkin_package(
  CATKIN_DEPENDS 
	std_msgs 
    std_srvs
    message_runtime
)


include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(smart_shape_finder_server src/smart.cpp)
target_link_libraries(smart_shape_finder_server ${catkin_LIBRARIES})
add_dependencies(smart_shape_finder_server navigator_shoot_vision_generate_messages_cpp)
add_dependencies(smart_shape_finder_server navigator_shoot_vision_gencpp)


add_executable(vision src/main.cpp src/FrameProc.cpp src/ShapeFind.cpp src/DebugWindow.cpp src/ShapeDetector.cpp)
add_dependencies(vision navigator_shoot_vision_gencpp)
target_link_libraries(vision ${catkin_LIBRARIES})
find_package( OpenCV REQUIRED )
target_link_libraries(vision ${OpenCV_LIBS} )

