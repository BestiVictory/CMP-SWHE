<<<<<<< f7e2854ca42afeaa1d95e9c337b92b0533d387c9
//#include "blind2.h"
#include "blind.h"
#include "matrix.h"
#include "others.h"
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
#include "test.h"
extern "C" {
#include <miracl.h>
#include <mirdef.h>
#include <stdio.h>
}





//#pragma comment(lib, "cryptlib.lib" )  

using namespace std;

using namespace CryptoPP;

void showMemoryInfo()
{
	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	cout << "**************************************内存使用:";
	cout << pmc.WorkingSetSize / 1000 << "K/" << pmc.PeakWorkingSetSize / 1000 << "K + " << pmc.PagefileUsage / 1000 << "K/" << pmc.PeakPagefileUsage / 1000 << "K" << endl;
}

int showMemoryInfo2()
{
	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	//cout << "**************************************内存使用:";
	//cout << pmc.WorkingSetSize / 1000 << "K/" << pmc.PeakWorkingSetSize / 1000 << "K + " << pmc.PagefileUsage / 1000 << "K/" << pmc.PeakPagefileUsage / 1000 << "K" << endl;
	return pmc.WorkingSetSize ;
}


int test_one() {
	UserKey* uk = new UserKey();
	string u = "233";
	uk->setkey(u);
	BPS_PubParas* pub = new BPS_PubParas();
	BPS_PriParas* pri = new BPS_PriParas();
	int a_size = 10;
	create_BPS_Paras(uk, pub, pri,a_size);

	clock_t encrypt_start, encrypt_end, decrypt_start, decrypt_end;
	clock_t add_start, add_end, sub_start, sub_end, mul_start, mul_end, pow_start, pow_end, neg_start, neg_end;
	clock_t half_add_start, half_add_end, half_sub_start, half_sub_end, half_mul_start, half_mul_end;
	double encrypt_time, decrypt_time, add_time, sub_time, mul_time, pow_time, neg_time, half_add_time, half_sub_time, half_mul_time;
	encrypt_time = 0;
	decrypt_time = 0;
	add_time = 0;
	sub_time = 0;
	mul_time = 0;
	pow_time = 0;
	neg_time = 0;
	half_add_time = 0;
	half_sub_time = 0;
	half_mul_time = 0;

	int jiami = 0;
	int mangjia = 0;
	int jiemi = 0;

	int count = 10;
	for (int i = 0;i < count;i++)
	{
		//cout << "i==" << i << endl;
		//int ming = i;
		//CipherText* mi = new CipherText();
		////加密测试
		//encrypt_start = clock();
		//Encrypt(pri, ming, mi);
		//encrypt_end = clock();
		//encrypt_time += (double)(encrypt_end - encrypt_start) / CLOCKS_PER_SEC;
		
		int ming1 = 12;
		int ming2 = 13;
		CipherText* mi1 = new CipherText();
		CipherText* mi2 = new CipherText();
		encrypt_start = clock();
		int kaishiqian = showMemoryInfo2();
		
		Encrypt(pri, ming1, mi1);
		Encrypt(pri, ming2, mi2);
		encrypt_end = clock();
		encrypt_time += (double)(encrypt_end - encrypt_start) / CLOCKS_PER_SEC;
		int jiamihou = showMemoryInfo2();
		jiami += jiamihou - kaishiqian;
		
		//盲加测试
		add_start = clock();
		BlindAddInplace(pub, mi1, mi2);    //盲加(替代)
		add_end = clock();
		int mangjiahou = showMemoryInfo2();
		add_time += (double)(add_end - add_start) / CLOCKS_PER_SEC;
		mangjia += mangjiahou - jiamihou;

		//解密测试
		decrypt_start = clock();
		Decrypt(pri, mi1);
		decrypt_end = clock();
		int jiemihou = showMemoryInfo2();
		decrypt_time += (double)(decrypt_end - decrypt_start) / CLOCKS_PER_SEC;
		jiemi += jiemihou - mangjiahou;

	}

	cout << "加密平均耗时：" << encrypt_time / count * 1000 << "ms" << endl;
	cout << "解密平均耗时：" << decrypt_time / count * 1000 << "ms" << endl;
	cout << "盲加平均耗时：" << add_time / count * 1000 << "ms" << endl;

	cout << "加密用时：" << encrypt_time / count << "," << "加密内存：" << jiami / count << endl;
	cout << "盲加用时：" << add_time / count << "," << "盲加内存：" << mangjia / count << endl;
	cout << "解密用时：" << decrypt_time / count << "," << "解密内存：" << jiemi / count << endl;

	return 0;
}


