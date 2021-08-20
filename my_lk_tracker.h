//#pragma once
//#pragma once
//#ifndef LK_TRACKER
//#define LK_TRACKER
//
//#include <iostream>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/core/core.hpp>
//
//using namespace std;
//using namespace cv;
//
//void trace(string out) {
//	cout << out << endl;
//};
//
//struct TrackedPoint {
//	Point point;
//	Mat opticalFlow;
//	TrackedPoint() {};
//	TrackedPoint(const Point p, const Mat of) :point(p), opticalFlow(of) {};
//};
//
//class LKTracker {
//private:
//	int maxPyramidLayer = 3;
//	int wx = 2;
//	int wy = 2;
//	int maxIteration = 50;
//	double opticalflowResidual = 0.0001;
//
//private:
//	static int getMatInt(Mat mat, int row, int col);
//	static double getMatDouble(Mat mat, int row, int col);
//	static double getMatDouble(Mat mat, double row, double col);
//	void lowpassFilter(InputArray src, OutputArray dst);
//	Mat calcGradientMatrix(InputArray frame, Point2f p);
//	Mat calcMismatchVector(InputArray preFrame, InputArray curFrame, Point2f p, Mat g, Mat v);
//	vector<Mat> buildPyramid(InputArray src);
//	double calcResidual(Mat mat);
//	bool isOpticalFlowValid(Mat of);
//	double calcHarrisResponse(Mat gradient, double alpha);
//
//public:
//	LKTracker();
//	~LKTracker();
//	vector<TrackedPoint> track(InputArray preFrame, InputArray curFrame, vector<Point> keyPoints);
//	vector<Point> track2(InputArray preFrame, InputArray curFrame, vector<Point> keyPoints);
//	vector<TrackedPoint> trackAll(InputArray preFrame, InputArray curFrame, double qualityLevel);
//};
//
//#endif
