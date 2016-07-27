class 
{
	private:
		static Mat color_frame;
		static Mat red_frame;
		static Mat green_frame;
		static Mat blue_frame;
		static std::vector<Results> results;
	public:
		static void init();
		static void UpdateColor(Mat frame)
		static void UpdateRed(Mat frame);
		static void UpdateBlue(Mat frame);
		static void UpdateGreen(Mat frame);
		static void UpdateResults(std::vector<Result> results);
		static void DrawAll();
};
