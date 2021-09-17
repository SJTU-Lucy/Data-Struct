#include<iostream>
using namespace std;

#define maxn 2000002

int num[maxn];             //记录一个数是否为素数,0为素数，1为合数
int prime[maxn];           //记录素数数组
int cnt = 1;			   //素数目前第一个空位
int n;                     //标定范围

void sieve()
{
	for (int i = 2; i <= n; ++i)
	{
		if (num[i] == 0)    //如果这个数是素数
		{
			prime[cnt] = i; //记录素数
			cnt += 1;
		}
		for (int j = 1; j < cnt; ++j)
		{
			if (i * prime[j] > n) break;
			num[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

int main()
{
	cin >> n;
	sieve();
	for (int i = 1; i < cnt; ++i) 
		cout << prime[i] << " ";
	return 0;
}