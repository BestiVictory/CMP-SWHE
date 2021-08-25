#include "blind.h"
#include "others.h"
//#include "test.h"
#include <iostream>
#include <windows.h>
#include <psapi.h>
#include <time.h>
#include <ctime>
#include <math.h>
#include <typeinfo>
#include <aes.h>  
#include <Hex.h>      // StreamTransformationFilter  
#include <modes.h>    // CFB_Mode  
#include <iostream>   // std:cerr    
#include <sstream>   // stringstream    
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc_c.h>
#include <fstream>

extern "C" {
#include <miracl.h>
#include <mirdef.h>
#include <stdio.h>
}

using namespace std;
using namespace cv;

int size1(big x)
{
	/*  get size of big number;  convert to integer - if possible */
	int n, m;
	mr_lentype s;
	if (x == NULL)return 0;
	s = (x->len&MR_MSBIT);
	m = (int)(x->len&MR_OBITS);
	if (m == 0)return 0;
	if (m == 1 && x->w[0] < (mr_small)MR_TOOBIG) n = (int)x->w[0];
	else n = MR_TOOBIG;
	if (s == MR_MSBIT)return(-n);
	return n;
}
cv::Mat Vec2Mat(cv::Mat img, int **array, int row, int col)
{
	uchar *ptmp = NULL;
	for (int i = 0; i < row; ++i)
	{
		ptmp = img.ptr<uchar>(i);
		for (int j = 0; j < col; ++j)
		{
			ptmp[j] = array[i][j];
		}
	}
	return img;
}
int main()
{
	miracl *mi = mirsys(70, 10);
	UserKey* uk = new UserKey();
	string u = "233";
	uk->setkey(u);
	BPS_PubParas* pub = new BPS_PubParas();
	BPS_PriParas* pri = new BPS_PriParas();
	create_BPS_Paras(uk, pub, pri,1);
	cout << "参数生成完毕" << endl;
	cv::Mat img1 = cv::imread("table1.jpg", 0);
	cv::Mat img2 = cv::imread("table2.jpg", 0);
	cv::Size size = img1.size();
	//cout << size.height << "," << size.width << endl;
	int **resint = new int*[size.height];
	for (int i = 0; i < size.height; i++)
	{
		resint[i] = new int[size.width];
	}
	CipherText* ct1;
	CipherText* ct2;
	CipherText* tmp;
	CipherText* res;
	CipherText* ans;
	CipherText* stard_in;
	CipherText* stard_out;
	int value = 20;//阈值
	stard_in = new CipherText();
	stard_out = new CipherText();
	Encrypt(pri, value, stard_in);
	BlindPow(pub, stard_in, 2, stard_out);//阈值的平方
	for (int i = 0; i < size.height; i++)
	{
		cout << i << endl;
		for (int j = 0; j < size.width; j++)
		{
			//srand(time(NULL));
			int mingwen1 = img1.at<uchar>(i, j), mingwen2 = img2.at<uchar>(i, j);
			ct1 = new CipherText();
			ct2 = new CipherText();
			tmp = new CipherText();
			ans = new CipherText();
			res = new CipherText();
			Encrypt(pri, mingwen1, ct1);
			Encrypt(pri, mingwen2, ct2);
			BlindSub(pub, ct1, ct2, tmp);
			BlindPow(pub, tmp, 2, res);
			BlindSub(pub, res, stard_out, ans);//和阈值的密文平方盲相减
			//srand(time(NULL));
			//int am = rand() % 1000 + 10;//随机成以的10-1009
			//Sendvalue(ans, am);
			//客户端解密
			int intres = Decrypt2(pri, ans);
			if (intres > 0)
			{
				intres = 255;
			}
			else
			{
				intres = 0;
			}
			resint[i][j] = intres;
			delete ct1->getValuesOnModBase();
			delete ct1;
			delete ct2->getValuesOnModBase();
			delete ct2;
			delete tmp->getValuesOnModBase();
			delete tmp;
			delete ans->getValuesOnModBase();
			delete ans;
			delete res->getValuesOnModBase();
			delete res;
		}
	}
	delete stard_in->getValuesOnModBase();
	delete stard_in;
	delete stard_out->getValuesOnModBase();
	delete stard_out;
	//cv::Mat imgres1(size.height, size.width, CV_8UC1);
	//cv::Mat imgres2(size.height, size.width, CV_8UC1);
	cv::Mat imgdif(size.height, size.width, CV_8UC1);
	imgdif = Vec2Mat(imgdif, resint, size.height, size.width);
	//cv::imshow("img1", imgres1);
	//cv::imshow("img2", imgres2);
	cv::imshow("img_dif", imgdif);
	cv::waitKey(0);
	for (int i = 0; i < size.height; i++) {
		//delete[] array1[i];
		//delete[] array2[i];
		//delete[] arrayres[i];
		delete[] resint[i];
	}
	//delete[] array1;
	//delete[] array2;
	//delete[] arrayres;
	delete[] resint;

	img1.release();
	img2.release();
	//imgres1.release();
	//imgres2.release();
	imgdif.release();
	//cv::destroyWindow("img1");
	//cv::destroyWindow("img2");
	cv::destroyWindow("img_dif");
	system("pause");
	return 0;
}