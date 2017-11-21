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
int H_tree[32][32];// int char?
class HeapNode {
	int key;//key값
public:
	HeapNode(int k = 0) :key(k) {}
	void setKey(int k) { key = k; }
	int getKey() { return key; }

	void display() {
		//printf("%d", key);
		if (key > 64 && key < 91)//대문자인경우
			cout<<(char)(key + 32);
		else if (key > 96 && key < 123)//소문자인경우
			cout <<(char)(key - 32);
		else
		cout << (char)key;
	}
};
class MaxHeap {
	HeapNode node[MAX_ELEMENT];//요소의 배열
	int size;
public:
	MaxHeap() :size(0) {}
	bool isEmpty() { return size == 0; }
	bool isFull() { return size == MAX_ELEMENT - 1; }
	

	HeapNode& getParent(int i) { return node[i / 2]; }
	HeapNode& getLeft(int i) { return node[i * 2]; }
	HeapNode& getRight(int i) { return node[i * 2 + 1]; }
	int getSize() { return size; }
	
	void insert(int key) {
		if (isFull())return;
		int i = ++size;
		if (key > 64 && key < 91)//대문자인경우
			key=(key + 32);
		else if (key > 96 && key < 123)//소문자인경우
			key=(key - 32);
		//트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
		while (i != 1
			&& key > getParent(i).getKey()) {
			node[i] = getParent(i);
			i /= 2;
		}
		node[i].setKey(key);//최종 위치에 데이터 복사
	}
	HeapNode remove() {
		if (isEmpty())return NULL;
		HeapNode item = node[1];//루트노드(꺼낼 요소)
		HeapNode last = node[size--];
		int parent = 1;
		int child = 2;
		while (child <= size) {
			//현재 노드의 자식 노드 중 더 큰 자식노드를 찾음
			if (child < size
				&&getLeft(parent).getKey() < getRight(parent).getKey())
				child++;//child:더 큰 자식 노드의 인덱스
						//마지막 노드가 더 큰 자식보다 크면 ==> 이동완료
			if (last.getKey() >= node[child].getKey())break;
			//아니면 ==>한단계 아래로 이동
			node[parent] = node[child];
			parent = child;
			child *= 2;
		}
		node[parent] = last;//마지막 노드를 최종 위치에 저장
		return item;//루트 노드 반환
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
	void print(int index,int depth)//추가함
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
			area = 1;
		}
		else if (size < 8)
			area = 3;
		else if (size < 16)
			area = 7;
		else if (size < 32)
			area = 15;
		else if (size < 64)
			area = 31;
		else if (size < 128)
			area = 63;
		else if (size < 256)
			area = 127;
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
		
		
		//printf("\n---------------------------------");
	}
	void H_function() {
		vector< vector<char> > v;
		vector<char> element;
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
		cout << x << endl;
		cout << size << endl;
		int row = x;
		int column = x;
		//초기화
		vector<std::vector<char> > m_sampleArray;
		for (int i = 0; i < row; i++)
		{
			std::vector<char> element;
			element.resize(column);
			m_sampleArray.push_back(element);
		}
		//사용
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				// Use!!    
				m_sampleArray[i][j] = '#';
			}
		}
		//출력
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				// Use!!    
				cout << m_sampleArray[i][j];
			}
			cout << endl;
		}
	}
	

	int center(int n) { return n <= 1 ? 0 : 2 * center(n / 4) + 1; }

	int depth(int n) { return n <= 7 ? 1 : 2 * depth(n / 4); }
	int V[4][2] = { { -1, 0 },{ 1, 0 },{ 0, 1 },{ 0, -1 } };
	
	void H(int index, int i, int j, int d, int U, int D, int R, int L)
	{
		if (index > size) return;
		H_tree[i][j] = node[index].getKey();
		//if (d > 0)
		//{
		//	H_tree[i + V[U][0]][j + V[U][1]] = '#';
		//}
		if (2 * index <= size) {
			if (d > 0)
			{
				H_tree[i + V[L][0]][j + V[L][1]] = '#';
			}
			if( d>1)
			{
				H_tree[i + d*V[L][0]+V[U][0]][j + d*V[L][1]+V[U][1]] = '#';
				H_tree[i + d*V[L][0] + V[D][0]][j + d*V[L][1] + V[D][1]] = '#';
			}
			H_tree[i + d*V[L][0]][j + d*V[L][1]] = node[2 * index].getKey();
			H(4 * index, i + d*(V[L][0] + V[U][0]),
				j + d*(V[L][1] + V[U][1]), d / 2, D, U, L, R);
			H(4 * index + 1, i + d*(V[L][0] + V[D][0]),
				j + d*(V[L][1] + V[D][1]), d / 2, U, D, R, L);
		}
		if (2 * index + 1 <= size) {
			if (d > 0)
			{
				H_tree[i + V[R][0]][j + V[R][1]] = '#';
			}
			if(d>1)
			{
				H_tree[i + d*V[R][0] + V[U][0]][j + d*V[R][1] + V[U][1]] = '#';
				H_tree[i + d*V[R][0] + V[D][0]][j + d*V[R][1] + V[D][1]] = '#';
			}
			H_tree[i + d*V[R][0]][j + d*V[R][1]] = node[2 * index +1 ].getKey();
			H(4 * index + 2, i + d*(V[R][0] + V[D][0]),
				j + d*(V[R][1] + V[D][1]), d / 2, U, D, R, L);
			H(4 * index + 3, i + d*(V[R][0] + V[U][0]),
				j + d*(V[R][1] + V[U][1]), d / 2, D, U, L, R);
		}
	}

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
	//void H_function();
	
};
//주함수
void main() {
	MaxHeap heap;

	//삽입 테스트
	
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
	// 파일 읽기 준비
	/*ifstream in("input.txt");*/
	string s;
	char c;
	int num;//갯수
	vector<char> v;
	/*if (in.is_open()) 
	{
		in >> num;
		cout << "노드 갯수 : " << num << endl;
	}
	else {
		cout << "파일을 찾을 수 없습니다!" << endl;
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
	//heap.not_rotated_form();//상태 출력
							//삭제 테스트
	
	//heap.display();
	cout << heap.getSize() << endl;
	cout << "non_rotate output" << endl;
	cout << "===============================================" << endl;
	heap.print(1, 0);
	cout << "non_rotate output" << endl;
	cout << "===============================================" << endl;
	heap.not_rotated_form();
	cout <<endl<< "===============================================" << endl;
	heap.H(1, heap.center(heap.getSize()), heap.center(heap.getSize()), heap.depth(heap.getSize()), 0, 1, 2, 3);
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if (H_tree[i][j] > 64 && H_tree[i][j] < 91)//대문자인경우
				cout << (char)(H_tree[i][j] + 32)<< ' ';
			else if (H_tree[i][j] > 96 && H_tree[i][j] < 123)//소문자인경우
				cout << (char)(H_tree[i][j] - 32)<< ' ';
			else
				cout << (char)H_tree[i][j]<< ' ';
			//cout << H_tree[i][j] << ' ';

		}
		cout << endl;
	}
	//heap.H_function();
	//heap.set_H_tree();
	//heap.H_tree_form(1, heap.center(heap.getSize()),heap.center(heap.getSize()), heap.depth(heap.getSize()), 1, 1, 1, 1);
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
//128은 한칸씩
//64는 처음에 한칸 그 다음 3칸씩
//32는 처음에 세칸 그 다음 7칸씩
//16은 처음에 7칸 그 다음 15칸
//8은 처음에 15칸 그다음 31칸
//4는 31칸,63칸
//2는 63칸,127칸
//1은 127칸

//H_Tree
/*
http://blog.naver.com/salinokl/220522345552
n : 0 >> 1 >> 1 >> 1
	1 >> 3 >> 7 >> 3
	2 >> 7 >> 31 >> 5
	3 >> 15 >>  127 >> 7
	4 >> 31 >>  511 >> 9 ??
	2의 (n+1)승 빼기 1인가보다
	곱하기 4 에다가 + 3이네
*/