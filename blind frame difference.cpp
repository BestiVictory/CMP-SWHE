//#include "blind.h"
//#include "others.h"
//#include "test.h"
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
//#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>  
//#include <opencv2/highgui/highgui.hpp> 
//#include <opencv2/imgproc/imgproc_c.h>
//#include <fstream>
//
//extern "C" {
//#include <miracl.h>
//#include <mirdef.h>
//#include <stdio.h>
//}
//
//using namespace std;
//using namespace cv;
//
////int size1(big x)
////{  /*  get size of big number;  convert to integer - if possible */
////	int n, m;
////	mr_lentype s;
////	if (x == NULL) return 0;
////	s = (x->len&MR_MSBIT);
////	m = (int)(x->len&MR_OBITS);
////	if (m == 0) return 0;
////	if (m == 1 && x->w[0] < (mr_small)MR_TOOBIG) n = (int)x->w[0];
////	else                                     n = MR_TOOBIG;
////	if (s == MR_MSBIT) return (-n);
////	return n;
////}
//
//int main()
//{
//	miracl *mi = mirsys(70, 10); //初始化系统，分配60位的十进制空间
//	UserKey* uk = new UserKey();
//	string u = "233";
//	uk->setkey(u);
//	BPS_PubParas* pub = new BPS_PubParas();
//	BPS_PriParas* pri = new BPS_PriParas();
//	create_BPS_Paras(uk, pub, pri);
//
//
//	//Mat img_pre = imread("..//Data//car1.jpg", 0);
//	//Mat img_now = imread("..//Data//car2.jpg", 0);
//	Mat img_pre = imread("..//..//input_png//image1124.png", 0);
//	Mat img_now = imread("..//..//input_png//image1125.png", 0);
//	// 创建一个二维数组中包含4个一维数组，即先定义4行
//	Size size = img_pre.size();
//	cout << size.height << "," << size.width << endl;
//
//	int h;
//	cin >> h;
//
//	int **resint = new int *[size.height];
//	for (int i = 0; i < size.height; i++) {
//		resint[i] = new int[size.width];
//	}
//	CipherText* ct_pre;
//	CipherText* ct_now;
//	CipherText* res;
//	for (int i = 0; i < size.height; i++) {
//		cout << i << endl;
//		for (int j = 0; j < size.width; j++) {
//			int mingwen_pre = img_pre.at<uchar>(i, j), mingwen_now = img_now.at<uchar>(i, j);
//			//cout << mingwen_pre << "," << mingwen_now << endl;
//			ct_pre = new CipherText();
//			ct_now = new CipherText();
//			res = new CipherText();
//			Encrypt(pri, mingwen_pre, ct_pre);
//			Encrypt(pri, mingwen_now, ct_now);
//			BlindSub(pub, ct_pre, ct_now, res);      //盲减
//			//big pdata = mirvar(0);
//			//pdata = Decrypt(pri, res);
//			//int intres = size1(pdata);
//			int intres = Decrypt2(pri, res);
//			//cout <<"intres=" <<intres << endl;
//			if (abs(intres) > 20) {
//				intres = 255;
//			}
//			else
//			{
//				intres = 0;
//			}
//			//cout << "解密结果为：" << intres << endl;
//			resint[i][j] = intres;
//			delete ct_pre->getValuesOnModBase();
//			delete ct_pre;
//			delete ct_now->getValuesOnModBase();
//			delete ct_now;
//			delete res->getValuesOnModBase();
//			delete res;
//			//mirkill(pdata);
//		}
//	}
//
//	//Mat imgres1(size.height, size.width, CV_8UC1);
//	//Mat imgres2(size.height, size.width, CV_8UC1);
//	Mat imgdif(size.height, size.width, CV_8UC1);
//	//imgres1 = Vec2Mat(imgres1,array1, size.height, size.width);
//	//imgres2 = Vec2Mat(imgres2, array2, size.height, size.width);
//	imgdif = Vec2Mat(imgdif, resint, size.height, size.width);
//	//imshow("img_pre", imgres1);
//	//imshow("img_now", imgres2);
//	imshow("img_dif", imgdif);
//	waitKey(0);
//	// 使用完请求分配的数值需要释放分配空间（内存）
//	// 释放分配空间，一行一行的删除
//	for (int i = 0; i < size.height; i++) {
//		//delete[] array1[i];
//		//delete[] array2[i];
//		//delete[] arrayres[i];
//		delete[] resint[i];
//	}
//	//delete[] array1;
//	//delete[] array2;
//	//delete[] arrayres;
//	delete[] resint;
//
//	img_pre.release();
//	img_now.release();
//	//imgres1.release();
//	//imgres2.release();
//	imgdif.release();
//	//destroyWindow("img_pre");
//	//destroyWindow("img_now");
//	destroyWindow("img_dif");
//	int jh;
//	cin >> jh;
//
//	return 0;
//}