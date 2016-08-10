#include "DebugWindow.h"

Mat DebugWindow::color_frame = Mat();
Mat DebugWindow::red_frame = Mat();
Mat DebugWindow::green_frame = Mat();
Mat DebugWindow::blue_frame = Mat();
navigator_shoot_vision::Symbols DebugWindow::symbols = navigator_shoot_vision::Symbols();

void DebugWindow::init() {
    color_frame = Mat();
    red_frame = Mat();
    blue_frame = Mat();
    green_frame = Mat();
    symbols = navigator_shoot_vision::Symbols();
    namedWindow("color", CV_WINDOW_AUTOSIZE);
    namedWindow("red", CV_WINDOW_AUTOSIZE);
    namedWindow("blue", CV_WINDOW_AUTOSIZE);
    namedWindow("green", CV_WINDOW_AUTOSIZE);
    std::cout << "Running GUI Debug mode" << std::endl;
}

void DebugWindow::UpdateColor(Mat frame) {
    color_frame = frame;
    imshow("color", color_frame);
}
void DebugWindow::UpdateRed(Mat frame) {
    red_frame = frame;
    imshow("red", red_frame);
}
void DebugWindow::UpdateBlue(Mat frame) {
    blue_frame = frame;
    imshow("blue", blue_frame);
}
void DebugWindow::UpdateGreen(Mat frame) {
    green_frame = frame;
    imshow("green", green_frame);
}
void DebugWindow::UpdateResults(navigator_shoot_vision::Symbols symbols) {
    for (int i = 0; i < symbols.list.size(); i++) {
        cv::Rect p = cv::Rect(symbols.list[i].CenterX-50, symbols.list[i].CenterY-50, 100, 100);
        cv::rectangle(color_frame, p.tl(), p.br(), cv::Scalar(100, 100, 100), 2);
    }
    imshow("color", color_frame);
    // results = rs;
    // for (std::vector<ShapeFind::Result>::iterator it = results.begin();it != results.end(); it++)
    //{
    //	std::cout <<  "Color: " << (*it).color << " Shape: " << (*it).shape << std::endl;
    //}
}
