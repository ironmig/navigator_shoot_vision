#include "ShapeFind.h"

ShapeFind::ShapeFind(Color C) { parseColor = c; }
ShapeFind::void FindContours() { findContours(binary_frame, contoursfindMat, hierarchyfindMat, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0)); }
ShapeFind::void FindShapes() {
    for (int i = 0; i < contoursfindMat.size(); i++) {
        std::vector<cv::Point> approx;
        approxPolyDP(Mat(contoursfindMat[i]), approx, arcLength(Mat(contoursfindMat[i]), true) * 0.025, true);
        shapes.push_back(approx);
    }
}

Point findCenter(std::vector<cvPoint> &points) {
    int x = 0, y = 0;
    for (int i = 0; i < approx.size(); i++) {
        x += approx[i].x;
        y += approx[i].y;
    }
    x /= approx.size();
    y /= approx.size();
    return Point(x, y);
}

ShapeFind::std::vector<Result> GetShapes(Mat frame) {
    Mat binary_frame = frame;
    FindContours();
    FindShapes();
    std::vector<Result> holder;
    for (int i = 0; i < shapes.size(); i++) {
        if (shapes[i].approx.size() == 12) {
            Result hold;
            hold.center = findCenter(shapes[i].approx.size());
            hold.Color = parseColor;
            hold.Shape = CROSS;
            holder.push_back(hold);
        } else if (shapes[i].approx.size() == 3) {
            Result hold;
            hold.center = findCenter(shapes[i].approx.size());
            hold.Color = parseColor;
            hold.Shape = CROSS;
            holder.push_back(hold);
        }
    }
    return holder;
}
