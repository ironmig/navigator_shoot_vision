#include "std_msgs/String.h"

#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>
#include "FrameProc.h"
#include "ShapeFind.h"

#include <vector>

#include "DebugWindow.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

#include "navigator_shoot_vision/GetShape.h"
#include "navigator_shoot_vision/Symbols.h"
#include "std_srvs/SetBool.h"

class ImageSearcher {
 private:
  ros::NodeHandle n;
  ros::Subscriber sub;
  ros::ServiceServer service;
  navigator_shoot_vision::Symbols syms;                            // latest frame
  std::vector<navigator_shoot_vision::Symbols> frameSymbolHolder;  // Previous frames
  std::vector<navigator_shoot_vision::Symbol> possibleSymbols;
  std::string possibleShapes[3] = {navigator_shoot_vision::Symbol::CROSS, navigator_shoot_vision::Symbol::TRIANGLE,
                                   navigator_shoot_vision::Symbol::CIRCLE};
  std::string possibleColors[3] = {navigator_shoot_vision::Symbol::RED, navigator_shoot_vision::Symbol::BLUE, navigator_shoot_vision::Symbol::GREEN};
  ros::ServiceServer serviceCommand;
  int counter[3 * 3];
  int frames;
  bool active;
  int lastCallFrame;

 public:
  ImageSearcher() {
    frames = 0;
    lastCallFrame = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        navigator_shoot_vision::Symbol holdSym;
        holdSym.Shape = possibleShapes[i];
        holdSym.Color = possibleColors[j];
        holdSym.CenterX = 0;
        holdSym.CenterY = 0;
        possibleSymbols.push_back(holdSym);
        counter[i * j] = 0;
      }
    }

    syms = navigator_shoot_vision::Symbols();
    sub = n.subscribe("/image_converter/found_shapes", 1000, &ImageSearcher::chatterCallback, this);
    serviceCommand = n.advertiseService("/shooter_vision/runsmart", &ImageSearcher::getShapeController, this);
    service = n.advertiseService("GetShape", &ImageSearcher::getShape, this);
    active = false;
  }

  float mean(int val, int size) { return val / size; }
  void shapeChecker(const navigator_shoot_vision::Symbols &symbols) {
    if (!active) return;
    for (int i = 0; i < symbols.list.size(); i++) {
      for (int k = 0; k < possibleSymbols.size(); k++) {
        if (symbols.list[i].Shape == possibleSymbols[k].Shape && symbols.list[i].Color == possibleSymbols[k].Color) {
          if (frames < 10) {
            possibleSymbols[k].CenterX += symbols.list[i].CenterX;
            possibleSymbols[k].CenterY += symbols.list[i].CenterY;
            counter[k]++;

          } else if (std::abs(symbols.list[i].CenterX - mean(possibleSymbols[k].CenterX, counter[k])) < 100 &&
                     std::abs(symbols.list[i].CenterY - mean(possibleSymbols[k].CenterY, counter[k])) < 100) {
            possibleSymbols[k].CenterX += symbols.list[i].CenterX;
            possibleSymbols[k].CenterY += symbols.list[i].CenterY;
            counter[k]++;
          }
        }
      }
    }
  }

  void chatterCallback(const navigator_shoot_vision::Symbols &symbols) {
    if (!active) return;
    frames++;
    syms = symbols;
    frameSymbolHolder.push_back(symbols);
    shapeChecker(symbols);
  }

  bool getShape(navigator_shoot_vision::GetShape::Request &req, navigator_shoot_vision::GetShape::Response &res) {
    if (!active) return false;
    if (frames == 0) {
    }
    if (frames < 10) {
      std::cout << "Too small of sample frames" << frames << std::endl;
      return false;
    }
    for (int j = 0; j < syms.list.size(); j++) {
      for (int i = 0; i < possibleSymbols.size(); i++) {
        if (req.Shape == possibleSymbols[i].Shape && req.Color == possibleSymbols[i].Color && syms.list[j].Shape == req.Shape &&
            syms.list[j].Color == req.Color && counter[i] > 10) {
          if (std::abs(syms.list[j].CenterX - mean(possibleSymbols[i].CenterX, counter[i])) < 100 &&
              std::abs(syms.list[j].CenterY - mean(possibleSymbols[i].CenterY, counter[i])) < 100) {
            res.symbol = syms.list[j];
            lastCallFrame = frames;

            return true;
          }
        }
      }
    }
    return false;
  }

  bool getShapeController(std_srvs::SetBool::Request &req, std_srvs::SetBool::Response &res) {
    std_srvs::SetBool msg;
    msg.request.data = req.data;
    active = req.data;

    ros::service::call("/shooter_vision/runvision", msg);
    std::cout << "Setting active to " << active << std::endl;
    res.success = true;
    return true;
  }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "smart_shape_finder_server");
  ImageSearcher imageSearcher;
  ros::spin();
  return 0;
}
