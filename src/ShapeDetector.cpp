

#include "ShapeDetector.h"

float ShapeDetector::findAngle(cv::Point p1, cv::Point p2, cv::Point p3) {
    cv::Point v1 = p2 - p1;
    cv::Point v2 = p3 - p1;
    float m1 = sqrt(v1.x * v1.x + v1.y * v1.y);
    float m2 = sqrt(v2.x * v2.x + v2.y * v2.y);
    float dot = v1.x * v2.x + v1.y * v2.y;

    float thecos = dot / (m1 * m2);

    return acos(thecos) * 180 / 3.1415;
}
float ShapeDetector::chisquared(std::vector<float> observed, float expected) {
    float sum = 0;
    for (int i = 0; i < observed.size(); i++) {
        sum += (observed[i] - expected) * (observed[i] - expected);
    }
    return sum / expected;
}

float ShapeDetector::findMean(std::vector<float> observed) {
    float sum = 0;
    for (int i = 0; i < observed.size(); i++) {
        sum += observed[i];
    }
    return sum / observed.size();
}
float ShapeDetector::findVarience(std::vector<float> observed) {
    float mean = findMean(observed);
    float sum = 0;
    for (int i = 0; i < observed.size(); i++) {
        sum += (observed[i] - mean) * (observed[i] - mean);
    }

    return sum / (observed.size() - 1);
}

bool ShapeDetector::boundingAreaCross(std::vector<cv::Point> &points) {
    cv::Rect boundingRect = cv::boundingRect(points);
    float area = contourArea(points) / (boundingRect.width * boundingRect.height);
//    std::cout << area << std::endl;
    if (area >= .53 && area <= .57)
        return true;
    return false;
}

bool ShapeDetector::boundingAreaTriangle(std::vector<cv::Point> &points) {
    cv::Rect boundingRect = cv::boundingRect(points);
    float area = contourArea(points) / (boundingRect.width * boundingRect.height);

    if (area >= .41 && area <= .5)
        return true;
    return false;
}

bool ShapeDetector::angleTestCross(std::vector<cv::Point> &points) {
    std::vector<float> angles;
    for (int i = 0; i < 10; i += 2) {
        angles.push_back(findAngle(points[i + 1], points[i], points[i + 2]));
    }
    angles.push_back(findAngle(points[11], points[10], points[0]));
    float chi = chisquared(angles, 90);
    float var = findVarience(angles);

    if (chi < 20 && var < 25) {

        return true;
    }
    return false;
}

bool ShapeDetector::angleTestTriangle(std::vector<cv::Point> &points) {

    std::vector<float> angles;
    angles.push_back(findAngle(points[1], points[0], points[2]));
    angles.push_back(findAngle(points[2], points[1], points[0]));
    angles.push_back(findAngle(points[0], points[1], points[2]));

    float chi = chisquared(angles, 60);
    float var = findVarience(angles);
    //            std::cout << "result: " << chi << std::endl;
    //            std::cout << "result: " << chi << " Mean: " << mean << " Var: " << var << std::endl;

    if (chi < 20 && var < 25) {
        return true;
    }
    return false;
}

bool ShapeDetector::testRatioCircle(std::vector<cv::Point> &points) {
	float a = contourArea(points);
	float p = arcLength(points, true);
	float r = 4 * 3.1415 * a / (p * p);
	if(r > 0.9 && r < 1.1)
		return true;
	return false;

}
