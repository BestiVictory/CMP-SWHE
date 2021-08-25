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
	cout << "**************************************�ڴ�ʹ��:";
	cout << pmc.WorkingSetSize / 1000 << "K/" << pmc.PeakWorkingSetSize / 1000 << "K + " << pmc.PagefileUsage / 1000 << "K/" << pmc.PeakPagefileUsage / 1000 << "K" << endl;
}

int showMemoryInfo2()
{
	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	//cout << "**************************************�ڴ�ʹ��:";
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
		////���ܲ���
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
		
		//ä�Ӳ���
		add_start = clock();
		BlindAddInplace(pub, mi1, mi2);    //ä��(���)
		add_end = clock();
		int mangjiahou = showMemoryInfo2();
		add_time += (double)(add_end - add_start) / CLOCKS_PER_SEC;
		mangjia += mangjiahou - jiamihou;

		//���ܲ���
		decrypt_start = clock();
		Decrypt(pri, mi1);
		decrypt_end = clock();
		int jiemihou = showMemoryInfo2();
		decrypt_time += (double)(decrypt_end - decrypt_start) / CLOCKS_PER_SEC;
		jiemi += jiemihou - mangjiahou;

	}

	cout << "����ƽ����ʱ��" << encrypt_time / count * 1000 << "ms" << endl;
	cout << "����ƽ����ʱ��" << decrypt_time / count * 1000 << "ms" << endl;
	cout << "ä��ƽ����ʱ��" << add_time / count * 1000 << "ms" << endl;

	cout << "������ʱ��" << encrypt_time / count << "," << "�����ڴ棺" << jiami / count << endl;
	cout << "ä����ʱ��" << add_time / count << "," << "ä���ڴ棺" << mangjia / count << endl;
	cout << "������ʱ��" << decrypt_time / count << "," << "�����ڴ棺" << jiemi / count << endl;

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
		//���ܲ���
		encrypt_start = clock();
		Encrypt(pri, ming, mi);
		encrypt_end = clock();
		encrypt_time += (double)(encrypt_end - encrypt_start) / CLOCKS_PER_SEC;
		//���ܲ���
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
		//ä�Ӳ���
		add_start = clock();
		BlindAddInplace(pub, mi1, mi2);    //ä��(���)
		add_end = clock();
		add_time += (double)(add_end - add_start) / CLOCKS_PER_SEC;
		//ä�˲���
		mul_start = clock();
		BlindAddInplace(pub, mi1, mi2);    //ä��(���)
		mul_end = clock();
		mul_time += (double)(mul_end - mul_start) / CLOCKS_PER_SEC;
		//ä�ݲ���
		pow_start = clock();
		BlindPowInplace(pub, mi1, 3);      //ä��(���)
		pow_end = clock();
		pow_time += (double)(pow_end - pow_start) / CLOCKS_PER_SEC;
		//ä������
		sub_start = clock();
		BlindSubInplace(pub, mi1, mi2);    //ä��(���)
		sub_end = clock();
		sub_time += (double)(sub_end - sub_start) / CLOCKS_PER_SEC;
		//��ä�Ӳ���
		half_add_start = clock();
		HalfBlindAddInplace(pub, mi1, 3);    //��ä��(���)
		half_add_end = clock();
		half_add_time += (double)(half_add_end - half_add_start) / CLOCKS_PER_SEC;
		//��ä������
		half_sub_start = clock();
		HalfBlindSubInplace(pub, mi1, 3);    //��ä��(���)
		half_sub_end = clock();
		half_sub_time += (double)(half_sub_end - half_sub_start) / CLOCKS_PER_SEC;
		//��ä�˲���
		half_mul_start = clock();
		HalfBlindMulInplace(pub, mi1, 2);    //��ä��(���)
		half_mul_end = clock();
		half_mul_time += (double)(half_mul_end - half_mul_start) / CLOCKS_PER_SEC;
		//äȡ������
		neg_start = clock();
		BlindNegifyInplace(pub, mi1);      //äȡ��(���)
		neg_end = clock();
		neg_time += (double)(neg_end - neg_start) / CLOCKS_PER_SEC;
	}

	cout << "����ƽ����ʱ��" << encrypt_time / count * 1000 << "ms" << endl;
	cout << "����ƽ����ʱ��" << decrypt_time / count * 1000 << "ms" << endl;
	cout << "ä��ƽ����ʱ��" << add_time / count * 1000 << "ms" << endl;
	cout << "ä��ƽ����ʱ��" << sub_time / count * 1000 << "ms" << endl;
	cout << "ä��ƽ����ʱ��" << mul_time / count * 1000 << "ms" << endl;
	cout << "ä��ƽ����ʱ��" << pow_time / count * 1000 << "ms" << endl;
	cout << "äȡ��ƽ����ʱ��" << neg_time / count * 1000 << "ms" << endl;
	cout << "��ä��ƽ����ʱ��" << half_add_time / count * 1000 << "ms" << endl;
	cout << "��ä��ƽ����ʱ��" << half_sub_time / count * 1000 << "ms" << endl;
	cout << "��ä��ƽ����ʱ��" << half_mul_time / count * 1000 << "ms" << endl;

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

	//BlindAdd(pub, ct3, ct2, res);      //ä��
	//BlindAddInplace(pub, ct2, ct4);    //ä��(���)
	//BlindSub(pub, ct1, ct2, res);      //ä��
	//BlindSubInplace(pub, ct1, ct2);    //ä��(���)
	//BlindMul(pub, ct2, ct4, res);      //ä��
	//BlindMulInplace(pub, ct2, ct4);    //ä��(���)
	//BlindPow(pub, ct1, 3, res);        //ä��
	//BlindPowInplace(pub, ct1, 3);      //ä��(���)
	//HalfBlindAdd(pub, ct1, 3, res);    //��ä��
	//HalfBlindAddInplace(pub, ct1, 3);  //��ä��(���)
	//HalfBlindSub(pub, ct1, 3, res);    //��ä��
	//HalfBlindSubInplace(pub, ct1, 3);  //��ä��(���)
	//HalfBlindMul(pub, ct1, 10, res);   //��ä��
	//HalfBlindMulInplace(pub, ct1, 10); //��ä��(���)
	//BlindNegify(pub, ct1, res);        //äȡ��
	//BlindNegifyInplace(pub, ct1);      //äȡ��(���)
	CipherText* c[3] = { ct2,ct3,ct4 };
	BlindAddMany(pub, 3, c, res);      //ä����
	//BlindMulMany(pub, 3, c, res);      //ä����

	big pdata = Decrypt(pri, res);
	cout << "���ܽ��Ϊ��";
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
	//cout << "�������пɻ��յ��ڴ�" << endl;
	//EmptyWorkingSet(GetCurrentProcess());
	//showMemoryInfo();
	//cout << "��ʼ��̬�����ڴ�" << endl;

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
	//	cout << "��" << i << "�ּ��ܺ��ڴ棺" << endl;
	//	showMemoryInfo();

	//	BlindMulInplace(pub, c1[i], c0[i]);    //ä��(���)
	//	HalfBlindAddInplace(pub, c0[i], 1);  //��ä��(���)
	//	HalfBlindMulInplace(pub, c2[i], 2); //��ä��(���)

	//	tmp[i] = new CipherText(c1[i]);
	//	cout << "tmp->order=" << tmp[i]->getorder() << endl;

	//	BlindAddInplace(pub, c2[i], tmp[i]);    //ä��(���)
	//	BlindNegifyInplace(pub, c1[i]);      //äȡ��(���)
	//	BlindMulInplace(pub, c3[i], c2[i]);    //ä��(���)
	//	BlindSubInplace(pub, c0[i], c3[i]);    //ä��(���)

	//	cout << "��" << i << "�ּ�����ڴ棺" << endl;
	//	showMemoryInfo();

	//	big pp0 = Decrypt(pri, c0[i]);
	//	big pp1 = Decrypt(pri, c1[i]);
	//	big pp2 = Decrypt(pri, c2[i]);
	//	big pp3 = Decrypt(pri, c3[i]);
	//	cout << "���ܽ��Ϊ��";
	//	cotnum(pp0, stdout);
	//	cotnum(pp1, stdout);
	//	cotnum(pp2, stdout);
	//	cotnum(pp3, stdout);

	//	cout << "��" << i << "�ֽ��ܺ��ڴ棺" << endl;
	//	showMemoryInfo();

	//}
	cout << "��ʼǰ�ڴ棺" << endl;
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
	cout << "���ܺ��ڴ棺" << endl;
	//showMemoryInfo();
	int jiamihou = showMemoryInfo2();

	encrypt_end = clock();
	encrypt_time += (double)(encrypt_end - start) / CLOCKS_PER_SEC;
	cout << "����ʱ�䣺" << encrypt_time*1000 << "ms" << endl;

	for (int i = 0;i < 24;i++) {
		BlindMulInplace(pub, c1[i], c0[i]);    //ä��(���)
		HalfBlindAddInplace(pub, c0[i], 1);  //��ä��(���)
		HalfBlindMulInplace(pub, c2[i], 2); //��ä��(���)

		tmp[i] = new CipherText(c1[i]);


		BlindAddInplace(pub, c2[i], tmp[i]);    //ä��(���)
		BlindNegifyInplace(pub, c1[i]);      //äȡ��(���)
		BlindMulInplace(pub, c3[i], c2[i]);    //ä��(���)
		BlindSubInplace(pub, c3[i], c0[i]);    //ä��(���)
		//cout << "tmp->order=" << tmp[i]->getorder() << endl;
		//cout << "c0->order=" << c0[i]->getorder() << endl;
		//cout << "c1->order=" << c1[i]->getorder() << endl;
		//cout << "c2->order=" << c2[i]->getorder() << endl;
		//cout << "c3->order=" << c3[i]->getorder() << endl;
	}
	cout << "������ڴ棺" << endl;
	//showMemoryInfo();
	int jisuanhou = showMemoryInfo2();

	compute_end = clock();
	compute_time += (double)(compute_end - encrypt_end) / CLOCKS_PER_SEC;
	cout << "����ʱ�䣺" << compute_time * 1000 << "ms" << endl;

	for (int i = 0;i < 24;i++) {
		//big pp0 = Decrypt(pri, c0[i]);
		//big pp1 = Decrypt(pri, c1[i]);
		//big pp2 = Decrypt(pri, c2[i]);
		//big pp3 = Decrypt(pri, c3[i]);
		cout << "���ܽ��Ϊ��";
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
	cout << "���ܺ��ڴ棺" << endl;
	//showMemoryInfo();
	int jiemihou = showMemoryInfo2();

	decrypt_end = clock();
	decrypt_time += (double)(decrypt_end - compute_end) / CLOCKS_PER_SEC;
	cout << "����ʱ�䣺" << decrypt_time * 1000 << "ms" << endl;

	cout << "�������пɻ��յ��ڴ�" << endl;
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
	cout << "**************************************�ڴ�ʹ��:";
	cout << pmc.WorkingSetSize / 1000 << "K/" << pmc.PeakWorkingSetSize / 1000 << "K + " << pmc.PagefileUsage / 1000 << "K/" << pmc.PeakPagefileUsage / 1000 << "K" << endl;
}

