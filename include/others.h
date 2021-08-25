#pragma once
extern "C" {
#include <miracl.h>
#include <mirdef.h>
#include <stdio.h>
}
#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc_c.h>
using namespace std;
using namespace cv;

//随机打乱数组顺序
void randomArray(int a[], int n);

//十六进制字符串转二进制字符串
string HexToBin(string h);

//二进制字符串转十进制int
int Bin2Dec(string s);

//ECB模式的AES加密
string ECB_AESEncryptStr(string sKey, const char *plainText);

//ECB模式的AES解密
string ECB_AESDecryptStr(string sKey, const char *cipherText);

//二维数组转为Mat
Mat Vec2Mat(Mat img, int **array, int row, int col);

//Mat转为一位数组
void Mat2List(Mat m,int list[]);

//一维数组转为二维数组
void one2two(int list[], int **array, int row, int col);


