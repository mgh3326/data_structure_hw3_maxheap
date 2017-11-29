#include<cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iomanip>
#include <math.h>
using namespace std;


#define MAX_ELEMENT 151//�ִ� 150���� �ޱ� ����
int H_tree[32][32];// H_tree�� ���� �迭�� ���������� �����Ͽ����ϴ�.
class HeapNode {
	int key;//key��
public:
	HeapNode(int k = 0) :key(k) {}
	void setKey(int k) { key = k; }//�� �� �Է¹޴� �Լ�
	int getKey() { return key; }//�� �� ��ȯ�ϴ� �Լ�
	//���� ����ϴ� �Լ�
	void display() {//�빮���� ��� �ҹ��ڰ� ��µǰ� �ϰ� �ҹ����� ��� �빮�ڰ� ��µǰ� �մϴ�.(�Է¹������� �ٲ㼭 �ޱ� ������ ��ҹ����� �켱������ �������ټ� �ֽ��ϴ�.)
		if (key > 64 && key < 91)//�빮���ΰ��
			cout<<(char)(key + 32);
		else if (key > 96 && key < 123)//�ҹ����ΰ��
			cout <<(char)(key - 32);
		else
		cout << (char)key;
	}
};
class MaxHeap {
	HeapNode node[MAX_ELEMENT];//����� �迭
	int size;
public:
	MaxHeap() :size(0) {}
	bool isEmpty() { return size == 0; }//����ִ��� Ȯ���ϴ� �Լ�
	bool isFull() { return size == MAX_ELEMENT - 1; }//���� á���� Ȯ���ϴ� �Լ�

	HeapNode& getparent(int i) { return node[i / 2]; }//�θ� ��带 ����Ű���� �ϴ� �Լ�
	HeapNode& getLeft(int i) { return node[i * 2]; }//���� �ڽ��� ����Ű���� �ϴ� �Լ��Դϴ�
	HeapNode& getRight(int i) { return node[i * 2 + 1]; }//������ �ڽ��� ����Ű���� �ϴ� �Լ��Դϴ�.
	int getSize() { return size; }//���� ����� �����մϴ�.
	
	void insert(int key) {
		if (isFull())return;
		int i = ++size;
		if (key > 64 && key < 91)//�빮���ΰ��
			key=(key + 32);
		else if (key > 96 && key < 123)//�ҹ����ΰ��
			key=(key - 32);
		//Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
		while (i != 1
			&& key > getparent(i).getKey()) {
			node[i] = getparent(i);
			i /= 2;
		}
		node[i].setKey(key);//���� ��ġ�� ������ ����
	}
	HeapNode Delete() {
		if (isEmpty())return NULL;
		HeapNode item = node[1];//��Ʈ���(���� ���)
		HeapNode last = node[size--];
		int root = 1;
		int child = 2;
		while (child <= size) {
			//���� ����� �ڽ� ��� �� �� ū �ڽĳ�带 ã��
			if (child < size
				&&getLeft(root).getKey() < getRight(root).getKey())
				child++;//child:�� ū �ڽ� ����� �ε���
						//������ ��尡 �� ū �ڽĺ��� ũ�� ==> �̵��Ϸ�
			if (last.getKey() >= node[child].getKey())break;
			//�ƴϸ� ==>�Ѵܰ� �Ʒ��� �̵�
			node[root] = node[child];
			root = child;
			child *= 2;
		}
		node[root] = last;//������ ��带 ���� ��ġ�� ����
		return item;//��Ʈ ��� ��ȯ
	}
	
	void rotated_form_print(int index=1,int depth=0)//rotated_form
	{
	
		if (index <= size)
		{
			rotated_form_print(index*2 +1, depth + 1);
			std::cout << std::setw(2 * depth) << ""; // Indent 2*depth spaces.
			node[index].display();
			cout << endl;
			rotated_form_print(index*2, depth + 1);
		}
	}
	void not_rotated_form() {//���ڰ� ����ִ� ������ ���ڸ� �ٷ� ����ϵ��� �Ͽ����ϴ�.
		int area = pow(2, (int)log2(size)) - 1;
			for (int i = 1, level = 1; i <= size; i++) {
				if (size == 1){
					cout << " ";
					node[i].display();
					break;
				}
				if (i == level) {
					
					printf("\n");
					for (int j = 0; j < area/level; j++)
					{
						cout << " ";
					}
					level *= 2;
					node[i].display();
				}
				else {
					for (int j = 0; j < area * 2 *2/ level ; j++)
					{
						cout << " ";
					}
					node[i].display();
				}
			}
	}
	
	

	int center(int n) {	return n <= 1 ? 0 : 2 * center(n / 4) + 1; }
	int depth(int n) { return n <= 7 ? 1 : 2 * depth(n / 4); }
	int V[4][2] = { { -1, 0 },{ 1, 0 },{ 0, 1 },{ 0, -1 } };
	
