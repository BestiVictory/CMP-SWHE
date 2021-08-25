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

//�����������˳��
void randomArray(int a[], int n);

//ʮ�������ַ���ת�������ַ���
string HexToBin(string h);

//�������ַ���תʮ����int
int Bin2Dec(string s);

//ECBģʽ��AES����
string ECB_AESEncryptStr(string sKey, const char *plainText);

//ECBģʽ��AES����
string ECB_AESDecryptStr(string sKey, const char *cipherText);

//��ά����תΪMat
Mat Vec2Mat(Mat img, int **array, int row, int col);

//MatתΪһλ����
void Mat2List(Mat m,int list[]);

//һά����תΪ��ά����
void one2two(int list[], int **array, int row, int col);


