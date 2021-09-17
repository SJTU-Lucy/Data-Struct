#include<iostream>
#include<cmath>
#include<cstdio>
#include<string>
#include<algorithm>
#include<iomanip>
#include<stack>
//#include<vector>
//#include<set>
#include<queue>
//#include<map>

using namespace std;

#define set_max 999999

//注：建立的线段树头节点放在0,不是1，左2*node+1,右2*node+2
template<typename T>
class segmentTree_point
{
public:
    struct node
    {
        T min = set_max;
        T sum;
    };
    node* tree;
    segmentTree_point() {}
    segmentTree_point(int x)
    {
        tree = new node[x];
    }
    ~segmentTree_point()
    {
        delete[]tree;
    }
    void giveSpace(int x)
    {
        tree = new node[x];
    }
    //更新node节点信息（由下面得到）
    void goup(int node)
    {
        int leftnode = node * 2 + 1;
        int rightnode = node * 2 + 2;
        tree[node].sum = tree[leftnode].sum + tree[rightnode].sum;
        tree[node].min = min(tree[leftnode].min, tree[rightnode].min);
    }
    //start是当前所在节点的左端点，end是当前所在节点的右端点
    void build_tree(int node, int start, int end,T arr[])
    {
        //如果到达叶节点，就把对应的值放进去
        if (start == end)
        {
            tree[node].sum = arr[start];
            tree[node].min = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        int leftnode = node * 2 + 1;
        int rightnode = node * 2 + 2;
        build_tree(leftnode, start, mid);
        build_tree(rightnode, mid + 1, end);
        goup(node);          //node节点更新
    }
    //节点信息的更新原数列中第idx个改成val
    void update_tree_point(int node, int start, int end, int idx, T val,T arr[])
    {
        //找到该节点了
        if (start == end)
        {
            arr[idx] = val;
            tree[node].sum = val;
            tree[node].min = val;
            return;
        }
        int mid = (start + end) / 2;
        int leftnode = node * 2 + 1;
        int rightnode = node * 2 + 2;
        //确定寻找的方向
        if (idx >= start && idx <= mid)
            update_tree_point(leftnode, start, mid,idx, val);
        else update_tree_point(rightnode, mid + 1, end, idx, val);
        goup(node);
    }
    //求[L,R]区间和(针对点类),start和end为全部区间的范围
    T query_sum(int node, int start, int end, int L, int R)
    {
        //被完全包括
        if (start >= L && end <= R)
            return tree[node].sum;
        //和该区间无关
        else if (start > R || end < L)
            return 0;
        //找到叶节点
        else if (start == end)
            return tree[node].sum;

        int mid = (start + end) / 2;
        int leftnode = node * 2 + 1;
        int rightnode = node * 2 + 2;
        T leftsum = query_sum(leftnode, start, mid, L, R);
        T rightsum = query_sum(rightnode, mid + 1, end, L, R);
        return leftsum + rightsum;
    }
    //求[L,R]区间最小值(针对点类),start和end为全部区间的范围
    T query_min(int node, int start, int end, int L, int R)
    {
        //被完全包括
        if (start >= L && end <= R)
            return tree[node].min;
        //和该区间无关
        else if (start > R || end < L)
            return set_max;
        //找到叶节点
        else if (start == end)
            return tree[node].min;

        int mid = (start + end) / 2;
        int leftnode = node * 2 + 1;
        int rightnode = node * 2 + 2;
        T leftmin = query_min(leftnode, start, mid, L, R);
        T rightmin = query_min(rightnode, mid + 1, end, L, R);
        return min(leftmin , rightmin);
    }
};

template<typename T>
class segmentTree_segment
{
public:
    struct node
    {
        T sum;
        T lazy = 0;
    };
    node* tree;
    segmentTree_segment() {}
    segmentTree_segment(int x)
    {
        tree = new node[x];
    }
    ~segmentTree_segment() 
    {
        delete[]tree;
    }
    //更新node节点信息（由下面得到）
    void goup(int node)
    {
        int leftnode = node * 2 + 1;
        int rightnode = node * 2 + 2;
        tree[node].sum = tree[leftnode].sum + tree[rightnode].sum;
    }
    //start是当前所在节点的左端点，end是当前所在节点的右端点
    void build_tree(int node, int start, int end,T arr[])
    {
        if (start == end)
        {
            tree[node].sum = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        int leftnode = node * 2 + 1;
        int rightnode = node * 2 + 2;
        build_tree(leftnode, start, mid);
        build_tree(rightnode, mid + 1, end);
        goup(node);
    }
    //给区间为[start,end]的node加上add(打标记)
    void update_tree_segment(int node, int start, int end, int add)
    {
        tree[node].lazy += add;
        tree[node].sum += (end - start + 1) * add;//维护区间和
    }
    //标记下传
    void update_tree_pushdown(int node, int start, int end)
    {
        if (start > end) return;
        if (tree[node].lazy == 0) return;
        int mid = (start + end) / 2;
        int leftnode = 2 * node + 1;
        int rightnode = 2 * node + 2;
        if (tree[node].lazy == 0) return;
        update_tree_segment(leftnode, start, mid, tree[node].lazy);    //下传到左子树
        update_tree_segment(rightnode, mid + 1, end, tree[node].lazy); //下传到右子树
        tree[node].lazy = 0; //清零标记
    }
    // 求[L, R]区间和(针对线段类)
    T query_sum_segment(int node, int start, int end, int L, int R)
    {   
        //当前区间小，目标区间大，被完全包括
        if (start >= L && end <= R)
            return tree[node].sum;
        int mid = (start + end) / 2;
        int leftnode = node * 2 + 1;
        int rightnode = node * 2 + 2;
        T res = 0;
        update_tree_pushdown(node, start, end);
        //在mid左右的部分分别求取
        if (L <= mid)
            res += query_sum_segment(leftnode, start, mid, L, R);
        if (R > mid)
            res += query_sum_segment(rightnode, mid + 1, end, L, R);
        return res;
    }
    //给区间[L,R]所有的数加上add(具体调用的时候用这个)
    void update_tree_modify(int node, int start, int end, int L, int R, int add)
    {
        //完全包含在区间内，就加上标记
        if (start >= L && end <= R)
            return update_tree_segment(node, start, end, add);
        int mid = (start + end) / 2;
        int leftnode = 2 * node + 1;
        int rightnode = 2 * node + 2;
        update_tree_pushdown(node, start, end);//到达每一个结点都要下传标记
        //分别修改mid左边和右边的子树
        if (L <= mid) update_tree_modify(leftnode, start, mid, L, R, add);   //修改左子树
        if (R > mid)  update_tree_modify(rightnode, mid + 1, end, L, R, add);//修改右子树
        goup(node);
    }
};
















