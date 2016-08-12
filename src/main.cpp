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
		
		ros::NodeHandle nh;
		image_transport::ImageTransport image_transport;
		image_transport::Subscriber image_sub;
		cv_bridge::CvImagePtr cv_ptr;
		ros::Publisher<navigator_shoot_vision::Symbols> pub;
	public:
		
	ShooterVision() :
		nh(),
    image_transport(nh),
		fp(),
		blueFinder(navigator_shoot_vision::Symbol::BLUE),
		redFinder(navigator_shoot_vision::Symbol::RED),
		greenFinder(navigator_shoot_vision::Symbol::GREEN),
		pub("/shooter_vision",5)
	{
		DebugWindow::init();
    image_sub = image_transport.subscribe("/camera/image_color", 1, &ShooterVision::run, this);
    nh.advertise(pub);
	}

	//Callback for subscriber to camera feed
	void run(const sensor_msgs::ImageConstPtr& msg)
	{
		//Convert ros image to opencv Mat
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
		}

		cv::waitKey(3); //Small wait to slow down

		//Process frame
		fp.Prepare(cv_ptr->image);
		symbols.list.clear();
		
		//Find shapes in each color
		blueFinder.GetSymbols(fp.GetBlue(),&symbols);
		redFinder.GetSymbols(fp.GetRed(),&symbols);
		greenFinder.GetSymbols(fp.GetGreen(),&symbols);
		
		//Publish to ros
		pub.publish(symbols);
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
