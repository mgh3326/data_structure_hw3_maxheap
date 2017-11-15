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
	void display() { printf("%4d", key); }
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
};
//���Լ�
void main() {
	MaxHeap heap;

	//���� �׽�Ʈ
	heap.insert(10);	heap.insert(5);
	heap.insert(30);	heap.insert(8);
	heap.insert(9);	heap.insert(3);
	heap.insert(7);
	heap.display();//���� ���

				   //���� �׽�Ʈ
	heap.remove();	heap.display();
	heap.remove();	heap.display();
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
	while (fin >> noskipws >> ch) {
		if(ch!=' '&&ch!='\n')
		v.push_back(ch); // Or whatever
	}
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << endl;
	num = v[0];
}