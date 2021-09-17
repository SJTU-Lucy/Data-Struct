#include<iostream>
using namespace std;

int N;               //数组的总个数数
int num[10001];        //数组

void quicksort(int low, int high)
{
	int i = low, j = high;
	int key = num[low];           //以第一个数作为基准元素

	if (low >= high) return;

	while (true)
	{
		//这样出现的j就是第一个小于等于key的j
		while (num[j] > key && j > i) j--;     
		num[i] = num[j];
		while (num[i] <= key && i < j) i++;
		num[j] = num[i];
		if (i == j) break;
	}                                                 
	num[i] = key;

	//递归将两部分也排序
	quicksort(low, i - 1);
	quicksort(i + 1, high);
}

void print()
{
	int i;
	for (i = 0; i < N; ++i)
		cout << num[i] << " ";
}

int main()
{
	int i;
	cin >> N;
	for (i = 0; i < N; ++i)
		cin >> num[i];
	quicksort(0, N - 1);
	print();
	return 0;
}