int test_time() {
	UserKey* uk = new UserKey();
	string u = "233";
	uk->setkey(u);
	BPS_PubParas* pub = new BPS_PubParas();
	BPS_PriParas* pri = new BPS_PriParas();
	int a_size = 10;
	create_BPS_Paras(uk, pub, pri, a_size);

	clock_t encrypt_start, encrypt_end, decrypt_start, decrypt_end;
	clock_t add_start, add_end, sub_start, sub_end, mul_start, mul_end, pow_start, pow_end, neg_start, neg_end;
	clock_t half_add_start, half_add_end, half_sub_start, half_sub_end, half_mul_start, half_mul_end;
	double encrypt_time, decrypt_time, add_time, sub_time, mul_time, pow_time, neg_time, half_add_time, half_sub_time, half_mul_time;
	encrypt_time = 0;
	decrypt_time = 0;
	add_time = 0;
	sub_time = 0;
	mul_time = 0;
	pow_time = 0;
	neg_time = 0;
	half_add_time = 0;
	half_sub_time = 0;
	half_mul_time = 0;

	int count = 10;
	for (int i = 0;i < count;i++)
	{
		cout << "i==" << i << endl;
		int ming = i;
		CipherText* mi = new CipherText();
		//加密测试
		encrypt_start = clock();
		Encrypt(pri, ming, mi);
		encrypt_end = clock();
		encrypt_time += (double)(encrypt_end - encrypt_start) / CLOCKS_PER_SEC;
		//解密测试
		decrypt_start = clock();
		Decrypt(pri, mi);
		decrypt_end = clock();
		decrypt_time += (double)(decrypt_end - decrypt_start) / CLOCKS_PER_SEC;

		int ming1 = i;
		int ming2 = i + 1;
		CipherText* mi1 = new CipherText();
		CipherText* mi2 = new CipherText();
		Encrypt(pri, ming1, mi1);
		Encrypt(pri, ming2, mi2);
		//盲加测试
		add_start = clock();
		BlindAddInplace(pub, mi1, mi2);    //盲加(替代)
		add_end = clock();
		add_time += (double)(add_end - add_start) / CLOCKS_PER_SEC;
		//盲乘测试
		mul_start = clock();
		BlindAddInplace(pub, mi1, mi2);    //盲乘(替代)
		mul_end = clock();
		mul_time += (double)(mul_end - mul_start) / CLOCKS_PER_SEC;
		//盲幂测试
		pow_start = clock();
		BlindPowInplace(pub, mi1, 3);      //盲幂(替代)
		pow_end = clock();
		pow_time += (double)(pow_end - pow_start) / CLOCKS_PER_SEC;
		//盲减测试
		sub_start = clock();
		BlindSubInplace(pub, mi1, mi2);    //盲减(替代)
		sub_end = clock();
		sub_time += (double)(sub_end - sub_start) / CLOCKS_PER_SEC;
		//半盲加测试
		half_add_start = clock();
		HalfBlindAddInplace(pub, mi1, 3);    //半盲加(替代)
		half_add_end = clock();
		half_add_time += (double)(half_add_end - half_add_start) / CLOCKS_PER_SEC;
		//半盲减测试
		half_sub_start = clock();
		HalfBlindSubInplace(pub, mi1, 3);    //半盲减(替代)
		half_sub_end = clock();
		half_sub_time += (double)(half_sub_end - half_sub_start) / CLOCKS_PER_SEC;
		//半盲乘测试
		half_mul_start = clock();
		HalfBlindMulInplace(pub, mi1, 2);    //半盲乘(替代)
		half_mul_end = clock();
		half_mul_time += (double)(half_mul_end - half_mul_start) / CLOCKS_PER_SEC;
		//盲取反测试
		neg_start = clock();
		BlindNegifyInplace(pub, mi1);      //盲取反(替代)
		neg_end = clock();
		neg_time += (double)(neg_end - neg_start) / CLOCKS_PER_SEC;
	}

	cout << "加密平均耗时：" << encrypt_time / count * 1000 << "ms" << endl;
	cout << "解密平均耗时：" << decrypt_time / count * 1000 << "ms" << endl;
	cout << "盲加平均耗时：" << add_time / count * 1000 << "ms" << endl;
	cout << "盲减平均耗时：" << sub_time / count * 1000 << "ms" << endl;
	cout << "盲乘平均耗时：" << mul_time / count * 1000 << "ms" << endl;
	cout << "盲幂平均耗时：" << pow_time / count * 1000 << "ms" << endl;
	cout << "盲取反平均耗时：" << neg_time / count * 1000 << "ms" << endl;
	cout << "半盲加平均耗时：" << half_add_time / count * 1000 << "ms" << endl;
	cout << "半盲减平均耗时：" << half_sub_time / count * 1000 << "ms" << endl;
	cout << "半盲乘平均耗时：" << half_mul_time / count * 1000 << "ms" << endl;

	return 0;
}

