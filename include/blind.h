#pragma once
#pragma once
#pragma once

#define MOD_BASE_NUM 20
#define MOD_CONFUSE_NUM 64

extern "C" {
#include <miracl.h>
#include <mirdef.h>
#include <stdio.h>
}
#include <iostream>
using namespace std;

//模基组
class ModBase {
public:
	ModBase();
	~ModBase();
	int* getBase() {
		return base;
	}
	void setBase(int b[MOD_BASE_NUM]) {
		base = b;
	}

private:
	int* base;
};

//真假位置模板，存20个值，即对于每个模基，第几个是真实的，用户持有的秘密参数中有这一项
class ModConfusePattern
{
public:
	ModConfusePattern();
	~ModConfusePattern();
	int* getPattern() {
		return pattern;
	}
	void setPattern(int p[MOD_BASE_NUM]) {
		pattern = p;
	}

private:
	int* pattern;//第几个是真的
};

//公钥
class BPS_PubParas
{
public:
	BPS_PubParas();
	~BPS_PubParas();
	int get_sid() { return this->sid; }
	void set_sid(int s) { this->sid = s; }
	int get_amp() { return this->amp; }
	void set_amp(int a) { this->amp = a; }
	ModBase get_mode_base() { return this->mod_base; }
	void set_mod_base(ModBase m) { this->mod_base = m; }
private:
	int sid;
	int amp;
	ModBase mod_base;
};

//私钥
class BPS_PriParas
{
public:
	BPS_PriParas();
	~BPS_PriParas();
	int get_sid() { return this->sid; }
	void set_sid(int s) { this->sid = s; }
	int get_amp() { return this->amp; }
	void set_amp(int a) { this->amp = a; }
	ModBase get_mode_base() { return this->mod_base; }
	void set_mod_base(ModBase m) { this->mod_base = m; }
	ModConfusePattern getpattern() { return this->pattern; }
	void setpattern(ModConfusePattern mcp) { this->pattern = mcp; }

private:
	int sid;
	int amp;
	ModBase mod_base;
	ModConfusePattern pattern;
};

//用户密钥
class UserKey
{
public:
	UserKey();
	~UserKey();
	char* getkey() { return key; }
	void setkey(string k) {strcpy_s(this->key, k.c_str());}
private:
	char key[32];
};

//密文数组，存一共20*64个值
class ValuesOnModBase
{
public:
	ValuesOnModBase();
	//ValuesOnModBase(int v[MOD_BASE_NUM][MOD_CONFUSE_NUM]) {this->value=v;}
	~ValuesOnModBase();

	int getvalue(int i, int j) { return value[i][j]; }
	void setvalue(int i, int j, int key) { value[i][j]=key; }
private:
	int value[MOD_BASE_NUM][MOD_CONFUSE_NUM];
};

//密文（含有密文数组和密文的阶）
class CipherText
{
public:
	CipherText();
	CipherText(CipherText* copy) {
		this->sid = copy->getsid();
		this->order = copy->getorder();
		this->setValuesOnModBase(copy->getValuesOnModBase());
	};
	~CipherText();
	void setsid(int s) { this->sid = s; }
	int getsid() { return this->sid; }
	void setorder(int o) { this->order = o; }
	int getorder() { return this->order; }
	void setValuesOnModBase(ValuesOnModBase *v) { this->data = v; }
	ValuesOnModBase* getValuesOnModBase() { return this->data; }

private:
	int sid;
	int order; //该密文的阶(明文阶为0)
	ValuesOnModBase* data;
};

//生成公私钥 
void create_BPS_Paras(UserKey *key, BPS_PubParas* pub_paras, BPS_PriParas* private_paras, int amp_size);

//根据秘密参数加密
int Encrypt(BPS_PriParas *private_paras, int data, CipherText* cipher);

//根据秘密参数解密
big Decrypt(BPS_PriParas *private_paras, CipherText* cipher);

//根据秘密参数解密
int Decrypt2(BPS_PriParas *private_paras, CipherText* cipher);

//求密文相反数 r=-x
void BlindNegify(BPS_PubParas* pub_paras, CipherText* x, CipherText* r);

//求密文相反数(替代)x=-x
void BlindNegifyInplace(BPS_PubParas* pub_paras, CipherText* x);

//盲加法 r=x+y
void BlindAdd(BPS_PubParas* pub_paras, CipherText* x, CipherText* y, CipherText* r);

//盲加法(替代) x=x+y
void BlindAddInplace(BPS_PubParas* pub_paras, CipherText* x, CipherText* y);

//盲减法 r=x-y
void BlindSub(BPS_PubParas* pub_paras, CipherText* x, CipherText* y, CipherText* r);

//盲减法(替代) x=x-y
void BlindSubInplace(BPS_PubParas* pub_paras, CipherText* x, CipherText* y);

//盲乘法 r=x*y
void BlindMul(BPS_PubParas* pub_paras, CipherText* x, CipherText* y, CipherText* r);

//盲乘法(替代) x=x*y
void BlindMulInplace(BPS_PubParas* pub_paras, CipherText* x, CipherText* y);

//盲幂运算 r=x^y
void BlindPow(BPS_PubParas* pub_paras, CipherText* x, int y, CipherText* r);

//盲幂运算(替代) x=x^y
void BlindPowInplace(BPS_PubParas* pub_paras, CipherText* x, int y);

//半盲加法 r=x+y
void HalfBlindAdd(BPS_PubParas* pub_paras, CipherText* x, int y, CipherText* r);

//半盲加法(替代) x=x+y
void HalfBlindAddInplace(BPS_PubParas* pub_paras, CipherText* x, int y);

//半盲减法 r=x-y
void HalfBlindSub(BPS_PubParas* pub_paras, CipherText* x, int y, CipherText* r);

//半盲减法(替代) x=x-y
void HalfBlindSubInplace(BPS_PubParas* pub_paras, CipherText* x, int y);

//半盲乘法 r=x*y
void HalfBlindMul(BPS_PubParas* pub_paras, CipherText* x, int y, CipherText* r);

//半盲乘法(替代) x=x*y
void HalfBlindMulInplace(BPS_PubParas* pub_paras, CipherText* x, int y);

//盲连加
void BlindAddMany(BPS_PubParas* pub_paras,int num, CipherText* x[], CipherText* r);

//盲连乘
void BlindMulMany(BPS_PubParas* pub_paras,int num, CipherText* x[], CipherText* r);

