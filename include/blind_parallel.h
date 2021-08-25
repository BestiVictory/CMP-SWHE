#pragma once
#pragma once
#pragma once
#pragma once


#include "blind.h" 
extern "C" {
#include <miracl.h>
#include <mirdef.h>
#include <stdio.h>
}
#include <iostream>
using namespace std;


//合成大数
big ComposeToBig(BPS_PriParas *private_paras, int num, int plain[]);

//对大数进行加密
int MultiEncrypt(BPS_PriParas *private_paras, big data, CipherText* cipher);

//根据秘密参数解密
big MultiDecrypt(BPS_PriParas *private_paras, CipherText* cipher);

//根据秘密参数解密
void DecomposeToInt(BPS_PriParas *private_paras, int num, big cipher, int res[]);



//求密文相反数 r=-x
void MultiBlindNegify(BPS_PubParas* pub_paras, CipherText* x[], CipherText* r[]);

//求密文相反数(替代)x=-x
void MultiBlindNegifyInplace(BPS_PubParas* pub_paras, CipherText* x[]);

//盲加法 r=x+y
void MultiBlindAdd(BPS_PubParas* pub_paras, CipherText* x[], CipherText* y[], CipherText* r[]);

//盲加法(替代) x=x+y
void MultiBlindAddInplace(BPS_PubParas* pub_paras, CipherText* x[], CipherText* y[]);

//盲减法 r=x-y
void MultiBlindSub(BPS_PubParas* pub_paras, big x, big y, big r);

//盲减法(替代) x=x-y
void MultiBlindSubInplace(BPS_PubParas* pub_paras, CipherText* x[], CipherText* y[]);

//盲乘法 r=x*y
void MultiBlindMul(BPS_PubParas* pub_paras, CipherText* x[], CipherText* y[], CipherText* r[]);

//盲乘法(替代) x=x*y
void MultiBlindMulInplace(BPS_PubParas* pub_paras, CipherText* x[], CipherText* y[]);

//盲幂运算 r=x^y
void MultiBlindPow(BPS_PubParas* pub_paras, CipherText* x[], int y[], CipherText* r[]);

//盲幂运算(替代) x=x^y
void MultiBlindPowInplace(BPS_PubParas* pub_paras, CipherText* x[], int y[]);

//半盲加法 r=x+y
void MultiHalfBlindAdd(BPS_PubParas* pub_paras, CipherText* x[], int y[], CipherText* r[]);

//半盲加法(替代) x=x+y
void MultiHalfBlindAddInplace(BPS_PubParas* pub_paras, CipherText* x[], int y[]);

//半盲减法 r=x-y
void MultiHalfBlindSub(BPS_PubParas* pub_paras, CipherText* x[], int y[], CipherText* r[]);

//半盲减法(替代) x=x-y
void MultiHalfBlindSubInplace(BPS_PubParas* pub_paras, CipherText* x[], int y[]);

//半盲乘法 r=x*y
void MultiHalfBlindMul(BPS_PubParas* pub_paras, CipherText* x[], int y[], CipherText* r[]);

//半盲乘法(替代) x=x*y
void MultiHalfBlindMulInplace(BPS_PubParas* pub_paras, CipherText* x[], int y[]);