int test_function() {
	UserKey* uk = new UserKey();
	string u = "233";
	uk->setkey(u);
	BPS_PubParas* pub = new BPS_PubParas();
	BPS_PriParas* pri = new BPS_PriParas();
	int a_size = 10;
	create_BPS_Paras(uk, pub, pri, a_size);

	int mingwen0 = 1000000, mingwen1 = 200000, mingwen2 = 50, mingwen3 = 10, mingwen4 = 2;
	//cout << "sid:" << pub->get_sid() << endl;
	CipherText* ct0 = new CipherText();
	CipherText* ct1 = new CipherText();
	CipherText* ct2 = new CipherText();
	CipherText* ct3 = new CipherText();
	CipherText* ct4 = new CipherText();

	CipherText* res = new CipherText();
	CipherText* res1 = new CipherText();
	CipherText* res2 = new CipherText();
	Encrypt(pri, mingwen0, ct0);
	Encrypt(pri, mingwen1, ct1);
	Encrypt(pri, mingwen2, ct2);
	Encrypt(pri, mingwen3, ct3);
	Encrypt(pri, mingwen4, ct4);
	CipherText* ct5 = new CipherText(ct4);

	//BlindAdd(pub, ct3, ct2, res);      //盲加
	//BlindAddInplace(pub, ct2, ct4);    //盲加(替代)
	//BlindSub(pub, ct1, ct2, res);      //盲减
	//BlindSubInplace(pub, ct1, ct2);    //盲减(替代)
	//BlindMul(pub, ct2, ct4, res);      //盲乘
	//BlindMulInplace(pub, ct2, ct4);    //盲乘(替代)
	//BlindPow(pub, ct1, 3, res);        //盲幂
	//BlindPowInplace(pub, ct1, 3);      //盲幂(替代)
	//HalfBlindAdd(pub, ct1, 3, res);    //半盲加
	//HalfBlindAddInplace(pub, ct1, 3);  //半盲加(替代)
	//HalfBlindSub(pub, ct1, 3, res);    //半盲减
	//HalfBlindSubInplace(pub, ct1, 3);  //半盲减(替代)
	//HalfBlindMul(pub, ct1, 10, res);   //半盲乘
	//HalfBlindMulInplace(pub, ct1, 10); //半盲乘(替代)
	//BlindNegify(pub, ct1, res);        //盲取反
	//BlindNegifyInplace(pub, ct1);      //盲取反(替代)
	CipherText* c[3] = { ct2,ct3,ct4 };
	BlindAddMany(pub, 3, c, res);      //盲连加
	//BlindMulMany(pub, 3, c, res);      //盲连乘

	big pdata = Decrypt(pri, res);
	cout << "解密结果为：";
	//cotnum(pdata, stdout);
	int intres = size(pdata);
	cout << intres << endl;

	return 0;
}

int test_memory() {
	clock_t start, encrypt_end, compute_end, decrypt_end;
	double encrypt_time, compute_time, decrypt_time;
	encrypt_time = 0;
	compute_time = 0;
	decrypt_time = 0;
	//showMemoryInfo();
	//cout << "回收所有可回收的内存" << endl;
	//EmptyWorkingSet(GetCurrentProcess());
	//showMemoryInfo();
	//cout << "开始动态分配内存" << endl;

	start = clock();

	UserKey* uk = new UserKey();
	string u = "233";
	uk->setkey(u);
	BPS_PubParas* pub = new BPS_PubParas();
	BPS_PriParas* pri = new BPS_PriParas();
	int a_size = 10;
	create_BPS_Paras(uk, pub, pri, a_size);

	//cout << "sid:" << pub->get_sid() << endl;
	CipherText *c0[24], *c1[24], *c2[24], *c3[24], *tmp[24];
	//for (int i = 0;i < 24;i++) {
	//	c0[i] = new CipherText();
	//	c1[i] = new CipherText();
	//	c2[i] = new CipherText();
	//	c3[i] = new CipherText();
	//	res[i] = new CipherText();
	//	Encrypt(pri, i+1, c0[i]);
	//	Encrypt(pri, i+1, c1[i]);
	//	Encrypt(pri, i+1, c2[i]);
	//	Encrypt(pri, i+1, c3[i]);
	//	cout << "第" << i << "轮加密后内存：" << endl;
	//	showMemoryInfo();

	//	BlindMulInplace(pub, c1[i], c0[i]);    //盲乘(替代)
	//	HalfBlindAddInplace(pub, c0[i], 1);  //半盲加(替代)
	//	HalfBlindMulInplace(pub, c2[i], 2); //半盲乘(替代)

	//	tmp[i] = new CipherText(c1[i]);
	//	cout << "tmp->order=" << tmp[i]->getorder() << endl;

	//	BlindAddInplace(pub, c2[i], tmp[i]);    //盲加(替代)
	//	BlindNegifyInplace(pub, c1[i]);      //盲取反(替代)
	//	BlindMulInplace(pub, c3[i], c2[i]);    //盲乘(替代)
	//	BlindSubInplace(pub, c0[i], c3[i]);    //盲减(替代)

	//	cout << "第" << i << "轮计算后内存：" << endl;
	//	showMemoryInfo();

	//	big pp0 = Decrypt(pri, c0[i]);
	//	big pp1 = Decrypt(pri, c1[i]);
	//	big pp2 = Decrypt(pri, c2[i]);
	//	big pp3 = Decrypt(pri, c3[i]);
	//	cout << "解密结果为：";
	//	cotnum(pp0, stdout);
	//	cotnum(pp1, stdout);
	//	cotnum(pp2, stdout);
	//	cotnum(pp3, stdout);

	//	cout << "第" << i << "轮解密后内存：" << endl;
	//	showMemoryInfo();

	//}
	cout << "开始前内存：" << endl;
	//showMemoryInfo();
	int kaishiqian = showMemoryInfo2();
	for (int i = 0;i < 24;i++) {
		c0[i] = new CipherText();
		c1[i] = new CipherText();
		c2[i] = new CipherText();
		c3[i] = new CipherText();
		Encrypt(pri, i + 1, c0[i]);
		Encrypt(pri, i + 1, c1[i]);
		Encrypt(pri, i + 1, c2[i]);
		Encrypt(pri, i + 1, c3[i]);
	}
	cout << "加密后内存：" << endl;
	//showMemoryInfo();
	int jiamihou = showMemoryInfo2();

	encrypt_end = clock();
	encrypt_time += (double)(encrypt_end - start) / CLOCKS_PER_SEC;
	cout << "加密时间：" << encrypt_time*1000 << "ms" << endl;

	for (int i = 0;i < 24;i++) {
		BlindMulInplace(pub, c1[i], c0[i]);    //盲乘(替代)
		HalfBlindAddInplace(pub, c0[i], 1);  //半盲加(替代)
		HalfBlindMulInplace(pub, c2[i], 2); //半盲乘(替代)

		tmp[i] = new CipherText(c1[i]);


		BlindAddInplace(pub, c2[i], tmp[i]);    //盲加(替代)
		BlindNegifyInplace(pub, c1[i]);      //盲取反(替代)
		BlindMulInplace(pub, c3[i], c2[i]);    //盲乘(替代)
		BlindSubInplace(pub, c3[i], c0[i]);    //盲减(替代)
		//cout << "tmp->order=" << tmp[i]->getorder() << endl;
		//cout << "c0->order=" << c0[i]->getorder() << endl;
		//cout << "c1->order=" << c1[i]->getorder() << endl;
		//cout << "c2->order=" << c2[i]->getorder() << endl;
		//cout << "c3->order=" << c3[i]->getorder() << endl;
	}
	cout << "计算后内存：" << endl;
	//showMemoryInfo();
	int jisuanhou = showMemoryInfo2();

	compute_end = clock();
	compute_time += (double)(compute_end - encrypt_end) / CLOCKS_PER_SEC;
	cout << "计算时间：" << compute_time * 1000 << "ms" << endl;

	for (int i = 0;i < 24;i++) {
		//big pp0 = Decrypt(pri, c0[i]);
		//big pp1 = Decrypt(pri, c1[i]);
		//big pp2 = Decrypt(pri, c2[i]);
		//big pp3 = Decrypt(pri, c3[i]);
		cout << "解密结果为：";
		//int intres0 = size(pp0);
		//int intres1 = size(pp1);
		//int intres2 = size(pp2);
		//int intres3 = size(pp3);
		//cout << intres0 << endl;
		//cout << intres1 << endl;
		//cout << intres2 << endl;
		//cout << intres3 << endl;

		cout << Decrypt2(pri, c0[i]) << endl;
		cout << Decrypt2(pri, c1[i]) << endl;
		cout << Decrypt2(pri, c2[i]) << endl;
		cout << Decrypt2(pri, c3[i]) << endl;

	}
	cout << "解密后内存：" << endl;
	//showMemoryInfo();
	int jiemihou = showMemoryInfo2();

	decrypt_end = clock();
	decrypt_time += (double)(decrypt_end - compute_end) / CLOCKS_PER_SEC;
	cout << "解密时间：" << decrypt_time * 1000 << "ms" << endl;

	cout << "回收所有可回收的内存" << endl;
	EmptyWorkingSet(GetCurrentProcess());
	showMemoryInfo();

	cout << endl;
	cout << endl;
	cout << endl;
	cout << jiamihou - kaishiqian << "," << jisuanhou - kaishiqian << "," << jiemihou - kaishiqian << endl;
	cout << encrypt_time * 1000 << "," << compute_time * 1000 << "," << decrypt_time * 1000 << endl;

	return 0;
}

