#include<cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iomanip>
using namespace std;


#define MAX_ELEMENT 150
#define MAX_SIZE 1000
char inputString[MAX_SIZE];
class HeapNode {
	int key;//key��
public:
	HeapNode(int k = 0) :key(k) {}
	void setKey(int k) { key = k; }
	int getKey() { return key; }
	void display() {
		//printf("%d", key);
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
	bool isEmpty() { return size == 0; }
	bool isFull() { return size == MAX_ELEMENT - 1; }
	int** H_tree;
	void set_H_tree(){
		int x;
		if (size == 1)
			x = 1;
		else if (size < 8)
			x = 3;
		else if (size < 32)
			x = 7;
		else if (size < 128)
			x = 15;
		else if (size < 512)
			x = 31;
	int **H_tree = new int*[x];
	for (int i = 0; i < x; ++i)//2���� �����Ҵ�
		H_tree[i] = new int[x];
	//return H_tree;
	}

	HeapNode& getParent(int i) { return node[i / 2]; }
	HeapNode& getLeft(int i) { return node[i * 2]; }
	HeapNode& getRight(int i) { return node[i * 2 + 1]; }
	int getSize() { return size; }
	int V[4][2] = { { -1, 0 },{ 1, 0 },{ 0, 1 },{ 0, -1 } };
	void insert(int key) {
		if (isFull())return;
		int i = ++size;
		if (key > 64 && key < 91)//�빮���ΰ��
			key=(key + 32);
		else if (key > 96 && key < 123)//�ҹ����ΰ��
			key=(key - 32);
		//Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
		while (i != 1
			&& key > getParent(i).getKey()) {
			node[i] = getParent(i);
			i /= 2;
		}
		node[i].setKey(key);//���� ��ġ�� ������ ����
	}
	HeapNode remove() {
		if (isEmpty())return NULL;
		HeapNode item = node[1];//��Ʈ���(���� ���)
		HeapNode last = node[size--];
		int parent = 1;
		int child = 2;
		while (child <= size) {
			//���� ����� �ڽ� ��� �� �� ū �ڽĳ�带 ã��
			if (child < size
				&&getLeft(parent).getKey() < getRight(parent).getKey())
				child++;//child:�� ū �ڽ� ����� �ε���
						//������ ��尡 �� ū �ڽĺ��� ũ�� ==> �̵��Ϸ�
			if (last.getKey() >= node[child].getKey())break;
			//�ƴϸ� ==>�Ѵܰ� �Ʒ��� �̵�
			node[parent] = node[child];
			parent = child;
			child *= 2;
		}
		node[parent] = last;//������ ��带 ���� ��ġ�� ����
		return item;//��Ʈ ��� ��ȯ
	}

	HeapNode find() { return node[1]; }
	void display() {
		for (int i = 1, level = 1; i <= size; i++) {
			if (i == level) {
				printf("\n");
				level *= 2;
			}
			node[i].display();
		}
		printf("\n---------------------------------");
	}
	void rotated_form() {
	}
	void print(int index,int depth)//�߰���
										   // Library facilities used: iomanip, iostream, stdlib
	{
	
		if (index <= size)
		{
			print(index*2 +1, depth + 1);
			std::cout << std::setw(2 * depth) << ""; // Indent 4*depth spaces. ->2*depth
			/*std::cout << (char)node[index].getKey() << std::endl;*/
			node[index].display();
			cout << endl;
			print(index*2, depth + 1);
		}
	}

	void not_rotated_form() {
		int area = 0;
		if (size > 1 && size < 4)
		{
			area = 3;
		}
		else if (size < 8)
			area = 7;
		else if (size < 16)
			area = 15;
		else if (size < 32)
			area = 31;
		else if (size < 64)
			area = 63;
		else if (size < 128)
			area = 127;
		else if (size < 256)
			area = 255;
			for (int i = 1, level = 1; i <= size; i++) {
				if (size == 1)
				{
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
		
		
		printf("\n---------------------------------");
	}
	
	void H_tree_form(int index, int i, int j, int d, int U, int D, int R, int L) {
		
	
		if (index > size) return;
		H_tree[i][j] = node[index].getKey();//unable
		if (2 * index <= size) {
			H_tree[i + d*V[L][0]][j + d*V[L][1]] = node[2 * index - 1].getKey();
			H_tree_form(4*index,i+d*(V[L][0]+V[U][0]),
				j + d*(V[L][1] + V[U][1]), d / 2, D, U, L, R);
			H_tree_form(4 * index + 1, i + d*(V[L][0] + V[D][0]),
				j + d*(V[L][1] + V[D][1]), d / 2, U, D, R, L);
		}
		if (2 * index + 1 <= size) {
			H_tree[i + d*V[R][0]][j + d*V[R][1]] = node[2 * index].getKey();
			H_tree_form(4 * index + 2, i + d*(V[R][0] + V[D][0]),
				j + d*(V[R][1] + V[D][1]), d / 2, U, D, R, L);
			H_tree_form(4 * index + 3, i + d*(V[R][0] + V[U][0]),
				j + d*(V[R][1] + V[U][1]), d / 2, D, U, L, R);
		}
		}

	int center(int n) { return n <= 1 ? 0 : 2 * center(n / 4) + 1; }

	int depth(int n) { return n <= 7 ? 1 : 2 * depth(n / 4); }
	/*	str[] = "123456789ABCDEFGHIJKLMNOPQRSTUV";
		V[4][2] = { { -1, 0 },{ 1, 0 },{ 0, 1 },{ 0, -1 } };
		H(node, i, j, d, U, D, R, L)
		{
			if (node > n) return;
			H_tree[i][j] = str[node - 1];
			if (2 * node <= n) {
				H_tree[i + d*V[L][0]][j + d*V[L][1]] = str[2 * node - 1];
				H(4 * node, i + d*(V[L][0] + V[U][0]),
					j + d*(V[L][1] + V[U][1]), d / 2, D, U, L, R);
				H(4 * node + 1, i + d*(V[L][0] + V[D][0]),
					j + d*(V[L][1] + V[D][1]), d / 2, U, D, R, L);
			}
			if (2 * node + 1 <= n) {
				H_tree[i + d*V[R][0]][j + d*V[R][1]] = str[2 * node];
				H(4 * node + 2, i + d*(V[R][0] + V[D][0]),
					j + d*(V[R][1] + V[D][1]), d / 2, U, D, R, L);
				H(4 * node + 3, i + d*(V[R][0] + V[U][0]),
					j + d*(V[R][1] + V[U][1]), d / 2, D, U, L, R);
			}
		}
		center(n) { return n <= 1 ? 0 : 2 * center(n / 4) + 1; }
		depth(n) { return n <= 7 ? 1 : 2 * depth(n / 4); }
		CALL  H(1, center(n), center(n), depth(n), N, S, E, W);*/

	
};
//���Լ�
void main() {
	MaxHeap heap;

	//���� �׽�Ʈ
	
	/*heap.insert(45);
	heap.insert(35);
	heap.insert(23);
	heap.insert(27);
	heap.insert(21);
	heap.insert(22);
	heap.insert(4);
	heap.insert(19);
	heap.insert(42);
	heap.remove();*/


	//heap.remove();	heap.display();
	//printf("\n");
	// ���� �б� �غ�
	/*ifstream in("input.txt");*/
	string s;
	char c;
	int num;//����
	vector<char> v;
	/*if (in.is_open()) 
	{
		in >> num;
		cout << "��� ���� : " << num << endl;
	}
	else {
		cout << "������ ã�� �� �����ϴ�!" << endl;
	}
	while (!in.eof())
	{
		getline(in, s);
		cout << s << endl;
		v1.push_back(tmp);
	}
	vector<char> v(s.length() + 1);
	std::copy(s.c_str(), s.c_str() + s.length() + 1, v.begin());
	cout << v[1] << endl;
	cout << endl;
	in.close();*/
	char ch;
	fstream fin("input.txt", fstream::in);
	fin >> noskipws >> num;
	while (fin >> noskipws >> ch) {
		if(ch!=' '&&ch!='\n')
		v.push_back(ch); // Or whatever
	}
	//num = v[0];
	//cout <<v.size()<< endl;
	for (int i = 0; i < v.size(); i++)
	{
		switch (v[i])
		{
		case 'I':
			heap.insert(v[++i]); break;
		case 'D':
			heap.remove(); break;
		default:
			break;
		}
		/*if (v[i] = 'D')
			heap.remove();*/
		/*if (v[i] = 'I')*/
				
	}
	//heap.not_rotated_form();//���� ���
							//���� �׽�Ʈ
	
	//heap.display();
	cout << heap.getSize() << endl;
	cout << "non_rotate output" << endl;
	cout << "===============================================" << endl;
	heap.print(1, 0);
	cout << "non_rotate output" << endl;
	cout << "===============================================" << endl;
	heap.not_rotated_form();
	heap.set_H_tree();
	heap.H_tree_form(1, heap.center(heap.getSize()),heap.center(heap.getSize()), heap.depth(heap.getSize()), 1, 1, 1, 1);
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