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
	int key;//key값
public:
	HeapNode(int k = 0) :key(k) {}
	void setKey(int k) { key = k; }
	int getKey() { return key; }
	void display() { printf("%d", key); }
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

	void insert(int key) {
		if (isFull())return;
		int i = ++size;

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
//주함수
void main() {
	MaxHeap heap;

	//삽입 테스트
	heap.insert(10);	heap.insert(5);
	heap.insert(30);	
	heap.insert(8);
	heap.insert(9);	heap.insert(3);
	heap.insert(7);
	heap.not_rotated_form();//상태 출력

				   //삭제 테스트
	/*heap.remove();	heap.display();
	heap.remove();	heap.display();*/
	printf("\n");
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
//128은 한칸씩
//64는 처음에 한칸 그 다음 3칸씩
//32는 처음에 세칸 그 다음 7칸씩
//16은 처음에 7칸 그 다음 15칸
//8은 처음에 15칸 그다음 31칸
//4는 31칸,63칸
//2는 63칸,127칸
//1은 127칸