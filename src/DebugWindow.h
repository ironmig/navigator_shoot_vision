
#ifndef DEBUG_WINDOW_H
#define DEBUG_WINDOW_H

#define DO_DEBUG

#include <iostream>
#include <fstream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"


#include "ShapeFind.h"
#include "navigator_shoot_vision/Symbols.h"

using namespace cv;
class DebugWindow
{
	private:
		static Mat color_frame;
		static Mat red_frame;
		static Mat green_frame;
		static Mat blue_frame;
		static navigator_shoot_vision::Symbols symbols;

	public:
    static std::vector<navigator_shoot_vision::Symbols> allFoundSymbols;
		static void init();
		static void UpdateColor(Mat frame);
		static void UpdateRed(Mat frame);
		static void UpdateBlue(Mat frame);
		static void UpdateGreen(Mat frame);
		static void UpdateResults(navigator_shoot_vision::Symbols s);
		static void DrawAll();
};

#endif