int showMemoryInfo2()
{
	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	//cout << "**************************************�ڴ�ʹ��:";
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
		////���ܲ���
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
		
		//ä�Ӳ���
		add_start = clock();
		BlindAddInplace(pub, mi1, mi2);    //ä��(���)
		add_end = clock();
		int mangjiahou = showMemoryInfo2();
		add_time += (double)(add_end - add_start) / CLOCKS_PER_SEC;
		mangjia += mangjiahou - jiamihou;

		//���ܲ���
		decrypt_start = clock();
		Decrypt(pri, mi1);
		decrypt_end = clock();
		int jiemihou = showMemoryInfo2();
		decrypt_time += (double)(decrypt_end - decrypt_start) / CLOCKS_PER_SEC;
		jiemi += jiemihou - mangjiahou;

	}

	cout << "����ƽ����ʱ��" << encrypt_time / count * 1000 << "ms" << endl;
	cout << "����ƽ����ʱ��" << decrypt_time / count * 1000 << "ms" << endl;
	cout << "ä��ƽ����ʱ��" << add_time / count * 1000 << "ms" << endl;

	cout << "������ʱ��" << encrypt_time / count << "," << "�����ڴ棺" << jiami / count << endl;
	cout << "ä����ʱ��" << add_time / count << "," << "ä���ڴ棺" << mangjia / count << endl;
	cout << "������ʱ��" << decrypt_time / count << "," << "�����ڴ棺" << jiemi / count << endl;

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
		//���ܲ���
		encrypt_start = clock();
		Encrypt(pri, ming, mi);
		encrypt_end = clock();
		encrypt_time += (double)(encrypt_end - encrypt_start) / CLOCKS_PER_SEC;
		//���ܲ���
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
		//ä�Ӳ���
		add_start = clock();
		BlindAddInplace(pub, mi1, mi2);    //ä��(���)
		add_end = clock();
		add_time += (double)(add_end - add_start) / CLOCKS_PER_SEC;
		//ä�˲���
		mul_start = clock();
		BlindAddInplace(pub, mi1, mi2);    //ä��(���)
		mul_end = clock();
		mul_time += (double)(mul_end - mul_start) / CLOCKS_PER_SEC;
		//ä�ݲ���
		pow_start = clock();
		BlindPowInplace(pub, mi1, 3);      //ä��(���)
		pow_end = clock();
		pow_time += (double)(pow_end - pow_start) / CLOCKS_PER_SEC;
		//ä������
		sub_start = clock();
		BlindSubInplace(pub, mi1, mi2);    //ä��(���)
		sub_end = clock();
		sub_time += (double)(sub_end - sub_start) / CLOCKS_PER_SEC;
		//��ä�Ӳ���
		half_add_start = clock();
		HalfBlindAddInplace(pub, mi1, 3);    //��ä��(���)
		half_add_end = clock();
		half_add_time += (double)(half_add_end - half_add_start) / CLOCKS_PER_SEC;
		//��ä������
		half_sub_start = clock();
		HalfBlindSubInplace(pub, mi1, 3);    //��ä��(���)
		half_sub_end = clock();
		half_sub_time += (double)(half_sub_end - half_sub_start) / CLOCKS_PER_SEC;
		//��ä�˲���
		half_mul_start = clock();
		HalfBlindMulInplace(pub, mi1, 2);    //��ä��(���)
		half_mul_end = clock();
		half_mul_time += (double)(half_mul_end - half_mul_start) / CLOCKS_PER_SEC;
		//äȡ������
		neg_start = clock();
		BlindNegifyInplace(pub, mi1);      //äȡ��(���)
		neg_end = clock();
		neg_time += (double)(neg_end - neg_start) / CLOCKS_PER_SEC;
	}

	cout << "����ƽ����ʱ��" << encrypt_time / count * 1000 << "ms" << endl;
	cout << "����ƽ����ʱ��" << decrypt_time / count * 1000 << "ms" << endl;
	cout << "ä��ƽ����ʱ��" << add_time / count * 1000 << "ms" << endl;
	cout << "ä��ƽ����ʱ��" << sub_time / count * 1000 << "ms" << endl;
	cout << "ä��ƽ����ʱ��" << mul_time / count * 1000 << "ms" << endl;
	cout << "ä��ƽ����ʱ��" << pow_time / count * 1000 << "ms" << endl;
	cout << "äȡ��ƽ����ʱ��" << neg_time / count * 1000 << "ms" << endl;
	cout << "��ä��ƽ����ʱ��" << half_add_time / count * 1000 << "ms" << endl;
	cout << "��ä��ƽ����ʱ��" << half_sub_time / count * 1000 << "ms" << endl;
	cout << "��ä��ƽ����ʱ��" << half_mul_time / count * 1000 << "ms" << endl;

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

	//BlindAdd(pub, ct3, ct2, res);      //ä��
	//BlindAddInplace(pub, ct2, ct4);    //ä��(���)
	//BlindSub(pub, ct1, ct2, res);      //ä��
	//BlindSubInplace(pub, ct1, ct2);    //ä��(���)
	//BlindMul(pub, ct2, ct4, res);      //ä��
	//BlindMulInplace(pub, ct2, ct4);    //ä��(���)
	//BlindPow(pub, ct1, 3, res);        //ä��
	//BlindPowInplace(pub, ct1, 3);      //ä��(���)
	//HalfBlindAdd(pub, ct1, 3, res);    //��ä��
	//HalfBlindAddInplace(pub, ct1, 3);  //��ä��(���)
	//HalfBlindSub(pub, ct1, 3, res);    //��ä��
	//HalfBlindSubInplace(pub, ct1, 3);  //��ä��(���)
	//HalfBlindMul(pub, ct1, 10, res);   //��ä��
	//HalfBlindMulInplace(pub, ct1, 10); //��ä��(���)
	//BlindNegify(pub, ct1, res);        //äȡ��
	//BlindNegifyInplace(pub, ct1);      //äȡ��(���)
	CipherText* c[3] = { ct2,ct3,ct4 };
	BlindAddMany(pub, 3, c, res);      //ä����
	//BlindMulMany(pub, 3, c, res);      //ä����

	big pdata = Decrypt(pri, res);
	cout << "���ܽ��Ϊ��";
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
	//cout << "�������пɻ��յ��ڴ�" << endl;
	//EmptyWorkingSet(GetCurrentProcess());
	//showMemoryInfo();
	//cout << "��ʼ��̬�����ڴ�" << endl;

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
	//	cout << "��" << i << "�ּ��ܺ��ڴ棺" << endl;
	//	showMemoryInfo();

	//	BlindMulInplace(pub, c1[i], c0[i]);    //ä��(���)
	//	HalfBlindAddInplace(pub, c0[i], 1);  //��ä��(���)
	//	HalfBlindMulInplace(pub, c2[i], 2); //��ä��(���)

	//	tmp[i] = new CipherText(c1[i]);
	//	cout << "tmp->order=" << tmp[i]->getorder() << endl;

	//	BlindAddInplace(pub, c2[i], tmp[i]);    //ä��(���)
	//	BlindNegifyInplace(pub, c1[i]);      //äȡ��(���)
	//	BlindMulInplace(pub, c3[i], c2[i]);    //ä��(���)
	//	BlindSubInplace(pub, c0[i], c3[i]);    //ä��(���)

	//	cout << "��" << i << "�ּ�����ڴ棺" << endl;
	//	showMemoryInfo();

	//	big pp0 = Decrypt(pri, c0[i]);
	//	big pp1 = Decrypt(pri, c1[i]);
	//	big pp2 = Decrypt(pri, c2[i]);
	//	big pp3 = Decrypt(pri, c3[i]);
	//	cout << "���ܽ��Ϊ��";
	//	cotnum(pp0, stdout);
	//	cotnum(pp1, stdout);
	//	cotnum(pp2, stdout);
	//	cotnum(pp3, stdout);

	//	cout << "��" << i << "�ֽ��ܺ��ڴ棺" << endl;
	//	showMemoryInfo();

	//}
	cout << "��ʼǰ�ڴ棺" << endl;
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
	cout << "���ܺ��ڴ棺" << endl;
	//showMemoryInfo();
	int jiamihou = showMemoryInfo2();

	encrypt_end = clock();
	encrypt_time += (double)(encrypt_end - start) / CLOCKS_PER_SEC;
	cout << "����ʱ�䣺" << encrypt_time*1000 << "ms" << endl;

	for (int i = 0;i < 24;i++) {
		BlindMulInplace(pub, c1[i], c0[i]);    //ä��(���)
		HalfBlindAddInplace(pub, c0[i], 1);  //��ä��(���)
		HalfBlindMulInplace(pub, c2[i], 2); //��ä��(���)

		tmp[i] = new CipherText(c1[i]);


		BlindAddInplace(pub, c2[i], tmp[i]);    //ä��(���)
		BlindNegifyInplace(pub, c1[i]);      //äȡ��(���)
		BlindMulInplace(pub, c3[i], c2[i]);    //ä��(���)
		BlindSubInplace(pub, c3[i], c0[i]);    //ä��(���)
		//cout << "tmp->order=" << tmp[i]->getorder() << endl;
		//cout << "c0->order=" << c0[i]->getorder() << endl;
		//cout << "c1->order=" << c1[i]->getorder() << endl;
		//cout << "c2->order=" << c2[i]->getorder() << endl;
		//cout << "c3->order=" << c3[i]->getorder() << endl;
	}
	cout << "������ڴ棺" << endl;
	//showMemoryInfo();
	int jisuanhou = showMemoryInfo2();

	compute_end = clock();
	compute_time += (double)(compute_end - encrypt_end) / CLOCKS_PER_SEC;
	cout << "����ʱ�䣺" << compute_time * 1000 << "ms" << endl;

	for (int i = 0;i < 24;i++) {
		//big pp0 = Decrypt(pri, c0[i]);
		//big pp1 = Decrypt(pri, c1[i]);
		//big pp2 = Decrypt(pri, c2[i]);
		//big pp3 = Decrypt(pri, c3[i]);
		cout << "���ܽ��Ϊ��";
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
	cout << "���ܺ��ڴ棺" << endl;
	//showMemoryInfo();
	int jiemihou = showMemoryInfo2();

	decrypt_end = clock();
	decrypt_time += (double)(decrypt_end - compute_end) / CLOCKS_PER_SEC;
	cout << "����ʱ�䣺" << decrypt_time * 1000 << "ms" << endl;

	cout << "�������пɻ��յ��ڴ�" << endl;
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