int test_matrix() {
	UserKey* uk = new UserKey();
	string u = "233";
	uk->setkey(u);
	BPS_PubParas* pub = new BPS_PubParas();
	BPS_PriParas* pri = new BPS_PriParas();
	int a_size = 10;
	create_BPS_Paras(uk, pub, pri, a_size);

	int **aa = new int*[2];
	int **bb = new int*[2];
	int **cc;
	for (int i = 0; i < 2; i++)
	{
		aa[i] = new int[3];
		bb[i] = new int[3];
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0;j < 3;j++) {
			aa[i][j] = i;
			bb[i][j] = i + 2;
		}
	}
	//CipherText*** aaa = new CipherText**();
	//CipherText*** bbb = new CipherText**();
	//CipherText*** ccc = new CipherText**();
	CipherText ***aaa = new CipherText **[2];
	CipherText ***bbb = new CipherText **[2];
	CipherText ***ccc = new CipherText **[2];
	CipherText* ct0 = new CipherText();
	for (int i = 0; i < 2; i++)
	{
		//aaa[i] = new CipherText*();
		//bbb[i] = new CipherText*();
		//ccc[i] = new CipherText*();
		aaa[i] = new CipherText*[3];
		bbb[i] = new CipherText*[3];
		ccc[i] = new CipherText*[3];
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0;j < 3;j++) {
			aaa[i][j] = new CipherText();
			bbb[i][j] = new CipherText();
			ccc[i][j] = new CipherText();
		}
	}

	//cout << "sid:" << pub->get_sid() << endl;
	
	EncryptArray(pri, 2, 3, aa, aaa);
	EncryptArray(pri, 2, 3, bb, bbb);
	HalfBlindMulMatrix(pub, 2, 3, aaa, bb, ccc);
	cc=DecryptArray(pri, 2, 3, ccc);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0;j < 3;j++) {
			cout << "c[" << i << "][" << j << "]=a["<<i<<"]["<<j<<"]+b["<<i<<"]["<<j<<"]="<<aa[i][j]<<"+"<<bb[i][j]<<"="<<cc[i][j] << endl;
		}
	}
	return 0;
}

