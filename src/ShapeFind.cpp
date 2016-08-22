#include "ShapeFind.h"

ShapeFind::ShapeFind(std::string color) {
  parseColor = color;
  binary_frame = Mat();
  contoursfindMat = std::vector<std::vector<Point> >();
  hierarchyfindMat = std::vector<Vec4i>();
  shapes = std::vector<std::vector<cv::Point> >();
  Point findCenter(std::vector<Point> points);
}
void ShapeFind::FindContours() {
  contoursfindMat.clear();
  hierarchyfindMat.clear();
  findContours(binary_frame, contoursfindMat, hierarchyfindMat, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));  /// currently produces error
}
void ShapeFind::FindShapes() {
  shapes.clear();
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
void ShapeFind::GetSymbols(Mat frame, navigator_shoot_vision::Symbols *symbols) {
  binary_frame = frame.clone();
  if (binary_frame.empty()) {
    std::cerr << "frame too small" << std::endl;
    return;
  }
  FindContours();
  FindShapes();

  for (int i = 0; i < shapes.size(); i++) {
    if (ShapeDetector::isCross(shapes[i])) {
      navigator_shoot_vision::Symbol hold;
      Point center = findCenter(shapes[i]);
      hold.CenterX = center.x;
      hold.CenterY = center.y;
      hold.Color = parseColor;
      hold.Shape = navigator_shoot_vision::Symbol::CROSS;
      for (int j = 0; j < shapes[i].size(); j++) {
        geometry_msgs::Point p;
        p.x = shapes[i][j].x;
        p.y = shapes[i][j].y;
        p.z = 0;
        hold.points.push_back(p);
      }
      symbols->list.push_back(hold);
    } else if (ShapeDetector::isTriangle(shapes[i])) {
      navigator_shoot_vision::Symbol hold;
      Point center = findCenter(shapes[i]);
      hold.CenterX = center.x;
      hold.CenterY = center.y;
      hold.Color = parseColor;
      hold.Shape = navigator_shoot_vision::Symbol::TRIANGLE;
      for (int j = 0; j < shapes[i].size(); j++) {
        geometry_msgs::Point p;
        p.x = shapes[i][j].x;
        p.y = shapes[i][j].y;
        p.z = 0;
        hold.points.push_back(p);
      }
      symbols->list.push_back(hold);
    } else if (ShapeDetector::isCircle(shapes[i])) {
      navigator_shoot_vision::Symbol hold;
      Point center = findCenter(shapes[i]);
      hold.CenterX = center.x;
      hold.CenterY = center.y;
      hold.Color = parseColor;
      hold.Shape = navigator_shoot_vision::Symbol::CIRCLE;
      for (int j = 0; j < shapes[i].size(); j++) {
        geometry_msgs::Point p;
        p.x = shapes[i][j].x;
        p.y = shapes[i][j].y;
        p.z = 0;
        hold.points.push_back(p);
      }
      symbols->list.push_back(hold);
    }
  }
}
