#ifndef SHAPE_FIND_HPP
#define SHAPE_FIND_HPP
// Finds shapes in Binary frame
class ShapeFind {
  private:
    Color parseColor;
    Mat binary_frame;
    std::vector<std::vector<Point>> contoursfindMat;
    std::vector<Vec4i> hierarchyfindMat;
    std::vector<std::vector<cv::Point>> shapes;
    Point findCenter(std::vector<Point> points);
    void FindContours();
    void FindShapes();

  public:
    typedef struct Result {
        Point center;
        enum Color { RED, BLUE, GREEN, BLACK };
        enum Shape { CROSS, TRIANGLE, CIRLCE };
    };
    ShapeFind(Color c);
    std::vector<Result> GetShapes(Mat frame);
};

#endif
