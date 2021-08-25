#pragma once
#define MOD_BASE_NUM 20
#define MOD_CONFUSE_NUM 64

extern "C" {
#include <miracl.h>
#include <mirdef.h>
#include <stdio.h>
}
#include <iostream>
//#include "blind.h"
#include "blind.h"
using namespace std;

//����ά������ܳ����ľ���
void EncryptArray(BPS_PriParas *private_paras, int rows, int cols, int** data, CipherText*** cipher);

//����ä�ӷ�
void BlindAddMatrix(BPS_PubParas* pub_paras, int rows, int cols, CipherText*** x, CipherText*** y, CipherText*** r);

//����ä����
void BlindSubMatrix(BPS_PubParas* pub_paras, int rows, int cols,  CipherText*** x, CipherText*** y, CipherText*** r);

//����ä�˷�
void BlindMulMatrix(BPS_PubParas* pub_paras, int rows, int cols, CipherText*** x, CipherText*** y, CipherText*** r);

//����ä���
void HalfBlindMulMatrix(BPS_PubParas* pub_paras, int rows, int cols, CipherText*** x, int** y, CipherText*** r);

//����ä���
void BlindConvolution(BPS_PubParas* pub_paras, CipherText*** x, CipherText*** y, CipherText*** r);

//�����ľ�����ܳɶ�ά����
int** DecryptArray(BPS_PriParas *private_paras, int rows, int cols, CipherText*** cipher);