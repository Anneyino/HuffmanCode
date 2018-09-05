#include<iostream>
#include<stack>
#include"MinHeap.h"
using namespace std;

typedef struct HuffNode{
    double wgt;
	int* HuffCode;
	HuffNode* left;
	HuffNode* right;
	int IsLeaf;

};
//�ݹ��㷨���Huffman����Huffman�� �������Ӧ��Ȩֵ
void LevelTraver(HuffNode* btArrayP, int level,int height,int pos,stack<char> stkCode,char** hcodes) {
	if (btArrayP->right != nullptr) {
		HuffNode* tmp = btArrayP;
		btArrayP = btArrayP->right;
		level--;
		height++;
		stkCode.push('1');
		LevelTraver(btArrayP, level,height,pos,stkCode,hcodes);
		level++;
		height--;
		stkCode.pop();
		btArrayP = tmp;
	}
	if (btArrayP->left!= nullptr) {
		HuffNode* tmp = btArrayP;
		btArrayP = btArrayP->left;
		level--;
		height++;
		stkCode.push('0');
		LevelTraver(btArrayP, level,height,pos,stkCode,hcodes);
		level++;
		height--;
		stkCode.pop();
		btArrayP = tmp;
	}
	if (level == 1&&btArrayP->left==NULL) {
		hcodes[pos] = new char[height];
		for (int i = height-1; i >= 0; i--) {
			hcodes[pos][i] = stkCode.top();
			stkCode.pop();
		}
		cout << "_____________________________________________________" << endl;
		for (int j = 0; j < height; j++) {
			cout << hcodes[pos][j];
		}
		for (int k = 39; k > height; k--) {
			cout << " ";
		}
		cout<< btArrayP->wgt<< endl;
		pos++;
	}
}
//�����ߵĸ�������
int Height(HuffNode* T) {
	if (T == NULL)
		return 0;
	else {
		int m = Height(T->left);
		int n = Height(T->right);
		return(m > n) ? (m + 1) : (n + 1);
	}
}
void HuffmanCode(double weights[], int size) {
	int newsize = size;//��ʼ���½���ʱ����Ĵ�С
	int pos = 0;//��ʼ��������±�
	int MaxLevel = 0;//��ʼ����������������������
	double tmp1;//������С�ѻ�ȡ��ʱ�����е���СȨֵ֮һ
	double tmp2;//������С�ѻ�ȡ��ʱ�����е���СȨֵ֮��
	double* tmpArray = new double[newsize];//��ʼ����ʱ����
	double* Branch = new double[size - 1];//��ʼ��֦�ɽ���Ȩֵ����
	double* LeavesP = new double[2 * size - 1];//�����ڵ����������Ȩֵ������
	//�����洢����������Ķ�άChar����
	char **hcodes = new char*[size];
	//�������������Ľ�����鲢��ÿ��left��right��ʼΪNULL
	HuffNode* HT = new HuffNode[2 * size - 1];
	HuffNode** HTp = new HuffNode*[2 * size - 1];
	for (int k = 0; k < 2 * size - 1; k++) {
		HTp[k] = &HT[k];
		HTp[k]->left = NULL;
		HTp[k]->right = NULL;
		HTp[k]->IsLeaf = 1;
	}
	for (int i = 0; i < newsize; i++) {
		tmpArray[i] = weights[i];
	}
	do {
		make_heap(tmpArray, newsize);
		tmp1 = tmpArray[0];
		tmpArray = DeleteE(tmpArray, newsize);
		newsize--;
		make_heap(tmpArray, newsize);
		tmp2 = tmpArray[0];
		tmpArray = DeleteE(tmpArray, newsize);
		newsize--;
		LeavesP[pos * 2] = tmp1;
		LeavesP[pos * 2 + 1] = tmp2;
		HTp[pos * 2]->wgt = tmp1;
		HTp[pos * 2 + 1]->wgt = tmp2;
		Branch[pos] = tmp1 + tmp2;
		tmpArray = InsertE(tmpArray, newsize, Branch[pos]);
		pos++;
		newsize++;
		//�����С����ֻʣһ��Ԫ�أ�������Ϊ���������ĸ����
		if (pos == size - 1) {
			LeavesP[2 * size - 2] = tmp1 + tmp2;
			HTp[2 * size - 2]->wgt = tmp1 + tmp2;
		}
	} while (newsize > 1);
	for (int j = 0; 2 * j + 1 < 2 * size - 2; j++) {
		int Pos;
		double res = HTp[2 * j]->wgt + HTp[2 * j + 1]->wgt;
		Pos = FindPos(LeavesP, 2 * size - 1, res);
		HTp[Pos]->left = HTp[2 * j];
		HTp[Pos]->right = HTp[2 * j + 1];
		HTp[Pos]->IsLeaf = 0;
	}
	//�ҵ�����㣬�ض�����������һλ
	HuffNode* root = HTp[2 * size - 2];
	HuffNode* n = HTp[2 * size - 2];
	//�ҵ��������Ĺ��������ĸ߶�
	MaxLevel = Height(n);
	stack<char>stk;
	for (int t = MaxLevel; t >= 2; t--) {
		LevelTraver(root, t, 0, 0, stk, hcodes);
	}
	delete[] hcodes;
	return;
}

int main() {
	int size;
	cout << "Please input the size of the double type array:" << endl;
	cin >> size;
	cout << endl;
	cout << "Please enter all the weight elements one by one like: 1.3 2.4 3.6 " << endl;
	cout << "Pay attention to that each elements is divided by a blank space" << endl;
	cout << endl;
	cout << "Now it's your turn to input "<<size<<" numbers: ";
	double* weight = new double[size];
	for (int i = 0; i < size; i++) {
		cin >> weight[i];
	}
	cout << endl;
	cout << "Now you will get the result as the following:" << endl;
	cout << endl;
	cout << "_____________________________________________________" << endl;
	cout << "Huffman Code" << "                         " << "Weights" << endl;
	HuffmanCode(weight, size);
	cout << "_____________________________________________________" << endl;
	system("pause");
	return 0;
}