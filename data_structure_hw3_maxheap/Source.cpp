#include<cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
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
	void display() { printf("%d", key); }
};
class MaxHeap {
	HeapNode node[MAX_ELEMENT];//����� �迭
	int size;
public:
	MaxHeap() :size(0) {}
	bool isEmpty() { return size == 0; }
	bool isFull() { return size == MAX_ELEMENT - 1; }

	HeapNode& getParent(int i) { return node[i / 2]; }
	HeapNode& getLeft(int i) { return node[i * 2]; }
	HeapNode& getRight(int i) { return node[i * 2 + 1]; }

	void insert(int key) {
		if (isFull())return;
		int i = ++size;

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
		
		if (size < 3)
		{
			for (int i = 1, level = 2; i <= size; i++) {
				if (i == level) {
					printf("\n    ");
					level *= 2;
				}
				node[i].display();
			}
			printf("\n---------------------------------");
		}
		else if (size < 7)
		{
			for (int i = 1, level = 2; i <= size; i++) {
				if (i == level) {
					printf("\n    ");
					level *= 2;
				}
				node[i].display();
			}
			printf("\n---------------------------------");
		}
	}
	void not_rotated_form() {
			for (int i = 1, level = 1; i <= size; i++) {
				if (i == level) {
					
					printf("\n");
					for (int j = 0; j < 127/level; j++)
					{
						cout << "a";
					}
					level *= 2;
				}

				node[i].display();
			}
		
		
		printf("\n---------------------------------");
	}
	void H_tree_form() {
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

	}
};
//���Լ�
void main() {
	MaxHeap heap;

	//���� �׽�Ʈ
	heap.insert(10);	heap.insert(5);
	heap.insert(30);	
	heap.insert(8);
	heap.insert(9);	heap.insert(3);
	heap.insert(7);
	heap.not_rotated_form();//���� ���

				   //���� �׽�Ʈ
	/*heap.remove();	heap.display();
	heap.remove();	heap.display();*/
	printf("\n");
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
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << endl;
	//int n1 = 63;
	//int n2 = 2;
	//cout << n1 / n2 << endl;
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