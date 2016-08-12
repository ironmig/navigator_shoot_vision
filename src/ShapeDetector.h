#ifndef SHAPE_DETECTOR_H
#define SHAPE_DETECTOR_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

//Tests if polygons 
class ShapeDetector {
	private:
	static float findAngle(cv::Point p1, cv::Point p2, cv::Point p3);
	static float chisquared(std::vector<float> observed, float expected);
	static float findMean(std::vector<float> observed);
	static float findVarience(std::vector<float> observed);

	static bool boundingAreaCross(std::vector<cv::Point> &points);
	static bool boundingAreaTriangle(std::vector<cv::Point> &points);
	static bool boundingAreaCircle(std::vector<cv::Point> &points); //Either with points or with Mat?
	static bool angleTestCross(std::vector<cv::Point> &points);
	static bool angleTestTriangle(std::vector<cv::Point> &points);
	static bool angleTestCircle(std::vector<cv::Point> &points); //Maybe
	static bool testRatioCircle(std::vector<cv::Point> &points);
	
	public:
	static bool isCross(std::vector<cv::Point> &points);
	static bool isTriangle(std::vector<cv::Point> &points);
	static bool isCircle(std::vector<cv::Point> &points);

};

#endif
