#include "std_msgs/String.h"

#include "FrameProc.h"
#include "ShapeFind.h"
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>

#include "DebugWindow.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

#include "navigator_shoot_vision/GetShape.h"
#include "navigator_shoot_vision/Symbols.h"

  	   navigator_shoot_vision::Symbols syms;
class ImageSearcher {
  private:

    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::ServiceServer service;

  public:

    ImageSearcher() {
    	syms = navigator_shoot_vision::Symbols();
        sub = n.subscribe("found_shapes", 1000, chatterCallback);
        service = n.advertiseService("GetShape", test);
    }
   static void chatterCallback(const navigator_shoot_vision::Symbols &symbols) { 
   syms = symbols;
//std::cout<<symbols.list.size()<<std::endl;
   }

  static  bool test(navigator_shoot_vision::GetShape::Request &req, navigator_shoot_vision::GetShape::Response &res) {
//        for(int i = 0; i < syms.size(); i++) {
        	for(int j =0; j < syms.list.size(); j++) {
        		if(req.Shape == syms.list[j].Shape && req.Color == syms.list[j].Color) {
        			res.CenterX = syms.list[j].CenterX;
        			res.CenterY = syms.list[j].CenterY;
        			return true;
        		}
   			 }
   			    			 return false;
   			 }

//   			 }
};


int main(int argc, char **argv) {
    ros::init(argc, argv, "smart_shape_finder_server");
	ImageSearcher imageSearcher;
    ros::spin();
    return 0;
}
