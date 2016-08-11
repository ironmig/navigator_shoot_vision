//Grabs frame from ROS, erode/dilate, converts to HSV, produces Red Green Blue Black binary frames;
#ifndef FROM_PROC_H
#define FROM_PROC_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

#include "DebugWindow.h"

using namespace cv;

class FrameProc
{
	private:
		//const int height = 480;
		//const int width = 640;
		static const int blur_kernel_size;
		static const int erode_kernel_size;
		static const int dilate_kernel_size;
		Mat erode_element;
		Mat dilate_element;
		struct ColorThresh
		{
			Scalar low;
			Scalar high;
		};
		ColorThresh red;
		ColorThresh red2;
		ColorThresh blue;
		ColorThresh green;

		Mat rgb_frame;
		Mat hsv_frame;
		Mat binary_blue_frame;
		Mat binary_red_frame;
		Mat binary_green_frame;

		void ErodeDilate();
		void ConvertHSV();
		void ThresholdColors();
	public:
		FrameProc();
		void Prepare(Mat frame);
		Mat GetRed();
		Mat GetBlue();
		Mat GetGreen();
};

#endif
