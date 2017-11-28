#include<cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iomanip>
#include <math.h>
using namespace std;


#define MAX_ELEMENT 150
//#define MAX_SIZE 1000
//char inputString[MAX_SIZE];
int sizeX=5;
int sizeY=5;
int H_tree[32][32];// int char?
//int** ary = new int*[sizeX];
//for (int i = 0; i < sizeY; ++i)
//	ary[i] = new int[sizeY];
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
		int parent = 1;//parent를 root로 바꾸는게 더 이쁠거 같다.
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

	//HeapNode find() { return node[1]; }필요없는거 같다.
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
	void print(int index=1,int depth=0)
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
			area = 1;
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
	

	int center(int n) {
		return n <= 1 ? 0 : 2 * center(n / 4) + 1; }

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
			//if (d > 0)
			//{
			//	for(int index=1;index<d;index++)
			//	H_tree[i + index*V[L][0]][j + index*V[L][1]] = '#';//왼쪽
			//}
			//if( d>1)//위아래
			//{
			//	for (int index = 0; index < d; index++)
			//		H_tree[i -index + d*V[L][0] + V[U][0]][j + d*V[L][1] + V[U][1]] = '#';
			//	for (int index = 0; index < d; index++)
			//		H_tree[i + index + d*V[L][0] + V[D][0]][j + d*V[L][1] + V[D][1]] = '#';
			//	
			//}
			
			H_tree[i + d*V[L][0]][j + d*V[L][1]] = node[2 * index].getKey();
			if (d==0)
			{
				H(4 * index, i + d*(V[L][0] + V[U][0])+1,
					j + d*(V[L][1] + V[U][1]), d / 2, D, U, L, R);
				H(4 * index + 1, i + d*(V[L][0] + V[D][0])-1,
					j + d*(V[L][1] + V[D][1]), d / 2, U, D, R, L);
			}
			else
			{
				H(4 * index, i + d*(V[L][0] + V[U][0]),
					j + d*(V[L][1] + V[U][1]), d / 2, D, U, L, R);
				H(4 * index + 1, i + d*(V[L][0] + V[D][0]),
					j + d*(V[L][1] + V[D][1]), d / 2, U, D, R, L);
			}
			
		}
		if (2 * index + 1 <= size) {
			//if (d > 0)//오른쪽
			//{
			//	for (int index = 1; index<d; index++)
			//	H_tree[i + index*V[R][0]][j + index*V[R][1]] = '#';
			//}
			//if(d>1)//위아래
			//{
			//	for (int index = 0; index < d; index++)
			//		H_tree[i -index+ d*V[R][0] + V[U][0]][j + d*V[R][1] + V[U][1]] = '#';
			//	for (int index = 0; index < d; index++)
			//		H_tree[i +index+ d*V[R][0] + V[D][0]][j + d*V[R][1] + V[D][1]] = '#';
			//}
			
			H_tree[i + d*V[R][0]][j + d*V[R][1]] = node[2 * index +1 ].getKey();
			if (d ==0)
			{
				H(4 * index + 2, i + d*(V[R][0] + V[D][0])-1,
					j + d*(V[R][1] + V[D][1]), d / 2, U, D, R, L);
				H(4 * index + 3, i + d*(V[R][0] + V[U][0])+1,
					j + d*(V[R][1] + V[U][1]), d / 2, D, U, L, R);
			}
			else
			{
				H(4 * index + 2, i + d*(V[R][0] + V[D][0]),
					j + d*(V[R][1] + V[D][1]), d / 2, U, D, R, L);
				H(4 * index + 3, i + d*(V[R][0] + V[U][0]),
					j + d*(V[R][1] + V[U][1]), d / 2, D, U, L, R);
			}
			
		}
	}	
};
//주함수
void main() {
	MaxHeap heap;
	string s;
	char c;
	int num;//갯수
	vector<char> v;
	char ch;
	fstream fin("input.txt", fstream::in);
	fin >> noskipws >> num;
	while (fin >> noskipws >> ch) {
		if(ch!=' '&&ch!='\n')
		v.push_back(ch); // Or whatever
	}
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
	}
	fin.close();//다 사용하였으므로 ifstream을 닫아줍니다.
	cout <<"size : " <<heap.getSize() << endl;//사이즈 확인용 곧 삭제 예정
	cout << "non_rotate output" << endl;
	cout << "===============================================" << endl;
	heap.print();
	cout << "non_rotate output" << endl;
	cout << "===============================================" << endl;
	heap.not_rotated_form();
	cout <<endl<< "===============================================" << endl;
	heap.H(1, heap.center(heap.getSize()), heap.center(heap.getSize()), heap.depth(heap.getSize()), 0, 1, 2, 3);//H트리 출력
	int size = heap.getSize();
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
	
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (H_tree[i][j] > 64 && H_tree[i][j] < 91)//대문자인경우
				cout << (char)(H_tree[i][j] + 32)<< ' ';
			else if (H_tree[i][j] > 96 && H_tree[i][j] < 123)//소문자인경우
				cout << (char)(H_tree[i][j] - 32)<< ' ';
			else
				cout << (char)H_tree[i][j]<< ' ';
		}
		cout << endl;
	}
	cout <<"==="<< size << endl;
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