#pragma once
#include<iostream>
using namespace std;
//��������
//����FindPos�������ҵ�ĳһԪ��λ�������е�λ��
int FindPos(double a[], int size, double e) {
	int pos = 0;
	for (int i = size - 1; i >= 0; i--) {
		if (e == a[i]) {
			pos = i;
		}
	}
	return pos;
}
//��������Сֵ������ǰλ�ĸ����������ڽ��Ѻ����б��ظ�����
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
//���Ѻ�����ͨ����ε���addjustDown��������С��
void make_heap(double a[], int size) {
	for (int i = size / 2 - 1; i >= 0; i--) {
		addjustDown(a, i, size);
	}
}
//����һ���µ�Ԫ���������з���һ���µ�����
double* InsertE(double a[], int size, double e) {
	double* b = new double[size + 1];
	b[0] = e;
	for (int i = 1; i < size + 1; i++) {
		b[i] = a[i - 1];
	}
	delete[] a;
	return b;
}
//��ԭ������ɾ����λԪ�أ�������һ���µ�����
double* DeleteE(double a[], int size) {
	double* b = new double[size - 1];
	for (int i = 0; i < size - 1; i++) {
		b[i] = a[i + 1];
	}
	delete[] a;
	return b;
}