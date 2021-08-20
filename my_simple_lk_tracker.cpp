//#include "my_lk_tracker.h"
//#include <opencv2\opencv.hpp>
//#include <iostream>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/core/core.hpp>
//#include <cmath>
//#include <algorithm>
////#include "blind.h"
//#include "blind2.h"
//#include "others.h"
//#include <iostream>
//#include <windows.h>
//#include <psapi.h>
//#include <time.h>
//#include <ctime>
//#include <math.h>
//#include <typeinfo>
//#include <aes.h>  
//#include <Hex.h>      // StreamTransformationFilter  
//#include <modes.h>    // CFB_Mode  
//#include <iostream>   // std:cerr    
//#include <sstream>   // stringstream    
//#include <string>
//extern "C" {
//#include <miracl.h>
//#include <mirdef.h>
//#include <stdio.h>
//}
//
//#pragma comment(lib, "cryptlib.lib" )  
//using namespace cv;
//using namespace std;
//using namespace CryptoPP;
//LKTracker::LKTracker() {
//
//}
//
//LKTracker::~LKTracker() {
//
//}
//int ccc = 0;
//int mmm = 0;
//int LKTracker::getMatInt(Mat mat, int row, int col) {
//	Size size = mat.size();
//	if (col < 0 || col >= size.width ||
//		row < 0 || row >= size.height) {
//		return 0;
//	}
//	return mat.at<uchar>(row, col);
//}
//
//double LKTracker::getMatDouble(Mat mat, int row, int col) {
//	Size size = mat.size();
//	if (col < 0 || col >= size.width ||
//		row < 0 || row >= size.height) {
//		return 0;
//	}
//	if (mat.type() == CV_64F) {
//		return mat.at<double>(row, col);
//	}
//	else {
//		return (double)mat.at<uchar>(row, col);
//	}
//}
//
//double LKTracker::getMatDouble(Mat mat, double row, double col) {
//	Size size = mat.size();
//	if (col < 0 || col >= size.width ||
//		row < 0 || row >= size.height) {
//		return 0;
//	}
//	int floorRow = floor(row);
//	int floorCol = floor(col);
//	double fracRow = row - floorRow;
//	double fracCol = col - floorCol;
//	int ceilRow = floorRow + 1;
//	int ceilCol = floorCol + 1;
//
//	return ((1.0 - fracRow) * (1.0 - fracCol) * getMatDouble(mat, floorRow, floorCol) +
//		(fracRow * (1.0 - fracCol) * getMatDouble(mat, ceilRow, floorCol)) +
//		((1.0 - fracRow) * fracCol * getMatDouble(mat, floorRow, ceilCol)) +
//		(fracRow * fracCol * getMatDouble(mat, ceilRow, ceilCol))
//		);
//}
//
//vector<int> get9Array(Mat Frame,int x,int y) {
//	vector<int> h;
//	h.push_back(Frame.at<uchar>(y - 1, x - 1));
//	h.push_back(Frame.at<uchar>(y - 1, x));
//	h.push_back(Frame.at<uchar>(y - 1, x + 1));
//	h.push_back(Frame.at<uchar>(y, x - 1));
//	h.push_back(Frame.at<uchar>(y, x));
//	h.push_back(Frame.at<uchar>(y, x + 1));
//	h.push_back(Frame.at<uchar>(y + 1, x - 1));
//	h.push_back(Frame.at<uchar>(y + 1, x ));
//	h.push_back(Frame.at<uchar>(y + 1, x + 1));
//	return h;
//}
//
//////只需将此函数改为盲计算即可
////int diff_vector(vector<int> v1, vector<int> v2) {
////	int diff = 0;
////	for (int i = 0;i < 9;i++) {
////		diff = diff + pow((v1[i] - v2[i]),2);
////	}
////	//cout << "diff=" << diff << endl;
////	return diff;
////}
//
////只需将此函数改为盲计算即可
//CipherText* diff_vector(CipherText *v1[], CipherText *v2[], CipherText *res, BPS_PubParas* pub) {
//	for (int i = 0;i < 9;i++) {
//		BlindSubInplace(pub, v2[i], v1[i]);
//		BlindPowInplace(pub, v2[i], 2);
//		BlindAddInplace(pub, res, v2[i]);
//		//cout << "order:" << res->getorder() << endl;
//	}
//	//cout << "8=" << v1[8]->getValuesOnModBase()->getvalue(2, 2) << endl;
//	return res;
//}
//
//vector<Point> LKTracker::track2(InputArray preFrame, InputArray curFrame, vector<Point> keyPoints) {
//	UserKey* uk = new UserKey();
//	string u = "233";
//	uk->setkey(u);
//	BPS_PubParas* pub = new BPS_PubParas();
//	BPS_PriParas* pri = new BPS_PriParas();
//
//	create_BPS_Paras(uk, pub, pri,10);
//
//	Mat preImage = preFrame.getMat();
//	Mat curImage = curFrame.getMat();
//	//tPoints是keypoints的返回值，即每一个keypoint下一帧的位置
//	vector<Point> tPoints;
//	//int count = 0;
//
//	//对于每个特征点做以下操作
//	for (unsigned int i = 0; i < keyPoints.size(); i++) {
//		//cout << "第" << i << "个点" << endl;
//		//以下由客户端计算
//		Point srcPoint = keyPoints[i];
//		vector<int> pre9;
//		vector<int> lefttop9, left9, leftbottom9, bottom9, rightbottom9, right9, righttop9, top9, middle9;
//		
//		pre9 = get9Array(preImage, srcPoint.x, srcPoint.y);
//		lefttop9 = get9Array(curImage, srcPoint.x-1, srcPoint.y-1);
//		top9 = get9Array(curImage, srcPoint.x, srcPoint.y - 1);
//		righttop9 = get9Array(curImage, srcPoint.x + 1, srcPoint.y - 1);
//		left9 = get9Array(curImage, srcPoint.x-1, srcPoint.y);
//		middle9 = get9Array(curImage, srcPoint.x, srcPoint.y);
//		right9 = get9Array(curImage, srcPoint.x + 1, srcPoint.y);
//		leftbottom9 = get9Array(curImage, srcPoint.x-1, srcPoint.y+1);
//		bottom9 = get9Array(curImage, srcPoint.x, srcPoint.y+1);
//		rightbottom9 = get9Array(curImage, srcPoint.x+1, srcPoint.y+1);
//
//		//在客户端对明文加密
//		CipherText *pre_blind9[9], *lefttop_blind9[9], *top_blind9[9], *righttop_blind9[9], *left_blind9[9], *middle_blind9[9], *right_blind9[9], *leftbottom_blind9[9], *bottom_blind9[9], *rightbottom_blind9[9];
//		for (int i = 0; i < 9; i++)
//		{
//			pre_blind9[i] = new CipherText();
//			Encrypt(pri, pre9[i], pre_blind9[i]);
//			lefttop_blind9[i] = new CipherText();
//			Encrypt(pri, lefttop9[i], lefttop_blind9[i]);
//			top_blind9[i] = new CipherText();
//			Encrypt(pri, top9[i], top_blind9[i]);
//			righttop_blind9[i] = new CipherText();
//			Encrypt(pri, righttop9[i], righttop_blind9[i]);
//			left_blind9[i] = new CipherText();
//			Encrypt(pri, left9[i], left_blind9[i]);
//			middle_blind9[i] = new CipherText();
//			Encrypt(pri, middle9[i], middle_blind9[i]);
//			right_blind9[i] = new CipherText();
//			Encrypt(pri, right9[i], right_blind9[i]);
//			leftbottom_blind9[i] = new CipherText();
//			Encrypt(pri, leftbottom9[i], leftbottom_blind9[i]);
//			bottom_blind9[i] = new CipherText();
//			Encrypt(pri, bottom9[i], bottom_blind9[i]);
//			rightbottom_blind9[i] = new CipherText();
//			Encrypt(pri, rightbottom9[i], rightbottom_blind9[i]);
//		}
//		
//		CipherText* kong1 = new CipherText();
//		CipherText* kong2 = new CipherText();
//		CipherText* kong3 = new CipherText();
//		CipherText* kong4 = new CipherText();
//		CipherText* kong5 = new CipherText();
//		CipherText* kong6 = new CipherText();
//		CipherText* kong7 = new CipherText();
//		CipherText* kong8 = new CipherText();
//		CipherText* kong9 = new CipherText();
//		Encrypt(pri, 0, kong1);
//		Encrypt(pri, 0, kong2);
//		Encrypt(pri, 0, kong3);
//		Encrypt(pri, 0, kong4);
//		Encrypt(pri, 0, kong5);
//		Encrypt(pri, 0, kong6);
//		Encrypt(pri, 0, kong7);
//		Encrypt(pri, 0, kong8);
//		Encrypt(pri, 0, kong9);
//		//以下由服务端计算
//		CipherText* dif_blind[9] = { diff_vector(pre_blind9,lefttop_blind9,kong1,pub),diff_vector(pre_blind9,top_blind9,kong2,pub),
//			diff_vector(pre_blind9,righttop_blind9,kong3,pub), diff_vector(pre_blind9,left_blind9,kong4,pub),
//			diff_vector(pre_blind9,middle_blind9,kong5,pub), diff_vector(pre_blind9,right_blind9,kong6,pub),
//			diff_vector(pre_blind9,leftbottom_blind9,kong7,pub), diff_vector(pre_blind9,bottom_blind9,kong8,pub),
//			diff_vector(pre_blind9,rightbottom_blind9,kong9,pub) };
//		
//		////以下由服务端计算
//		//int dif[9] = {diff_vector(pre9,lefttop9),diff_vector(pre9,top9), diff_vector(pre9,righttop9), diff_vector(pre9,left9),
//		//	diff_vector(pre9,middle9), diff_vector(pre9,right9), diff_vector(pre9,leftbottom9), diff_vector(pre9,bottom9), diff_vector(pre9,rightbottom9) };
//		
//		int dif_decrypt[9];
//		//cout << "??" << endl;
//		//以下由客户端解密
//		for (int i = 0; i < 9; i++)
//		{
//			//cout << "d[" << i << "]=" << Decrypt2(pri, dif_blind[i]) << endl;
//			dif_decrypt[i] = Decrypt2(pri, dif_blind[i]);
//		}
//
//		//以下要用额外的服务器（/客户端）来计算
//		int minValue = *min_element(dif_decrypt, dif_decrypt + 9);
//		int minIndex = min_element(dif_decrypt, dif_decrypt + 9)- dif_decrypt;
//		//cout <<"min="<< minIndex << endl;
//
//		Point dstPoint;
//		switch (minIndex)
//		{
//		case(0):
//			dstPoint.x = srcPoint.x - 1;
//			dstPoint.y = srcPoint.y - 1;
//		case(1):
//			dstPoint.x = srcPoint.x;
//			dstPoint.y = srcPoint.y - 1;
//		case(2):
//			dstPoint.x = srcPoint.x + 1;
//			dstPoint.y = srcPoint.y - 1;
//		case(3):
//			dstPoint.x = srcPoint.x - 1;
//			dstPoint.y = srcPoint.y;
//		case(4):
//			dstPoint.x = srcPoint.x;
//			dstPoint.y = srcPoint.y;
//		case(5):
//			dstPoint.x = srcPoint.x + 1;
//			dstPoint.y = srcPoint.y;
//		case(6):
//			dstPoint.x = srcPoint.x - 1;
//			dstPoint.y = srcPoint.y + 1;
//		case(7):
//			dstPoint.x = srcPoint.x;
//			dstPoint.y = srcPoint.y + 1;
//		case(8):
//			dstPoint.x = srcPoint.x + 1;
//			dstPoint.y = srcPoint.y + 1;
//		default:
//			break;
//		}
//		delete kong1, kong2, kong3, kong4, kong5, kong6, kong7, kong8, kong9;
//
//		Point tPoint(dstPoint);
//		tPoints.push_back(tPoint);
//
//		for (int i = 0; i < 9; i++)
//		{
//			delete pre_blind9[i]->getValuesOnModBase();
//			delete pre_blind9[i];
//			delete lefttop_blind9[i]->getValuesOnModBase();
//			delete lefttop_blind9[i];
//			delete top_blind9[i]->getValuesOnModBase();
//			delete top_blind9[i];
//			delete righttop_blind9[i]->getValuesOnModBase();
//			delete righttop_blind9[i];
//			delete left_blind9[i]->getValuesOnModBase();
//			delete left_blind9[i];
//			delete middle_blind9[i]->getValuesOnModBase();
//			delete middle_blind9[i];
//			delete right_blind9[i]->getValuesOnModBase();
//			delete right_blind9[i];
//			delete leftbottom_blind9[i]->getValuesOnModBase();
//			delete leftbottom_blind9[i];
//			delete bottom_blind9[i]->getValuesOnModBase();
//			delete bottom_blind9[i];
//			delete rightbottom_blind9[i]->getValuesOnModBase();
//			delete rightbottom_blind9[i];
//		}
//	}
//	return tPoints;
//}
//
//int const MAX_CORNERS = 1000;
//int main(int argc, char **argv)
//{
//	//CvCapture* capture = 0;
//	//capture = cvCaptureFromCAM(CV_CAP_ANY);  //get frame
//
//	IplImage *src_img1;  //the previous frame (gray)
//	IplImage *src_img2;  //the current frame(gray)
//
//	IplImage *dst_img;   //the result
//	IplImage *cur_img;
//	IplImage *pre_img;
//
//	IplImage *kong_dst_img;//全黑图用于在上边加光流效果
//
//	CvPoint2D32f * move_old_point = new CvPoint2D32f[MAX_CORNERS];
//	CvPoint2D32f * move_new_point = new CvPoint2D32f[MAX_CORNERS];
//	char *features_found = new char[MAX_CORNERS];
//	float *features_error = new float[MAX_CORNERS];
//	CvTermCriteria criteria;
//	criteria = cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 64, 0.01);
//
//	int i, j;
//
//	int p = 0;
//	int rows, cols;
//	int countn = MAX_CORNERS;
//
//	pre_img = cvLoadImage("..//..//input_png//pets2006//image1124.png", 1);
//
//	CvSize img_sz = cvGetSize(pre_img);
//	src_img1 = cvCreateImage(img_sz, IPL_DEPTH_8U, 1);
//	cvCvtColor(pre_img, src_img1, CV_RGB2GRAY);
//
//	cur_img = cvLoadImage("..//..//input_png//pets2006//image1126.png", 1);
//	src_img2 = cvCreateImage(img_sz, IPL_DEPTH_8U, 1);
//	cvCvtColor(cur_img, src_img2, CV_RGB2GRAY);
//
//	dst_img = (IplImage *)cvClone(cur_img);
//	Mat m = Mat(Size(src_img1->width, src_img1->height), CV_8UC3, Scalar(0, 0, 0));
//	IplImage temp = (IplImage)m;
//	kong_dst_img = &temp;
//
//	IplImage *move_img = cvCreateImage(img_sz, IPL_DEPTH_8U, 1);
//	cvZero(move_img);
//	//cvAbsDiff(src_img1, src_img2,move_img);
//	cols = src_img1->width;
//	rows = src_img1->height;
//	for (i = 0; i < cols; i++)
//	{
//		for (j = 0; j < rows; j++)
//		{
//			double a = abs(cvGet2D(src_img1, j, i).val[0] - cvGet2D(src_img2, j, i).val[0]);
//			//CvScalar b = cvScalar(a, 0, 0, 0);
//			//cvSet2D(move_img, j, i, b);
//			if (a > 20)
//			{
//				if (p < MAX_CORNERS - 1)
//				{
//					a = 255;
//					int d = ++p;
//					move_old_point[d].x = i;
//					move_old_point[d].y = j;
//					//d=1--d=999
//				}
//			}
//			else {
//				a = 0;
//			}
//			CvScalar b = cvScalar(a, 0, 0, 0);
//			cvSet2D(move_img, j, i, b);
//		}
//	}
//	//cvNamedWindow("moving object", 1);
//	//cvShowImage("moving object", move_img);
//
//	cv::Mat mat_src_img1 = cv::cvarrToMat(cvLoadImage("..//..//input_png//pets2006//image1124.png", CV_LOAD_IMAGE_GRAYSCALE));
//	cv::Mat mat_src_img2 = cv::cvarrToMat(cvLoadImage("..//..//input_png//pets2006//image1126.png", CV_LOAD_IMAGE_GRAYSCALE));
//
//
//	vector<Point> keyPoints(MAX_CORNERS - 1);
//	for (int i = 0; i < MAX_CORNERS - 1; i++) {
//		keyPoints[i].x = int(move_old_point[i + 1].x);
//		keyPoints[i].y = int(move_old_point[i + 1].y);
//	}
//
//
//	LKTracker* lkt = new LKTracker();
//	vector<Point> res;
//	//res = lkt->trackAll(mat_src_img1, mat_src_img2,0.01);
//	//cout << "sss:" << res[1].point.x << endl;
//	//cout << "sss:" << res[1].point.y << endl;
//
//	res = lkt->track2(mat_src_img1, mat_src_img2, keyPoints);
//	cout << "size=" << res.size() << endl;
//	//cout << "ccc=" << ccc << endl;
//	//cout << "mmm=" << mmm << endl;
//
//	//Mat m;
//	//m.create(Size(src_img1->width, src_img1->height), CV_8UC1);
//	//m.at<uchar>(1, 2) = (uchar)123;
//
//	int dx, dy;
//	for (i = 0; i < MAX_CORNERS - 1; i++)
//	{
//		//int x1 = (int)res[i].point.x;
//		//int x2 = (int)move_old_point[i].x;
//		//int y1 = (int)res[i].point.y;
//		//int y2 = (int)move_old_point[i].y;
//		int x1 = (int)res[i].x;
//		int x2 = (int)move_old_point[i+1].x;
//		int y1 = (int)res[i].y;
//		int y2 = (int)move_old_point[i+1].y;
//
//		dx = abs(x1 - x2);
//		dy = abs(y1 - y2);
//
//		if (dx+dy>=2)
//		{
//			cvLine(dst_img, cvPoint(x2, y2), cvPoint(x1, y1), CV_RGB(255, 0, 0), 1, CV_AA, 0);
//			cvLine(kong_dst_img, cvPoint(x2, y2), cvPoint(x1, y1), CV_RGB(255, 0, 0), 1, CV_AA, 0);
//		}
//	}
//	cvNamedWindow("原图+光流", 1);
//	cvShowImage("原图+光流", dst_img);
//	cvSaveImage("原图光流.png", dst_img);
//	cvNamedWindow("光流", 1);
//	cvShowImage("光流", kong_dst_img);
//	cvSaveImage("纯光流.png", kong_dst_img);
//	cvWaitKey(0);
//	cvReleaseImage(&dst_img);
//	//cvReleaseImage(&pyrA);
//	//cvReleaseImage(&pyrB);
//	cvReleaseImage(&move_img);
//
//	return 0;
//}