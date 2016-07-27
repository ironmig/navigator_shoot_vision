//Grabs frame from ROS, erode/dilate, converts to HSV, produces Red Green Blue Black binary frames;

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
class FrameProc
{
	private:
		const int height = 480;
		const int width = 640;
		const int blur_kernel_size = 3;
		const int erode_kernel_size = 3;
		const int dilate_kernel_size = 3;
		typedef struct ColorThresh
		{
			Scalar low;
			Scalar high;
		}
		ColorThresh red;
		ColorThresh blue;
		ColorThresh green;
		VideoCapture cap;

		Mat rgb_frame;
		Mat hsv_frame;
		Mat binary_blue_frame;
		Mat binary_red_frame;
		Mat binary_green_frame;
		Mat binary_black_frame;

		static void GetFrame();
		static void ErodeDilate();
		static void ConvertHSV();
		static void ThresholdColors();
	public:
		static void Prepare(Mat frame);
		static Mat GetRed();
		static Mat GetBlue();
		static Mat GetGreen();
		static Mat GetBlack();
}
