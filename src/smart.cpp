#include "std_msgs/String.h"

#include "FrameProc.h"
#include "ShapeFind.h"
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>

#include <vector>

#include "DebugWindow.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

#include "navigator_shoot_vision/GetShape.h"
#include "navigator_shoot_vision/Symbols.h"



class ImageSearcher {
  private:
    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::ServiceServer service;
	navigator_shoot_vision::Symbols syms;

  public:
  	std::vector<navigator_shoot_vision::Symbols> frameSymbolHolder;
    ImageSearcher() {
        syms = navigator_shoot_vision::Symbols();
        sub = n.subscribe("found_shapes", 1000, &ImageSearcher::chatterCallback, this);
        service = n.advertiseService("GetShape", &ImageSearcher::test, this);
    }
   void chatterCallback(const navigator_shoot_vision::Symbols &symbols) {
        syms = symbols;
        frameSymbolHolder.push_back(symbols);
        // std::cout<<symbols.list.size()<<std::endl;
    }

   bool test(navigator_shoot_vision::GetShape::Request &req, navigator_shoot_vision::GetShape::Response &res) {
        //        for(int i = 0; i < syms.size(); i++) {
        for (int j = 0; j < syms.list.size(); j++) {
            if (req.Shape == syms.list[j].Shape && req.Color == syms.list[j].Color) {
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