=======
//#include "blind2.h"
#include "blind.h"
#include "matrix.h"
#include "others.h"
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
#include "test.h"
extern "C" {
#include <miracl.h>
#include <mirdef.h>
#include <stdio.h>
}





//#pragma comment(lib, "cryptlib.lib" )  

using namespace std;

using namespace CryptoPP;

void showMemoryInfo()
{
	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	cout << "**************************************内存使用:";
	cout << pmc.WorkingSetSize / 1000 << "K/" << pmc.PeakWorkingSetSize / 1000 << "K + " << pmc.PagefileUsage / 1000 << "K/" << pmc.PeakPagefileUsage / 1000 << "K" << endl;
}

int showMemoryInfo2()
{
	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	//cout << "**************************************内存使用:";
	//cout << pmc.WorkingSetSize / 1000 << "K/" << pmc.PeakWorkingSetSize / 1000 << "K + " << pmc.PagefileUsage / 1000 << "K/" << pmc.PeakPagefileUsage / 1000 << "K" << endl;
	return pmc.WorkingSetSize ;
}


int test_one() {
	UserKey* uk = new UserKey();
	string u = "233";
	uk->setkey(u);
	BPS_PubParas* pub = new BPS_PubParas();
	BPS_PriParas* pri = new BPS_PriParas();
	int a_size = 10;
	create_BPS_Paras(uk, pub, pri,a_size);

	clock_t encrypt_start, encrypt_end, decrypt_start, decrypt_end;
	clock_t add_start, add_end, sub_start, sub_end, mul_start, mul_end, pow_start, pow_end, neg_start, neg_end;
	clock_t half_add_start, half_add_end, half_sub_start, half_sub_end, half_mul_start, half_mul_end;
	double encrypt_time, decrypt_time, add_time, sub_time, mul_time, pow_time, neg_time, half_add_time, half_sub_time, half_mul_time;
	encrypt_time = 0;
	decrypt_time = 0;
	add_time = 0;
	sub_time = 0;
	mul_time = 0;
	pow_time = 0;
	neg_time = 0;
	half_add_time = 0;
	half_sub_time = 0;
	half_mul_time = 0;

	int jiami = 0;
	int mangjia = 0;
	int jiemi = 0;

	int count = 10;
	for (int i = 0;i < count;i++)
	{
		//cout << "i==" << i << endl;
		//int ming = i;
		//CipherText* mi = new CipherText();
		////加密测试
		//encrypt_start = clock();
		//Encrypt(pri, ming, mi);
		//encrypt_end = clock();
		//encrypt_time += (double)(encrypt_end - encrypt_start) / CLOCKS_PER_SEC;
		
		int ming1 = 12;
		int ming2 = 13;
		CipherText* mi1 = new CipherText();
		CipherText* mi2 = new CipherText();
		encrypt_start = clock();
		int kaishiqian = showMemoryInfo2();
		
		Encrypt(pri, ming1, mi1);
		Encrypt(pri, ming2, mi2);
		encrypt_end = clock();
		encrypt_time += (double)(encrypt_end - encrypt_start) / CLOCKS_PER_SEC;
		int jiamihou = showMemoryInfo2();
		jiami += jiamihou - kaishiqian;
		
		//盲加测试
		add_start = clock();
		BlindAddInplace(pub, mi1, mi2);    //盲加(替代)
		add_end = clock();
		int mangjiahou = showMemoryInfo2();
		add_time += (double)(add_end - add_start) / CLOCKS_PER_SEC;
		mangjia += mangjiahou - jiamihou;

		//解密测试
		decrypt_start = clock();
		Decrypt(pri, mi1);
		decrypt_end = clock();
		int jiemihou = showMemoryInfo2();
		decrypt_time += (double)(decrypt_end - decrypt_start) / CLOCKS_PER_SEC;
		jiemi += jiemihou - mangjiahou;

	}

	cout << "加密平均耗时：" << encrypt_time / count * 1000 << "ms" << endl;
	cout << "解密平均耗时：" << decrypt_time / count * 1000 << "ms" << endl;
	cout << "盲加平均耗时：" << add_time / count * 1000 << "ms" << endl;

	cout << "加密用时：" << encrypt_time / count << "," << "加密内存：" << jiami / count << endl;
	cout << "盲加用时：" << add_time / count << "," << "盲加内存：" << mangjia / count << endl;
	cout << "解密用时：" << decrypt_time / count << "," << "解密内存：" << jiemi / count << endl;

	return 0;
}


