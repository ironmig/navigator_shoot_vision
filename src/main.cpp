#include "std_msgs/String.h"

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include "FrameProc.h"
#include "ShapeFind.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "DebugWindow.h"

#include "navigator_shoot_vision/Symbols.h"

using namespace cv;

class ShooterVision
{
	private:
		//ros frame thing
		navigator_shoot_vision::Symbols symbols;
		FrameProc fp;
		ShapeFind blueFinder;
		ShapeFind redFinder;
		ShapeFind greenFinder;
		
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;
	public:
		
	ShooterVision() : 
    it_(nh_),
		fp(),
		blueFinder(navigator_shoot_vision::Symbol::BLUE),
		redFinder(navigator_shoot_vision::Symbol::RED),
		greenFinder(navigator_shoot_vision::Symbol::GREEN)
	{
		DebugWindow::init();
    image_sub_ = it_.subscribe("/camera/image_color", 1, &ShooterVision::run, this);
		symbols = navigator_shoot_vision::Symbols();
	}

	void run(const sensor_msgs::ImageConstPtr& msg)
	{
		//Grab ros frame
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
    std::cout << "Loop. Rows=" << cv_ptr->image.rows << std::endl;
		//Convert Ros frame to opencv
     cv::waitKey(3);
		//Process frame
		fp.Prepare(cv_ptr->image);
		symbols.list.clear();
		
		//Find shapes in each color
		blueFinder.GetSymbols(fp.GetBlue(),&symbols);
		redFinder.GetSymbols(fp.GetRed(),&symbols);
		greenFinder.GetSymbols(fp.GetGreen(),&symbols);
		//Publish to ros
		DebugWindow::UpdateResults(symbols);
	}
};

int main(int argc,char ** argv)
{
  ros::init(argc, argv, "image_converter");
	ShooterVision sv = ShooterVision();
	while (waitKey(50) == -1 && ros::ok())
	{
    ros::spin();
		//sv.run();
	}
	std::cout << "Key detected, exiting" << std::endl;
}
