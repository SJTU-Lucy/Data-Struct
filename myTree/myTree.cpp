#include <iostream>
using namespace std;

#define maxn 1000005
//二叉树类模板

template<typename T>
class BinaryTree
{
public:
	struct Node
	{
		int parent = 0;
		int lchild = 0;
		int rchild = 0;
		T data;
	};
	int len = 1;           //用来记录当前应该存入的节点是在哪个位置
	int Max_depth = 0;
	Node* element;
	BinaryTree() {};
	BinaryTree(int x)
	{
		element = new Node[x];
	}
	~BinaryTree() 
	{ 
		delete[]element;
	}
	void giveSpace(int x)
	{
		element = new Node[x];
	}
	void push_by_child(T Data,int Lchild,int Rchild)
	{
		element[len].data = Data;
		element[len].lchild = Lchild;
		element[len].rchild = Rchild;
		element[Lchild].parent = len;
		element[Rchild].parent = len;
		len += 1;
	}
	void push_by_parent(T Data, int Parent)
	{
		element[len].parent = Parent;
		element[len].data = Data;
		if (element[Parent].lchild == 0)
			element[Parent].lchild = len;
		else  element[Parent].rchild = len;
		len++;
	}
	int findRoot()
	{
		int tmp = 1;
		while (element[tmp].parent != 0)
			tmp = element[tmp].parent;
		return tmp;
	}
	void prevOrder()
	{
		int root = findRoot();
		cout << element[root].data << " ";
		if (element[root].lchild != 0) prevOrder(element[root].lchild);
		if (element[root].rchild != 0) prevOrder(element[root].rchild);
		cout << endl;
	}
	void prevOrder(int root)
	{
		cout << element[root].data << " ";
		if (element[root].lchild != 0) prevOrder(element[root].lchild);
		if (element[root].rchild != 0) prevOrder(element[root].rchild);
	}
	void midOrder()
	{
		int root = findRoot();
		if (element[root].lchild != 0) midOrder(element[root].lchild);		
		cout << element[root].data << " ";
		if (element[root].rchild != 0) midOrder(element[root].rchild);	 		
		cout << endl;
	}
	void midOrder(int root)
	{
		if (element[root].lchild != 0) latterOrder(element[root].lchild);
		cout << element[root].data << " ";
		if (element[root].rchild != 0) latterOrder(element[root].rchild);
	}
	void latterOrder()
	{
		int root = findRoot();
		if (element[root].lchild != 0) latterOrder(element[root].lchild);
		if (element[root].rchild != 0) latterOrder(element[root].rchild);
		cout << element[root].data << endl;
	}
	void latterOrder(int root)
	{
		if (element[root].lchild != 0) latterOrder(element[root].lchild);
		if (element[root].rchild != 0) latterOrder(element[root].rchild);
		cout << element[root].data << " ";
	}
	void levelOrder()
	{
		int root = findRoot();
		int* Queue;
		Queue = new int[len];
		int head = 0;
		int tail = 0;     //tail是不存放数字的
		Queue[tail++] = root;
		while(head!=tail)
		{
			int tmp = Queue[head++];
			cout << element[tmp].data << " ";
			if (element[tmp].lchild != 0)
				Queue[tail++] = element[tmp].lchild;
			if (element[tmp].rchild != 0)
				Queue[tail++] = element[tmp].rchild;
		}
		cout << endl;
		delete[]Queue;
	}
	void clear()
	{
		delete[]element;
	}
	inline int max(int a, int b)
	{
		if (a > b) return a;
		else return b;
	}
	void search_depth(int index, int depth)
	{
		int ldepth = 0;
		int rdepth = 0;
		if (element[index].lchild == 0 && element[index].rchild == 0)
		{
			Max_depth = max(depth, Max_depth);
			return;
		}
		if (element[index].lchild != 0)
			search_depth(element[index].lchild, depth + 1);
		if (element[index].rchild != 0)
			search_depth(element[index].rchild, depth + 1);
	}
};

int main()
{
	BinaryTree<int> myTree(maxn);
	int N;
	cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		int a, b;
		cin >> a >> b;
		myTree.push_by_child(0, a, b);
	}
	myTree.search_depth(1, 1);
	cout << myTree.Max_depth;
	return 0;
}