int test_time() {
	UserKey* uk = new UserKey();
	string u = "233";
	uk->setkey(u);
	BPS_PubParas* pub = new BPS_PubParas();
	BPS_PriParas* pri = new BPS_PriParas();
	int a_size = 10;
	create_BPS_Paras(uk, pub, pri, a_size);

	clock_t encrypt_start, encrypt_end, decrypt_start, decrypt_end;
	clock_t add_start, add_end, sub_start, sub_end, mul_start, mul_end, pow_start, pow_end, neg_start, neg_end;
	clock_t half_add_start, half_add_end, half_sub_start, half_sub_end, half_mul_start, half_mul_end;
	double encrypt_time, decrypt_time, add_time, sub_time, mul_time, pow_time, neg_time, half_add_time, half_sub_time, half_mul_time;
	encrypt_time = 0;
	decrypt_time = 0;
	add_time = 0;
	sub_time = 0;
	mul_time = 0;
	pow_time = 0;
	neg_time = 0;
	half_add_time = 0;
	half_sub_time = 0;
	half_mul_time = 0;

	int count = 10;
	for (int i = 0;i < count;i++)
	{
		cout << "i==" << i << endl;
		int ming = i;
		CipherText* mi = new CipherText();
		//加密测试
		encrypt_start = clock();
		Encrypt(pri, ming, mi);
		encrypt_end = clock();
		encrypt_time += (double)(encrypt_end - encrypt_start) / CLOCKS_PER_SEC;
		//解密测试
		decrypt_start = clock();
		Decrypt(pri, mi);
		decrypt_end = clock();
		decrypt_time += (double)(decrypt_end - decrypt_start) / CLOCKS_PER_SEC;

		int ming1 = i;
		int ming2 = i + 1;
		CipherText* mi1 = new CipherText();
		CipherText* mi2 = new CipherText();
		Encrypt(pri, ming1, mi1);
		Encrypt(pri, ming2, mi2);
		//盲加测试
		add_start = clock();
		BlindAddInplace(pub, mi1, mi2);    //盲加(替代)
		add_end = clock();
		add_time += (double)(add_end - add_start) / CLOCKS_PER_SEC;
		//盲乘测试
		mul_start = clock();
		BlindAddInplace(pub, mi1, mi2);    //盲乘(替代)
		mul_end = clock();
		mul_time += (double)(mul_end - mul_start) / CLOCKS_PER_SEC;
		//盲幂测试
		pow_start = clock();
		BlindPowInplace(pub, mi1, 3);      //盲幂(替代)
		pow_end = clock();
		pow_time += (double)(pow_end - pow_start) / CLOCKS_PER_SEC;
		//盲减测试
		sub_start = clock();
		BlindSubInplace(pub, mi1, mi2);    //盲减(替代)
		sub_end = clock();
		sub_time += (double)(sub_end - sub_start) / CLOCKS_PER_SEC;
		//半盲加测试
		half_add_start = clock();
		HalfBlindAddInplace(pub, mi1, 3);    //半盲加(替代)
		half_add_end = clock();
		half_add_time += (double)(half_add_end - half_add_start) / CLOCKS_PER_SEC;
		//半盲减测试
		half_sub_start = clock();
		HalfBlindSubInplace(pub, mi1, 3);    //半盲减(替代)
		half_sub_end = clock();
		half_sub_time += (double)(half_sub_end - half_sub_start) / CLOCKS_PER_SEC;
		//半盲乘测试
		half_mul_start = clock();
		HalfBlindMulInplace(pub, mi1, 2);    //半盲乘(替代)
		half_mul_end = clock();
		half_mul_time += (double)(half_mul_end - half_mul_start) / CLOCKS_PER_SEC;
		//盲取反测试
		neg_start = clock();
		BlindNegifyInplace(pub, mi1);      //盲取反(替代)
		neg_end = clock();
		neg_time += (double)(neg_end - neg_start) / CLOCKS_PER_SEC;
	}

	cout << "加密平均耗时：" << encrypt_time / count * 1000 << "ms" << endl;
	cout << "解密平均耗时：" << decrypt_time / count * 1000 << "ms" << endl;
	cout << "盲加平均耗时：" << add_time / count * 1000 << "ms" << endl;
	cout << "盲减平均耗时：" << sub_time / count * 1000 << "ms" << endl;
	cout << "盲乘平均耗时：" << mul_time / count * 1000 << "ms" << endl;
	cout << "盲幂平均耗时：" << pow_time / count * 1000 << "ms" << endl;
	cout << "盲取反平均耗时：" << neg_time / count * 1000 << "ms" << endl;
	cout << "半盲加平均耗时：" << half_add_time / count * 1000 << "ms" << endl;
	cout << "半盲减平均耗时：" << half_sub_time / count * 1000 << "ms" << endl;
	cout << "半盲乘平均耗时：" << half_mul_time / count * 1000 << "ms" << endl;

	return 0;
}

