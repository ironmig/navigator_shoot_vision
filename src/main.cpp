#include "ros/ros.h"
#include "std_msgs/String.h"


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
		
	public:
		
	ShooterVision() : 
		fp(),
		blueFinder(navigator_shoot_vision::Symbol::BLUE),
		redFinder(navigator_shoot_vision::Symbol::RED),
		greenFinder(navigator_shoot_vision::Symbol::GREEN)
	{
		DebugWindow::init();
		symbols = navigator_shoot_vision::Symbols();
	}

	void run()
	{
		//Grab ros frame

		//Convert Ros frame to opencv

		//Process frame
		fp.Prepare();
		symbols.list.clear();
		
		//Find shapes in each color
		blueFinder.GetSymbols(fp.GetBlue(),&symbols);
		redFinder.GetSymbols(fp.GetRed(),&symbols);
		greenFinder.GetSymbols(fp.GetGreen(),&symbols);
		//Publish to ros
		DebugWindow::UpdateResults(symbols);
	}
};

int main()
{
	ShooterVision sv = ShooterVision();
	while (waitKey(50) == -1)
	{
		sv.run();
	}
	std::cout << "Key detected, exiting" << std::endl;
}
