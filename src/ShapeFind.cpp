#include "ShapeFind.h"

ShapeFind::ShapeFind(Color c) { 
	parseColor = c; 
    binary_frame = Mat();
    contoursfindMat = std::vector< std::vector<Point> >();
    hierarchyfindMat = std::vector<Vec4i>();
	shapes = std::vector<std::vector<cv::Point> > ();
    Point findCenter(std::vector<Point> points);
}
void ShapeFind::FindContours() { 
	findContours(binary_frame, contoursfindMat, hierarchyfindMat, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0)); ///currently produces error
}
void ShapeFind::FindShapes() {
	std::cout << "Findin shapes" << std::endl;
    for (int i = 0; i < contoursfindMat.size(); i++) {
        std::vector<cv::Point> approx;
        approxPolyDP(Mat(contoursfindMat[i]), approx, arcLength(Mat(contoursfindMat[i]), true) * 0.025, true);
        shapes.push_back(approx);
    }
}

Point ShapeFind::findCenter(std::vector<Point> points) {
    int x = 0, y = 0;
    for (int i = 0; i < points.size(); i++) {
        x += points[i].x;
        y += points[i].y;
    }
    x /= points.size();
    y /= points.size();
    return Point(x, y);
}

void ShapeFind::GetShapes(Mat frame, std::vector<Result> results)
{

    Mat binary_frame = frame;
    FindContours();

    FindShapes();
    for (int i = 0; i < shapes.size(); i++) {
        if (shapes[i].size() == 12) {
            Result hold;
            hold.center = findCenter(shapes[i]);
            hold.color = parseColor;
            hold.shape = CROSS;
            results.push_back(hold);
        } else if (shapes[i].size() == 3) {
            Result hold;
            hold.center = findCenter(shapes[i]);
            hold.color = parseColor;
            hold.shape = CROSS;
            results.push_back(hold);
        }
    }
}
