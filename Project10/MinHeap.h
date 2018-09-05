#pragma once
#include<iostream>
using namespace std;
//辅助函数
//定义FindPos函数来找到某一元素位于数组中的位置
int FindPos(double a[], int size, double e) {
	int pos = 0;
	for (int i = size - 1; i >= 0; i--) {
		if (e == a[i]) {
			pos = i;
		}
	}
	return pos;
}
//用来将较小值逐步移至前位的辅助函数，在建堆函数中被重复调用
void addjustDown(double a[], int i, int size) {
	int j;
	j = 2 * i + 1;
	double temp;
	temp = a[i];
	while (j < size) {
		if (a[j] > a[j + 1] && j + 1 < size) {
			++j;
		}
		if (a[j] <temp) {
			a[i] = a[j];
			i = j;
			j = 2 * i + 1;
		}
		else
			break;
	}
	a[i] = temp;
}
//建堆函数，通过多次调用addjustDown来构建最小堆
void make_heap(double a[], int size) {
	for (int i = size / 2 - 1; i >= 0; i--) {
		addjustDown(a, i, size);
	}
}
//插入一个新的元素于数组中返回一个新的数组
double* InsertE(double a[], int size, double e) {
	double* b = new double[size + 1];
	b[0] = e;
	for (int i = 1; i < size + 1; i++) {
		b[i] = a[i - 1];
	}
	delete[] a;
	return b;
}
//从原数组中删除首位元素，并返回一个新的数组
double* DeleteE(double a[], int size) {
	double* b = new double[size - 1];
	for (int i = 0; i < size - 1; i++) {
		b[i] = a[i + 1];
	}
	delete[] a;
	return b;
}