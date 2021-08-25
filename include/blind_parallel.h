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


//�ϳɴ���
big ComposeToBig(BPS_PriParas *private_paras, int num, int plain[]);

//�Դ������м���
int MultiEncrypt(BPS_PriParas *private_paras, big data, CipherText* cipher);

//�������ܲ�������
big MultiDecrypt(BPS_PriParas *private_paras, CipherText* cipher);

//�������ܲ�������
void DecomposeToInt(BPS_PriParas *private_paras, int num, big cipher, int res[]);



//�������෴�� r=-x
void MultiBlindNegify(BPS_PubParas* pub_paras, CipherText* x[], CipherText* r[]);

//�������෴��(���)x=-x
void MultiBlindNegifyInplace(BPS_PubParas* pub_paras, CipherText* x[]);

//ä�ӷ� r=x+y
void MultiBlindAdd(BPS_PubParas* pub_paras, CipherText* x[], CipherText* y[], CipherText* r[]);

//ä�ӷ�(���) x=x+y
void MultiBlindAddInplace(BPS_PubParas* pub_paras, CipherText* x[], CipherText* y[]);

//ä���� r=x-y
void MultiBlindSub(BPS_PubParas* pub_paras, big x, big y, big r);

//ä����(���) x=x-y
void MultiBlindSubInplace(BPS_PubParas* pub_paras, CipherText* x[], CipherText* y[]);

//ä�˷� r=x*y
void MultiBlindMul(BPS_PubParas* pub_paras, CipherText* x[], CipherText* y[], CipherText* r[]);

//ä�˷�(���) x=x*y
void MultiBlindMulInplace(BPS_PubParas* pub_paras, CipherText* x[], CipherText* y[]);

//ä������ r=x^y
void MultiBlindPow(BPS_PubParas* pub_paras, CipherText* x[], int y[], CipherText* r[]);

//ä������(���) x=x^y
void MultiBlindPowInplace(BPS_PubParas* pub_paras, CipherText* x[], int y[]);

//��ä�ӷ� r=x+y
void MultiHalfBlindAdd(BPS_PubParas* pub_paras, CipherText* x[], int y[], CipherText* r[]);

//��ä�ӷ�(���) x=x+y
void MultiHalfBlindAddInplace(BPS_PubParas* pub_paras, CipherText* x[], int y[]);

//��ä���� r=x-y
void MultiHalfBlindSub(BPS_PubParas* pub_paras, CipherText* x[], int y[], CipherText* r[]);

//��ä����(���) x=x-y
void MultiHalfBlindSubInplace(BPS_PubParas* pub_paras, CipherText* x[], int y[]);

//��ä�˷� r=x*y
void MultiHalfBlindMul(BPS_PubParas* pub_paras, CipherText* x[], int y[], CipherText* r[]);

//��ä�˷�(���) x=x*y
void MultiHalfBlindMulInplace(BPS_PubParas* pub_paras, CipherText* x[], int y[]);

