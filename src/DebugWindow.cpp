#include "DebugWindow.h"

DebugWindow::init()
{
	namedWindow("color",CV_WINDOW_AUTOSIZE);
	namedWindow("red",CV_WINDOW_AUTOSIZE);
	namedWindow("blue",CV_WINDOW_AUTOSIZE);
	namedWindow("green",CV_WINDOW_AUTOSIZE);
}
