#ifndef SHAPE_FIND_HPP
#define SHAPE_FIND_HPP
// Finds shapes in Binary frame

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
class ShapeFind {
  public:
    enum Color { RED,BLUE, GREEN };
    enum Shape { CROSS, TRIANGLE, CIRCLE };
    struct Result {
        Point center;
        Color color;
        Shape shape;
    };
    ShapeFind(Color c);
    void GetShapes(Mat frame, std::vector<Result>* results);
  private:
    Color parseColor;
    Mat binary_frame;
    std::vector< std::vector<Point> > contoursfindMat;
    std::vector<Vec4i> hierarchyfindMat;
    std::vector<std::vector<cv::Point> > shapes;
    Point findCenter(std::vector<Point> points);
    void FindContours();
    void FindShapes();
};

#endif
