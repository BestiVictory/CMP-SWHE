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

//将二维数组加密成密文矩阵
void EncryptArray(BPS_PriParas *private_paras, int rows, int cols, int** data, CipherText*** cipher);

//矩阵盲加法
void BlindAddMatrix(BPS_PubParas* pub_paras, int rows, int cols, CipherText*** x, CipherText*** y, CipherText*** r);

//矩阵盲减法
void BlindSubMatrix(BPS_PubParas* pub_paras, int rows, int cols,  CipherText*** x, CipherText*** y, CipherText*** r);

//矩阵盲乘法
void BlindMulMatrix(BPS_PubParas* pub_paras, int rows, int cols, CipherText*** x, CipherText*** y, CipherText*** r);

//矩阵盲点积
void HalfBlindMulMatrix(BPS_PubParas* pub_paras, int rows, int cols, CipherText*** x, int** y, CipherText*** r);

//矩阵盲卷积
void BlindConvolution(BPS_PubParas* pub_paras, CipherText*** x, CipherText*** y, CipherText*** r);

//将密文矩阵解密成二维数组
int** DecryptArray(BPS_PriParas *private_paras, int rows, int cols, CipherText*** cipher);