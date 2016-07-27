#include "ros/ros.h"
#include "std_msgs/String.h"


#include "FrameProc.h"
#include "ShapeFind.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;

class ShooterVision
{
	private:
		//ros frame thing
		std::vector <ShapeFind::Result> shapes;
		ShapeFind bluefinder;
		ShapeFind redFinder;
		ShapeFind greenFinder;
		ShapeFind blackFinder;
	public:
		
	ShooterVision()
	{
		//init ShapeFind's, frames
	}

	void run()
	{
		//Grab ros frame

		//Convert Ros frame to opencv

		//Process frame
		FrameProc::Prepare(frame);

		//Find shapes in each color
		shapes.insert ( blueFinder.GetShapes(FrameProc::GetBlue()) )
		//do for other colors

		//Publish to ros
	}
};