int test_function() {
	UserKey* uk = new UserKey();
	string u = "233";
	uk->setkey(u);
	BPS_PubParas* pub = new BPS_PubParas();
	BPS_PriParas* pri = new BPS_PriParas();
	int a_size = 10;
	create_BPS_Paras(uk, pub, pri, a_size);

	int mingwen0 = 1000000, mingwen1 = 200000, mingwen2 = 50, mingwen3 = 10, mingwen4 = 2;
	//cout << "sid:" << pub->get_sid() << endl;
	CipherText* ct0 = new CipherText();
	CipherText* ct1 = new CipherText();
	CipherText* ct2 = new CipherText();
	CipherText* ct3 = new CipherText();
	CipherText* ct4 = new CipherText();

	CipherText* res = new CipherText();
	CipherText* res1 = new CipherText();
	CipherText* res2 = new CipherText();
	Encrypt(pri, mingwen0, ct0);
	Encrypt(pri, mingwen1, ct1);
	Encrypt(pri, mingwen2, ct2);
	Encrypt(pri, mingwen3, ct3);
	Encrypt(pri, mingwen4, ct4);
	CipherText* ct5 = new CipherText(ct4);

	//BlindAdd(pub, ct3, ct2, res);      //盲加
	//BlindAddInplace(pub, ct2, ct4);    //盲加(替代)
	//BlindSub(pub, ct1, ct2, res);      //盲减
	//BlindSubInplace(pub, ct1, ct2);    //盲减(替代)
	//BlindMul(pub, ct2, ct4, res);      //盲乘
	//BlindMulInplace(pub, ct2, ct4);    //盲乘(替代)
	//BlindPow(pub, ct1, 3, res);        //盲幂
	//BlindPowInplace(pub, ct1, 3);      //盲幂(替代)
	//HalfBlindAdd(pub, ct1, 3, res);    //半盲加
	//HalfBlindAddInplace(pub, ct1, 3);  //半盲加(替代)
	//HalfBlindSub(pub, ct1, 3, res);    //半盲减
	//HalfBlindSubInplace(pub, ct1, 3);  //半盲减(替代)
	//HalfBlindMul(pub, ct1, 10, res);   //半盲乘
	//HalfBlindMulInplace(pub, ct1, 10); //半盲乘(替代)
	//BlindNegify(pub, ct1, res);        //盲取反
	//BlindNegifyInplace(pub, ct1);      //盲取反(替代)
	CipherText* c[3] = { ct2,ct3,ct4 };
	BlindAddMany(pub, 3, c, res);      //盲连加
	//BlindMulMany(pub, 3, c, res);      //盲连乘

	big pdata = Decrypt(pri, res);
	cout << "解密结果为：";
	//cotnum(pdata, stdout);
	int intres = size(pdata);
	cout << intres << endl;

	return 0;
}

int test_memory() {
	clock_t start, encrypt_end, compute_end, decrypt_end;
	double encrypt_time, compute_time, decrypt_time;
	encrypt_time = 0;
	compute_time = 0;
	decrypt_time = 0;
	//showMemoryInfo();
	//cout << "回收所有可回收的内存" << endl;
	//EmptyWorkingSet(GetCurrentProcess());
	//showMemoryInfo();
	//cout << "开始动态分配内存" << endl;

	start = clock();

	UserKey* uk = new UserKey();
	string u = "233";
	uk->setkey(u);
	BPS_PubParas* pub = new BPS_PubParas();
	BPS_PriParas* pri = new BPS_PriParas();
	int a_size = 10;
	create_BPS_Paras(uk, pub, pri, a_size);

	//cout << "sid:" << pub->get_sid() << endl;
	CipherText *c0[24], *c1[24], *c2[24], *c3[24], *tmp[24];
	//for (int i = 0;i < 24;i++) {
	//	c0[i] = new CipherText();
	//	c1[i] = new CipherText();
	//	c2[i] = new CipherText();
	//	c3[i] = new CipherText();
	//	res[i] = new CipherText();
	//	Encrypt(pri, i+1, c0[i]);
	//	Encrypt(pri, i+1, c1[i]);
	//	Encrypt(pri, i+1, c2[i]);
	//	Encrypt(pri, i+1, c3[i]);
	//	cout << "第" << i << "轮加密后内存：" << endl;
	//	showMemoryInfo();

	//	BlindMulInplace(pub, c1[i], c0[i]);    //盲乘(替代)
	//	HalfBlindAddInplace(pub, c0[i], 1);  //半盲加(替代)
	//	HalfBlindMulInplace(pub, c2[i], 2); //半盲乘(替代)

	//	tmp[i] = new CipherText(c1[i]);
	//	cout << "tmp->order=" << tmp[i]->getorder() << endl;

	//	BlindAddInplace(pub, c2[i], tmp[i]);    //盲加(替代)
	//	BlindNegifyInplace(pub, c1[i]);      //盲取反(替代)
	//	BlindMulInplace(pub, c3[i], c2[i]);    //盲乘(替代)
	//	BlindSubInplace(pub, c0[i], c3[i]);    //盲减(替代)

	//	cout << "第" << i << "轮计算后内存：" << endl;
	//	showMemoryInfo();

	//	big pp0 = Decrypt(pri, c0[i]);
	//	big pp1 = Decrypt(pri, c1[i]);
	//	big pp2 = Decrypt(pri, c2[i]);
	//	big pp3 = Decrypt(pri, c3[i]);
	//	cout << "解密结果为：";
	//	cotnum(pp0, stdout);
	//	cotnum(pp1, stdout);
	//	cotnum(pp2, stdout);
	//	cotnum(pp3, stdout);

	//	cout << "第" << i << "轮解密后内存：" << endl;
	//	showMemoryInfo();

	//}
	cout << "开始前内存：" << endl;
	//showMemoryInfo();
	int kaishiqian = showMemoryInfo2();
	for (int i = 0;i < 24;i++) {
		c0[i] = new CipherText();
		c1[i] = new CipherText();
		c2[i] = new CipherText();
		c3[i] = new CipherText();
		Encrypt(pri, i + 1, c0[i]);
		Encrypt(pri, i + 1, c1[i]);
		Encrypt(pri, i + 1, c2[i]);
		Encrypt(pri, i + 1, c3[i]);
	}
	cout << "加密后内存：" << endl;
	//showMemoryInfo();
	int jiamihou = showMemoryInfo2();

	encrypt_end = clock();
	encrypt_time += (double)(encrypt_end - start) / CLOCKS_PER_SEC;
	cout << "加密时间：" << encrypt_time*1000 << "ms" << endl;

	for (int i = 0;i < 24;i++) {
		BlindMulInplace(pub, c1[i], c0[i]);    //盲乘(替代)
		HalfBlindAddInplace(pub, c0[i], 1);  //半盲加(替代)
		HalfBlindMulInplace(pub, c2[i], 2); //半盲乘(替代)

		tmp[i] = new CipherText(c1[i]);


		BlindAddInplace(pub, c2[i], tmp[i]);    //盲加(替代)
		BlindNegifyInplace(pub, c1[i]);      //盲取反(替代)
		BlindMulInplace(pub, c3[i], c2[i]);    //盲乘(替代)
		BlindSubInplace(pub, c3[i], c0[i]);    //盲减(替代)
		//cout << "tmp->order=" << tmp[i]->getorder() << endl;
		//cout << "c0->order=" << c0[i]->getorder() << endl;
		//cout << "c1->order=" << c1[i]->getorder() << endl;
		//cout << "c2->order=" << c2[i]->getorder() << endl;
		//cout << "c3->order=" << c3[i]->getorder() << endl;
	}
	cout << "计算后内存：" << endl;
	//showMemoryInfo();
	int jisuanhou = showMemoryInfo2();

	compute_end = clock();
	compute_time += (double)(compute_end - encrypt_end) / CLOCKS_PER_SEC;
	cout << "计算时间：" << compute_time * 1000 << "ms" << endl;

	for (int i = 0;i < 24;i++) {
		//big pp0 = Decrypt(pri, c0[i]);
		//big pp1 = Decrypt(pri, c1[i]);
		//big pp2 = Decrypt(pri, c2[i]);
		//big pp3 = Decrypt(pri, c3[i]);
		cout << "解密结果为：";
		//int intres0 = size(pp0);
		//int intres1 = size(pp1);
		//int intres2 = size(pp2);
		//int intres3 = size(pp3);
		//cout << intres0 << endl;
		//cout << intres1 << endl;
		//cout << intres2 << endl;
		//cout << intres3 << endl;

		cout << Decrypt2(pri, c0[i]) << endl;
		cout << Decrypt2(pri, c1[i]) << endl;
		cout << Decrypt2(pri, c2[i]) << endl;
		cout << Decrypt2(pri, c3[i]) << endl;

	}
	cout << "解密后内存：" << endl;
	//showMemoryInfo();
	int jiemihou = showMemoryInfo2();

	decrypt_end = clock();
	decrypt_time += (double)(decrypt_end - compute_end) / CLOCKS_PER_SEC;
	cout << "解密时间：" << decrypt_time * 1000 << "ms" << endl;

	cout << "回收所有可回收的内存" << endl;
	EmptyWorkingSet(GetCurrentProcess());
	showMemoryInfo();

	cout << endl;
	cout << endl;
	cout << endl;
	cout << jiamihou - kaishiqian << "," << jisuanhou - kaishiqian << "," << jiemihou - kaishiqian << endl;
	cout << encrypt_time * 1000 << "," << compute_time * 1000 << "," << decrypt_time * 1000 << endl;

	return 0;
}

