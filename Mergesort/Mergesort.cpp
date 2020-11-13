#include<iostream>
using namespace std;

int num[100];
int N;

void mergesort(int low, int high)
{
	//如果只有一个数，就返回
	if (high == low) return;

	int mid = (low + high) / 2;
	int* tmp;
	int i, j, k;

	//devide and conquer
	mergesort(low, mid);
	mergesort(mid + 1, high);


	//handle
	tmp = new int[high - low + 1];
	i = low;
	j = mid + 1;
	k = 0;
	//移动指针比较两数的大小
	while (i <= mid && j <= high)
	{
		if (num[i] < num[j])
		{
			tmp[k] = num[i];
			i += 1;
			k += 1;
		}
		else if (num[i] >= num[j])
		{
			tmp[k] = num[j];
			j += 1;
			k += 1;
		}
	}
	//多的数补上
	if (i <= mid)
		for (; i <= mid; ++i)
		{
			tmp[k] = num[i];
			k += 1;
		}
	else if (j <= high)
		for (; j <= high; ++j)
		{
			tmp[k] = num[j];
			k += 1;
		}
	//把结合的数组替换原数组
	for (i = 0; i <= high - low; ++i)
		num[i + low] = tmp[i];
	delete[]tmp;
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

	mergesort(0, N - 1);
	print();

	return 0;
}