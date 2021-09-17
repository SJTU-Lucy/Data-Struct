#include<iostream>
#include<vector>
using namespace std;
#define INF 100000
//该代码以任务一为介绍
//由于数据量太大，此处不具体展示内容
int map[28][28];	 	//邻接矩阵
int edge[51][2];		//存放图中的边
int dis[28][28];        //dis[i][j]即表示i与j点间的距离

void floyd()
{
	//初始化邻接矩阵和答案矩阵
	for (int i = 1; i < 28; ++i)
		for (int j = 1; j < 28; ++j)
		{
			//若是对角线，答案在后面无需变化，邻接矩阵中值为0
			if (i == j)
			{
				dis[i][j] = 0;
				map[i][j] = 0;
			}
			//其他情况，均定义为一个很大的常数，以便后续更新
			else
			{
				dis[i][j] = INF;
				map[i][j] = INF;
			}
		}
	//使用边来产生邻接矩阵
	for (int i = 0; i < 51; ++i)
	{
		int a = edge[i][0];
		int b = edge[i][1];
		map[i][j] = 1;
		map[j][i] = 1;
	}
	for (int k = 1; k <= 27; ++k)
		for (int i = 1; i <= 27; ++i)
			for (int j = 1; j <= 27; ++j)
				if (dis[i][j] > dis[i][k] + dis[k][j])
					dis[i][j] = dis[i][k] + dis[k][j]);
}
