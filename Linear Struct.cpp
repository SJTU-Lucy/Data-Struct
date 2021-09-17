#include<iostream>
using namespace std;

template<class T>
class myStack
{
private:
	T* Data;
	int tail = -1;
public:
	myStack() {};
	myStack(int n) 
	{
		Data = new T[n];
	}
	~myStack() 
	{
		delete[]Data;
	}
	void push(T tmp)
	{
		Data[++tail] = tmp;
	}
	T top()
	{
		return Data[tail];
	}
	void pop()
	{
		if (tail==-1) return;
		else tail--;
	}
	bool isEmpty()
	{
		if (tail==-1) return true;
		else return false;
	}
};


template<class T>
class myQueue
{
private:
	T* Data;
	int head = 0;
	int tail = 0;
public:
	myQueue() {};
	myQueue(int n)
	{
		Data = new T[n];
	}
	~myQueue()
	{
		delete[]Data;
	}
	void push(T tmp)
	{
		Data[tail++] = tmp;
	}
	T top()
	{
		return Data[head];
	}
	void pop()
	{
		if (head == tail) return;
		else head++;
	}
	bool isEmpty()
	{
		if (head == tail) return true;
		else return false;
	}
};


template<class T>
class order_list
{
public:
	T* records;
	int length = 0;
	order_list() {};
	order_list(int n)
	{
		records = new T[n];
		length = 0;
	}
	~order_list()
	{
		delete[]records;
	}
	int Length()
	{
		return length;
	}
	void insert(const T a, int pos)
	{
		for (int i = pos + 1; i <= length + 1; ++i)
			records[i] = records[i - 1];
		records[pos] = a;
		length += 1;
	}
	void remove(int pos)
	{
		for (int i = pos; i < length; ++i)
			records[i] = records[i + 1];
		length -= 1;
	}
	int search(const T target)
	{
		for (int i = 1; i <= length; ++i)
		{
			if (records[i] == target)
				return i;
		}
		return -1;
	}
	T visit(int x)
	{
		return records[x];
	}
	void traverse()
	{
		for (int i = 1; i <= length; ++i)
			cout << records[i] << " ";
		cout << '\n';
	}
};

template<class T>
class block_list
{
public:
	struct node
	{
		T data;
		node* next = nullptr;
	};
	node* head;
	int length = 0;
	block_list() 
	{
		head = new node;
	}
	~block_list()
	{
		delete head;
	}
	int Length()
	{
		return length;
	}
	void insert(const T a, int pos)
	{
		if (length == 0)
		{
			node* tmp;
			tmp = new node;
			tmp->data = a;
			head->next = tmp;
			length += 1;
		}
		else
		{
			node* tmp1;        //tmp1是插入前面那个
			node* tmp2;	       //tmp2是要被插入的那个
			tmp2 = new node;
			tmp1 = head;
			tmp2->data = a;
			for (int i = 1; i < pos; ++i)
				tmp1 = tmp1->next;
			tmp2->next = tmp1->next;
			tmp1->next = tmp2;
			length += 1;
		}
	}
	void remove(int pos)
	{
		node* tmp1;        //tmp1是插入前面那个
		node* tmp2;
		tmp1 = head;
		for (int i = 1; i < pos; ++i)
			tmp1 = tmp1->next;
		tmp2 = tmp1->next->next;
		tmp1->next = tmp2;
		length -= 1;
	}
	T visit(int n)
	{
		node* tmp = head;
		for (int i = 0; i < n; ++i)
			tmp = tmp->next;
		return tmp->data;
	}
	void traverse()
	{
		node* tmp = head;
		for (int i = 1; i <= length; ++i)
		{
			tmp = tmp->next;
			cout << tmp->data << " ";
		}
	}
};

int main()
{
	block_list<int> myVector;
	myVector.insert(1, 1);
	myVector.insert(2, 2);
	myVector.insert(3, 2);
	myVector.remove(1);
	myVector.remove(2);
	myVector.traverse();

	return 0;
}