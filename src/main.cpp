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
		FrameProc fp;
		ShapeFind blueFinder;
		ShapeFind redFinder;
		ShapeFind greenFinder;
		
	public:
		
	ShooterVision() : 
		fp(),
		blueFinder(ShapeFind::BLUE),
		redFinder(ShapeFind::RED),
		greenFinder(ShapeFind::GREEN)
	{

	}

	void run()
	{
		//Grab ros frame

		//Convert Ros frame to opencv

		//Process frame
		fp.Prepare();

		shapes.clear();
		//Find shapes in each color
		blueFinder.GetShapes(fp.GetBlue(),shapes);
		redFinder.GetShapes(fp.GetRed(),shapes);
		greenFinder.GetShapes(fp.GetGreen(),shapes);
		//Publish to ros
	}
};

int main()
{
	ShooterVision sv = ShooterVision();
	while (1)
	{
		sv.run();
	}
}
