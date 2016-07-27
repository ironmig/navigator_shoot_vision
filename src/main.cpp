#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/opencv.hpp"

#include "ros/ros.h"
#include "std_msgs/String.h"

float getAngle(cv::Point p0, cv::Point p1, cv::Point p2) {
  float v1x = p1.x - p0.x;
  float v1y = p1.y - p0.y;
  float v2x = p2.x - p1.x;
  float v2y = p2.y - p1.y;

  std::cout << v1x << " " << v1y << " " << v2x << " " << v2y << std::endl;

  float dot = v1x * v2x + v1y * v2y;

  //	return dot;

  float mag = sqrt((v1x * v1x + v1y * v1y) + sqrt(v2x * v2x + v2y * v2y));
  std::cout << "dot: " << dot << " mag: " << mag << std::endl;
  return acos(dot / mag) * 90 / 3.1415;
}


int main(int argc, char **argv) {
	
ros::init(argc, argv, "talker");
 ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("shooter_control", 1000);
  
  
  
  cv::Mat A;
  A = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);

  cv::namedWindow("Display window", CV_WINDOW_AUTOSIZE);
  cv::imshow("Display window", A);

  cv::waitKey(0);

  cv::Mat B;
//  cv::blur(A, B, cv::Size(3, 3));
  cv::cvtColor(A, B, CV_BGR2GRAY );
  cv::threshold(B, B, 150, 255, 3);

  cv::imshow("Display window", B);
  cv::waitKey(0);

  cv::Mat canny_output;
  std::vector<std::vector<cv::Point> > contours;
  std::vector<cv::Vec4i> hierarchy;

  cv::Canny(B, canny_output, 0, 200 * 3, 3);

cv::imshow("Display window", canny_output);
cv::waitKey(0);

  cv::findContours(canny_output, contours, hierarchy, CV_RETR_TREE,
                   CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

  cv::imshow("Display window", canny_output);
      cv::Scalar color = cv::Scalar(0, 0, 200);
  cv::waitKey(0);
  cv::Mat drawing = cv::Mat::zeros(canny_output.size(), CV_8UC3);
  for (int i = 0; i < contours.size(); i++) {
    if (std::fabs(cv::contourArea(contours[i])) < 200)
      continue;
    std::vector<cv::Point> approx;
    cv::approxPolyDP(cv::Mat(contours[i]), approx,
                     cv::arcLength(cv::Mat(contours[i]), true) * 0.023, true);
    if (approx.size() == 12) {
    	std::cout<<"boo"<<std::endl;
		 cv::Rect _boundingRect = boundingRect( contours[i]);
		 cv::Scalar mean_color = cv::mean( A( _boundingRect ) );
		 std::cout<<mean_color<<std::endl;

		 cv::drawContours(A, contours, i, color, CV_FILLED );
		 
		 std_msgs::String msg;
		 std::stringstream ss;
		 ss << "ledon";
		  msg.data = ss.str();
		  ROS_INFO("%s", msg.data.c_str());
		  chatter_pub.publish(msg);
		  ros::spinOnce();
//		for(int j =0; j<11; j++) {
//			cv::line(A, approx[j], approx[j+1], color);
//		}
    }
//    if(approx.size()==3) {
//    	std::cout<<"triangle"<<std::endl;
//    	cv::Rect _boundingRect = boundingRect( contours[i]);
//		 cv::Scalar mean_color = cv::mean( A( _boundingRect ) );
//		 std::cout<<mean_color<<std::endl;
//		 cv::drawContours(A, contours, i, color, CV_FILLED );
//    }
  }

  cv::namedWindow("Contours", CV_WINDOW_AUTOSIZE);
  cv::imshow("Contours", A);
  cv::waitKey(0);
  return 0;
}
