#include<iostream>
#include<cmath>
#include<cstdio>
#include<string>
#include<algorithm>
#include<iomanip>
#include<stack>
#include<queue>
using namespace std;

//树状数组模板，更新是从底部向上加,求前缀和，一个个往回减

int n, a[100005], x, y;
char opt[10];

inline int lowbit(int x)
{
    return x & -x;
}

inline void update(int i, int x)
{
    for (; i <= n; i += lowbit(i)) a[i] += x;
}

inline int query(int i)
{
    int ans = 0;
    for (; i; i -= lowbit(i)) ans += a[i];
    return ans;
}
