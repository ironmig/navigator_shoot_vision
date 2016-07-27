#include "ros/ros.h"
#include "std_msgs/String.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;

const int height = 480;
const int width = 640;
const int blur_kernel_size = 3;
const int erode_kernel_size = 3;
const int dilate_kernel_size = 3;

int main(int argc, char **argv)
{
	//Ros Stuff
	ros::init(argc, argv, "talker");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<std_msgs::String>("shooter_control", 1000);
	std_msgs::String msg;
	
	VideoCapture cap(1);
	if (!cap.isOpened())
	{
		std::cerr << "Camera opening error" << std::endl;
		return -1;
	}
	cap.set(CAP_PROP_FRAME_WIDTH,width);
	cap.set(CAP_PROP_FRAME_HEIGHT, height);
	
	//Stores images
	Mat frame (height,width,CV_8UC3);
	Mat hsv_frame (height,width,CV_8UC3);
	Mat binary_frame (height,width,CV_8UC1);
	
	//For blur
	Mat erode_element = cv::getStructuringElement(MORPH_RECT,Size(erode_kernel_size,erode_kernel_size), Point(-1,1));
	Mat dilate_element = cv::getStructuringElement(MORPH_RECT,Size(dilate_kernel_size,dilate_kernel_size),Point(-1,1));
	
	//Stuff for shape detection
	cv::OutputArrayOfArrays contours();
	
	//
	Scalar hsvLOW (0,0,0);
	Scalar hsvHIGH (255,255,255);
	
	namedWindow("RGB", WINDOW_AUTOSIZE );
	namedWindow("Binary",WINDOW_AUTOSIZE);

	while (ros::ok())
	{
		//contours.clear(); //Clear contours from last loop
		
		//Grab new frame from camera
		if (!cap.read(frame))
		{
			std::cerr << "Could not read frame" << std::endl;
			continue;
		}
		imshow("RGB", frame); //Show color image on screen
	
		medianBlur(frame,frame,blur_kernel_size); //Blurs frame
		cvtColor(frame,hsv_frame,CV_BGR2HSV); //Converts BGR frame to HSV color
		inRange(hsv_frame,hsvLOW,hsvHIGH,binary_frame); //Thresholds HSV frame for given range
		imshow("Binary",binary_frame);
		
		//findContours(binary_frame, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE,Point(0,0)); //Finds contours in binary frame

		msg.data = "ledon";
		chatter_pub.publish(msg);
		ros::spinOnce();
	}
	return 0;
}