int test_matrix() {
	UserKey* uk = new UserKey();
	string u = "233";
	uk->setkey(u);
	BPS_PubParas* pub = new BPS_PubParas();
	BPS_PriParas* pri = new BPS_PriParas();
	int a_size = 10;
	create_BPS_Paras(uk, pub, pri, a_size);

	int **aa = new int*[2];
	int **bb = new int*[2];
	int **cc;
	for (int i = 0; i < 2; i++)
	{
		aa[i] = new int[3];
		bb[i] = new int[3];
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0;j < 3;j++) {
			aa[i][j] = i;
			bb[i][j] = i + 2;
		}
	}
	//CipherText*** aaa = new CipherText**();
	//CipherText*** bbb = new CipherText**();
	//CipherText*** ccc = new CipherText**();
	CipherText ***aaa = new CipherText **[2];
	CipherText ***bbb = new CipherText **[2];
	CipherText ***ccc = new CipherText **[2];
	CipherText* ct0 = new CipherText();
	for (int i = 0; i < 2; i++)
	{
		//aaa[i] = new CipherText*();
		//bbb[i] = new CipherText*();
		//ccc[i] = new CipherText*();
		aaa[i] = new CipherText*[3];
		bbb[i] = new CipherText*[3];
		ccc[i] = new CipherText*[3];
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0;j < 3;j++) {
			aaa[i][j] = new CipherText();
			bbb[i][j] = new CipherText();
			ccc[i][j] = new CipherText();
		}
	}

	//cout << "sid:" << pub->get_sid() << endl;
	
	EncryptArray(pri, 2, 3, aa, aaa);
	EncryptArray(pri, 2, 3, bb, bbb);
	HalfBlindMulMatrix(pub, 2, 3, aaa, bb, ccc);
	cc=DecryptArray(pri, 2, 3, ccc);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0;j < 3;j++) {
			cout << "c[" << i << "][" << j << "]=a["<<i<<"]["<<j<<"]+b["<<i<<"]["<<j<<"]="<<aa[i][j]<<"+"<<bb[i][j]<<"="<<cc[i][j] << endl;
		}
	}
	return 0;
}

>>>>>>> first commit
