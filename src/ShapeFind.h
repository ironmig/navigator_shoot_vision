
//Finds shapes in Binary frame
class ShapeFind
{
	private:
		Color myColor;
		Mat binary_frame;
      	std::vector<std::vector<Point> > contoursfindMat;
		std::vector<Vec4i> hierarchyfindMat;
		std::vector < std::vector<cv::Point> > shapes;
		st
		void FindContours();
		void FindShapes();
	public:
		typedef struct Result
		{
			Point center;
			enum Color
			{
				RED,
				BLUE,
				GREEN,
				BLACK
			}
			enum Shape
			{
				CROSS,
				TRIANGLE,
				CIRLCE
			}
		}
		ShapeFind(Color c);
		std::vector<Result> GetShapes(Mat frame);		
};
