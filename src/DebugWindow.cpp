#include "DebugWindow.h"


Mat DebugWindow::color_frame = Mat();
Mat  DebugWindow::red_frame = Mat();
Mat  DebugWindow::green_frame = Mat();
Mat  DebugWindow::blue_frame = Mat();
std::vector<ShapeFind::Result>  DebugWindow::results = std::vector<ShapeFind::Result>();

void DebugWindow::init()
{
	color_frame = Mat();
	red_frame = Mat();
	blue_frame = Mat();
	green_frame = Mat();
	results = std::vector<ShapeFind::Result>();
	namedWindow("color",CV_WINDOW_AUTOSIZE);
	namedWindow("red",CV_WINDOW_AUTOSIZE);
	namedWindow("blue",CV_WINDOW_AUTOSIZE);
	namedWindow("green",CV_WINDOW_AUTOSIZE);
	std::cout << "Running GUI Debug mode" << std::endl;
}

void DebugWindow::UpdateColor(Mat frame)
{
	color_frame = frame;
	imshow("color",color_frame);
}
void DebugWindow::UpdateRed(Mat frame)
{
	red_frame = frame;
	imshow("red",red_frame);
}
void DebugWindow::UpdateBlue(Mat frame)
{
	blue_frame = frame;
	imshow("blue",blue_frame);
}
void DebugWindow::UpdateGreen(Mat frame)
{
	green_frame = frame;
	imshow("green",green_frame);
}
void DebugWindow::UpdateResults(std::vector<ShapeFind::Result> rs)
{
	results = rs;
}
