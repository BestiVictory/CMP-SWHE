#pragma once
extern "C" {
#include <miracl.h>
#include <mirdef.h>
#include <stdio.h>
}
#include <iostream>
#include <time.h>

using namespace std;

//测试时间性能
int test_time();

//测试功能
int test_function();
int test_one();
////测试cpu占用率
//int test_cpu();
//
////测试硬盘占用率
//int test_disk();

//测试内存占用率
int test_memory();

int test_matrix();