	void H(int index, int i, int j, int d, int U, int D, int R, int L)
	{
		if (index > size) return;
		H_tree[i][j] = node[index].getKey();
		if (2 * index <= size) {
			if (d > 0)
			{
				for(int index=1;index<d;index++)
				H_tree[i + index*V[L][0]][j + index*V[L][1]] = '#';//����
			}
			if( d>1)//���Ʒ�
			{
				for (int index = 0; index < d; index++)
					H_tree[i -index + d*V[L][0] + V[U][0]][j + d*V[L][1] + V[U][1]] = '#';
				for (int index = 0; index < d; index++)
					H_tree[i + index + d*V[L][0] + V[D][0]][j + d*V[L][1] + V[D][1]] = '#';
				
			}
			
			H_tree[i + d*V[L][0]][j + d*V[L][1]] = node[2 * index].getKey();
				H(4 * index, i + d*(V[L][0] + V[U][0]),
					j + d*(V[L][1] + V[U][1]), d / 2, D, U, L, R);
				H(4 * index + 1, i + d*(V[L][0] + V[D][0]),
					j + d*(V[L][1] + V[D][1]), d / 2, U, D, R, L);
		}
		if (2 * index + 1 <= size) {
			if (d > 0)//������
			{
				for (int index = 1; index<d; index++)
				H_tree[i + index*V[R][0]][j + index*V[R][1]] = '#';
			}
			if(d>1)//���Ʒ�
			{
				for (int index = 0; index < d; index++)
					H_tree[i -index+ d*V[R][0] + V[U][0]][j + d*V[R][1] + V[U][1]] = '#';
				for (int index = 0; index < d; index++)
					H_tree[i +index+ d*V[R][0] + V[D][0]][j + d*V[R][1] + V[D][1]] = '#';
			}
			
			H_tree[i + d*V[R][0]][j + d*V[R][1]] = node[2 * index +1 ].getKey();
		
				H(4 * index + 2, i + d*(V[R][0] + V[D][0]),
					j + d*(V[R][1] + V[D][1]), d / 2, U, D, R, L);
				H(4 * index + 3, i + d*(V[R][0] + V[U][0]),
					j + d*(V[R][1] + V[U][1]), d / 2, D, U, L, R);
		}
		if (size > 127)
		{
			int x = (int)log2(size)-3;
			H_tree[x][x-1] = '#';
			H_tree[x][2 * x + x - 1] = '#';
			H_tree[x][x*x+ x - 1] = '#';
			H_tree[x][x*x+ 2 * x + x - 1] = '#';
			H_tree[2*x+2][x-1] = '#';
			H_tree[2 * x + 2][x*x+ 2 * x + x - 1] = '#';
			H_tree[2 * x + 2][2*x+ x - 1] = '#';
			H_tree[2 * x + 2][x*x+ x - 1] = '#';
		}
	}	
};
//���Լ�
void main() {
	MaxHeap heap;
	string s;
	int txt_size;//����
	vector<char> v;
	char ch;
	fstream fin("input.txt", fstream::in);
	fin >> noskipws >> txt_size;
	while (fin >> noskipws >> ch) {
		if(ch!=' '&&ch!='\n')
		v.push_back(ch); //���ڸ� �޵��� �Ͽ����ϴ�.
	}
	for (int i = 0; i < v.size(); i++)
	{
		switch (v[i])
		{
		case 'I':
			heap.insert(v[++i]); break;
		case 'D':
			heap.Delete(); break;
		default:
			break;
		}		
	}
	fin.close();//�� ����Ͽ����Ƿ� ifstream�� �ݾ��ݴϴ�.
	cout << "1. rotated form" << endl;
	heap.rotated_form_print();
	cout <<endl<< "2. not-rotated form" << endl;
	heap.not_rotated_form();
	cout <<endl<<endl<< "3. H-tree form" <<endl<< endl;
	heap.H(1, heap.center(heap.getSize()), heap.center(heap.getSize()),
		heap.depth(heap.getSize()), 0, 1, 2, 3);//HƮ�� ���
	int size = heap.getSize();
	int x;
	//������� ����� ũ�⸦ �����ִ� ���� x�� ũ�⸦ size�� ���� x���� �������ݴϴ�.
	if (size == 1)
		x = 1;
	else if (size < 8)
		x = 3;//2^2 2^3
	else if (size < 32)
		x = 7;//2^3 2^5
	else if (size < 128)
		x = 15;//2^4 2&7
	else if (size < 512)
		x = 31;//2^5 2^9
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (H_tree[i][j] > 64 && H_tree[i][j] < 91)//�빮���ΰ��
				cout << (char)(H_tree[i][j] + 32)<< ' ';
			else if (H_tree[i][j] > 96 && H_tree[i][j] < 123)//�ҹ����ΰ��
				cout << (char)(H_tree[i][j] - 32)<< ' ';
			else
				cout << (char)H_tree[i][j]<< ' ';
		}
		cout << endl;
	}
}
//1	                                   	                                   	                                                        0
//2	                                   	                               0                                                                                                                               1
//4	                                   0                                                               1                                                               2                                                               3
//8	                   0                               1                               2                               3                               4                               5                               6                               7
//16	       0               1               2               3               4               5               6               7               8               9               0               1               2               3               4               5
//32	   0       1       2       3       4       5       6       7       8       9       0       1       2       3       4       5       6       7       8       9       0       1       2       3       4       5       6       7       8       9       0       1
//64	 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8   9   1   2   3   4   5   6   7   8   9   1   2   3   4   5   6   7   8   9   1   2   3   4   5   6   7   8   9   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
//128	0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//
//128�� ��ĭ��
//64�� ó���� ��ĭ �� ���� 3ĭ��
//32�� ó���� ��ĭ �� ���� 7ĭ��
//16�� ó���� 7ĭ �� ���� 15ĭ
//8�� ó���� 15ĭ �״��� 31ĭ
//4�� 31ĭ,63ĭ
//2�� 63ĭ,127ĭ
//1�� 127ĭ

//H_Tree
/*
http://blog.naver.com/salinokl/220522345552
n : 0 >> 1 >> 1 >> 1
	1 >> 3 >> 7 >> 3
	2 >> 7 >> 31 >> 5
	3 >> 15 >>  127 >> 7
	4 >> 31 >>  511 >> 9 ??
	2�� (n+1)�� ���� 1�ΰ�����
	���ϱ� 4 ���ٰ� + 3�̳�
*/