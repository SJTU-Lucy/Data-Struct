#include<iostream>
using namespace std;

struct node
{
	int Data;
	int lnode = -1;
	int rnode = -1;
};

class search_tree
{
public:
	node* record;
	int len = 0;
	int root = 0;
	search_tree() {};
	search_tree(int n)
	{
		record = new node[n];
	}
	~search_tree()
	{
		delete []record;
	}
	//在二叉查找树中寻找值为x的节点
	int find(int x)
	{
		return find(x, root);
	}
	int find(int x, int Root)
	{
		//找到值或者不存在这样的值就直接返回
		if (x == record[Root].Data)
			return Root;
		else if (Root == -1) return -1;
		//若比root小，找左边否则找右边
		else if (x < record[Root].Data)
			return find(x, record[Root].lnode);
		else return find(x, record[Root].rnode);
	}
	void insert(int x)
	{
		//若根节点还不存在，就先作为根节点
		if (len == 0)
		{
			root = 1;
			record[++len].Data = x;
			return;
		}
		return insert(x, root);
	}
	void insert(int x, int Root)
	{
		//若比root的小，插左子树，否则插右子树,一旦发现左或右还没插，就插入
		if (x < record[Root].Data)
		{
			if (record[Root].lnode == -1)
			{
				record[Root].lnode = ++len;
				record[record[Root].lnode].Data = x;
				return;
			}
			else return insert(x, record[Root].lnode);
		}
		else if (x > record[Root].Data)
		{
			if (record[Root].rnode == -1)
			{
				record[Root].rnode = ++len;
				record[record[Root].rnode].Data = x;
				return;
			}
			else return insert(x, record[Root].rnode);
		}
	}
	void remove(int x)
	{
		return remove(x, root);
	}
	void remove(int x, int Root)
	{
		//该节点不存在，就返回
		if (Root == -1) return;
		if (x == record[Root].Data)
		{
			handleDelete(0, root, 0);
		}
		//若不是要找的节点，就向左边和右边延伸,若节点就是要删除的点，跳出特别处理
		if (x < record[Root].Data)
		{
			if (record[record[Root].lnode].Data == x)
				return handleDelete(Root,record[Root].lnode, 1);
			else return remove(x, record[Root].lnode);
		}
		else if (x > record[Root].Data)
		{
			if (record[record[Root].rnode].Data == x)
				return handleDelete(Root,record[Root].rnode, 2);
			else return remove(x, record[Root].rnode);
		}
	}
	void handleDelete(int parent, int position, int direction)
	{
		//要删除的是叶子节点
		if (record[position].lnode == -1 && record[position].rnode == -1)
		{
			if (parent == 0)
			{
				root = -1;
				return;
			}
			if (direction == 1)
			{
				record[parent].lnode = -1;
				return;
			}
			else 
			{
				record[parent].rnode = -1;
				return;
			}
		}
		//要删除的节点只有一个儿子
		else if (record[position].lnode != -1)
		{
			if (parent == 0)
			{
				root = record[position].lnode;
				return;
			}
			if (direction == 1)
			{
				record[parent].lnode = record[position].lnode;
				return;
			}
			else
			{
				record[parent].rnode = record[position].lnode;
				return;
			}
		}
		else if (record[position].rnode != -1)
		{
			if (parent == 0)
			{
				root = record[position].rnode;
				return;
			}
			if (direction == 1)
			{
				record[parent].lnode = record[position].rnode;
				return;
			}
			else
			{
				record[parent].rnode = record[position].rnode;
				return;
			}
		}
		//要删除的节点两个儿子都有
		else
		{
			int t = record[position].lnode;
			int prev = position;
			//寻找结点左边最大的值（即没有右节点）
			while (record[t].rnode != -1)
			{
				prev = t;
				t = record[t].rnode;
			}
			//此时得到的t即为左边最大节点的值
			record[position].Data = record[t].Data;	  //交换数值
			record[prev].rnode = record[t].lnode;     //将这个节点的信息抹去
		}
	}
	//按照存储的顺序打印信息
	void print()
	{
		for (int i = 1; i <= len; ++i)
			cout << record[i].Data << " ";
		cout << endl;
	} 
	//前序遍历
	void front()
	{
		return front(root);
	}
	void front(int Root)
	{
		if (Root == -1) return;
		cout << record[Root].Data << endl;
		front(record[Root].lnode);
		front(record[Root].rnode);
	}
};

int main()
{
	search_tree myTree(100);
	myTree.insert(1);
	myTree.insert(2);
	myTree.insert(3);
	myTree.insert(4);
	cout << myTree.find(1) << " ";
	cout << myTree.find(2) << " ";
	cout << myTree.find(3) << " ";
	cout << myTree.find(4) << " ";
	cout << endl;
	myTree.front();
	myTree.remove(4);
	myTree.front();
	myTree.remove(3);
	myTree.front();
	myTree.remove(2);
	myTree.front();
	myTree.remove(1);
	myTree.front();
	return 0;
}													   