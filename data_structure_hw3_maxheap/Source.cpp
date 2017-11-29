#include<cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iomanip>
#include <math.h>
using namespace std;


#define MAX_ELEMENT 151//최대 150개를 받기 위함
int H_tree[32][32];// H_tree를 담을 배열을 전역변수로 선언하였습니다.
class HeapNode {
	int key;//key값
public:
	HeapNode(int k = 0) :key(k) {}
	void setKey(int k) { key = k; }//값 을 입력받는 함수
	int getKey() { return key; }//값 을 반환하는 함수
	//값을 출력하는 함수
	void display() {//대문자인 경우 소문자가 출력되게 하고 소문자인 경우 대문자가 출력되게 합니다.(입력받을때도 바꿔서 받기 때문에 대소문자의 우선순위를 변경해줄수 있습니다.)
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
	bool isEmpty() { return size == 0; }//비어있는지 확인하는 함수
	bool isFull() { return size == MAX_ELEMENT - 1; }//가득 찼는지 확인하는 함수

	HeapNode& getparent(int i) { return node[i / 2]; }//부모 노드를 가르키도록 하는 함수
	HeapNode& getLeft(int i) { return node[i * 2]; }//왼쪽 자식을 가르키도록 하는 함수입니다
	HeapNode& getRight(int i) { return node[i * 2 + 1]; }//오른쪽 자식을 가르키도록 하는 함수입니다.
	int getSize() { return size; }//현재 사이즈를 리턴합니다.
	
	void insert(int key) {
		if (isFull())return;
		int i = ++size;
		if (key > 64 && key < 91)//대문자인경우
			key=(key + 32);
		else if (key > 96 && key < 123)//소문자인경우
			key=(key - 32);
		//트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
		while (i != 1
			&& key > getparent(i).getKey()) {
			node[i] = getparent(i);
			i /= 2;
		}
		node[i].setKey(key);//최종 위치에 데이터 복사
	}
	HeapNode Delete() {
		if (isEmpty())return NULL;
		HeapNode item = node[1];//루트노드(꺼낼 요소)
		HeapNode last = node[size--];
		int root = 1;
		int child = 2;
		while (child <= size) {
			//현재 노드의 자식 노드 중 더 큰 자식노드를 찾음
			if (child < size
				&&getLeft(root).getKey() < getRight(root).getKey())
				child++;//child:더 큰 자식 노드의 인덱스
						//마지막 노드가 더 큰 자식보다 크면 ==> 이동완료
			if (last.getKey() >= node[child].getKey())break;
			//아니면 ==>한단계 아래로 이동
			node[root] = node[child];
			root = child;
			child *= 2;
		}
		node[root] = last;//마지막 노드를 최종 위치에 저장
		return item;//루트 노드 반환
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
	void not_rotated_form() {//문자가 들어있는 벡터의 문자를 바로 출력하도록 하였습니다.
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
				H_tree[i + index*V[L][0]][j + index*V[L][1]] = '#';//왼쪽
			}
			if( d>1)//위아래
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
			if (d > 0)//오른쪽
			{
				for (int index = 1; index<d; index++)
				H_tree[i + index*V[R][0]][j + index*V[R][1]] = '#';
			}
			if(d>1)//위아래
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
//주함수
void main() {
	MaxHeap heap;
	string s;
	int txt_size;//갯수
	vector<char> v;
	char ch;
	fstream fin("input.txt", fstream::in);
	fin >> noskipws >> txt_size;
	while (fin >> noskipws >> ch) {
		if(ch!=' '&&ch!='\n')
		v.push_back(ch); //문자만 받도록 하였습니다.
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
	fin.close();//다 사용하였으므로 ifstream을 닫아줍니다.
	cout << "1. rotated form" << endl;
	heap.rotated_form_print();
	cout <<endl<< "2. not-rotated form" << endl;
	heap.not_rotated_form();
	cout <<endl<<endl<< "3. H-tree form" <<endl<< endl;
	heap.H(1, heap.center(heap.getSize()), heap.center(heap.getSize()),
		heap.depth(heap.getSize()), 0, 1, 2, 3);//H트리 출력
	int size = heap.getSize();
	int x;
	//사이즈별로 출력할 크기를 정해주는 변수 x의 크기를 size에 따라 x값을 결정해줍니다.
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
			if (H_tree[i][j] > 64 && H_tree[i][j] < 91)//대문자인경우
				cout << (char)(H_tree[i][j] + 32)<< ' ';
			else if (H_tree[i][j] > 96 && H_tree[i][j] < 123)//소문자인경우
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