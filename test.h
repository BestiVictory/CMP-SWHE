#pragma once
extern "C" {
#include <miracl.h>
#include <mirdef.h>
#include <stdio.h>
}
#include <iostream>
#include <time.h>

using namespace std;

//����ʱ������
int test_time();

//���Թ���
int test_function();
int test_one();
////����cpuռ����
//int test_cpu();
//
////����Ӳ��ռ����
//int test_disk();

//�����ڴ�ռ����
int test_memory();

int test_matrix();