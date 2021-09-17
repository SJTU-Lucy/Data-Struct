#include<iostream>
#include<cmath>
#include<cstdio>
#include<string>
#include<algorithm>
#include<iomanip>
#include<stack>
#include<queue>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
using namespace std;

class DisjointedSet
{
public:
	int* parent;  //若为根节点，保存的负值为元素个数，若为正则为父亲
	int size;
	//初始化，一开始的值全为-1
	DisjointedSet(int n)
	{
		size = n + 1;
		parent = new int[size];
		for (int i = 0; i < size; ++i)
			parent[i] = -1;
	}
	~DisjointedSet()
	{
		delete[] parent;
	}
	void print()
	{
		for (int i = 1; i < size; ++i)
			cout << Find(i) << " ";
		cout << endl;
	}
	void Union(int x, int y)
	{
		int root1 = Find(x);
		int root2 = Find(y);
		if (root1 == root2) return;		
		if (parent[root1] > parent[root2]) 
		{
			parent[root2] += parent[root1];
			parent[root1] = root2;
		} 
		else
		{
			parent[root1] += parent[root2];
			parent[root2] = root1;
		}
	}
	int Find(int x)
	{
		if (parent[x] < 0) return x;
		int myStack[100];
		int head = 0;
		int current = x;      //是最终的答案
		int tmp;
		while (true)
		{
			//current到达根节点
			if (parent[current] < 0)
				break;
			else
			{
				myStack[head++] = current;
				current = parent[current];
			}
		}
		head -= 1;
		while (head >= 0)
		{
			tmp = myStack[head--];
			parent[tmp] = current;
		}
		return current;
	}
};

int main()
{
	int m, n, p;
	cin >> m >> n >> p;
	DisjointedSet mySet(m);
	int order1, order2;
	for (int i = 0; i < n; ++i)
	{
		cin >> order1 >> order2;
		mySet.Union(order1, order2);
	}
	for (int i = 0; i < p; ++i)
	{
		cin >> order1 >> order2;
		if(mySet.Find(order1) == mySet.Find(order2))
			cout << "Yes" << '\n';
		else cout << "No" << '\n';
	}
	return 0;
	
}