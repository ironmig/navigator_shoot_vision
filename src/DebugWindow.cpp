#include "DebugWindow.h"

Mat DebugWindow::color_frame = Mat();
Mat DebugWindow::red_frame = Mat();
Mat DebugWindow::green_frame = Mat();
Mat DebugWindow::blue_frame = Mat();
navigator_shoot_vision::Symbols DebugWindow::symbols = navigator_shoot_vision::Symbols();
std::vector<navigator_shoot_vision::Symbols> DebugWindow::allFoundSymbols = std::vector<navigator_shoot_vision::Symbols>();

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
    namedWindow("Result",CV_WINDOW_AUTOSIZE);
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
  Mat res = color_frame;
    for (int i = 0; i < symbols.list.size(); i++) {
    	allFoundSymbols.push_back(symbols);
        cv::Rect p = cv::Rect(symbols.list[i].CenterX-50, symbols.list[i].CenterY-50, 100, 50);
        cv::rectangle(res, p, cv::Scalar(200, 200, 200), -1);
        Scalar color;
        if(symbols.list[i].Color == 'r') color = Scalar(0,0,100);
        else if(symbols.list[i].Color == 'g') color = Scalar(0,100,0);
       	else if(symbols.list[i].Color == 'b') color = Scalar(100,0,0);
       	
       	
       	if(symbols.list[i].Shape == 't') putText(res, "TRI", Point(symbols.list[i].CenterX-25, symbols.list[i].CenterY-25), 4, 1, color,  3);
       	if(symbols.list[i].Shape == 'c') putText(res, "CIR", Point(symbols.list[i].CenterX-25, symbols.list[i].CenterY-25), 4, 1, color,  3);
       	if(symbols.list[i].Shape == 'p') putText(res, "CROSS", Point(symbols.list[i].CenterX-50, symbols.list[i].CenterY-25), 4, 1, color,3);
    }
    imshow("Result",res);
    

    // results = rs;
    // for (std::vector<ShapeFind::Result>::iterator it = results.begin();it != results.end(); it++)
    //{
    //	std::cout <<  "Color: " << (*it).color << " Shape: " << (*it).shape << std::endl;
    //}
}
