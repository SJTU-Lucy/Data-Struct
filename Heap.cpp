#include<iostream>
#include<cmath>
#include<cstdio>
#include<string>
#include<algorithm>
#include<iomanip>
#include<stack>
#include<queue>

using namespace std;

template<typename T>
class Heap_min
{
private:
    int capacity;
    T* heap;
    int len;
public:
    Heap_min(int x)
    {
        capacity = x;
        heap = new T[capacity];
        len = 0;
    }
    ~Heap_min() 
    {
        delete[]heap; 
    }
    //打印节点的元素
    void print()
    {
        cout << "the current heap elements are:" << endl;
        for (int i = 1; i <= len; ++i)
            cout << heap[i] << " ";
        cout << endl;
    }
    //向下移动节点
    void minheapify(int x)
    {
        int smallest = x;
        int l, r;
        T tmp;
        while (true)
        {
            l = x << 1;
            r = l + 1;
            if (l <= len && heap[l] < heap[x]) smallest = l;
            if (r <= len && heap[r] < heap[smallest]) smallest = r;
            if (smallest != x)
            {
                tmp = heap[smallest];
                heap[smallest] = heap[x];
                heap[x] = tmp;
                x = smallest;
            }
            else break;
        }
    }
    //上浮
    void goup(int x)
    {
        int i = x;
        T tmp;
        while (i > 1 && heap[i / 2] > heap[i])
        {
            tmp = heap[i / 2];
            heap[i / 2] = heap[i];
            heap[i] = tmp;
            i = i / 2;
        }
    }
    //插入节点元素(即入队)
    void insert(T x)
    {
        heap[++len] = x;
        goup(len);
    }
    //弹出
    T pop()
    {
        T ret = heap[1];
        heap[1] = heap[len--];
        minheapify(1);
        return ret;
    }
    T Min()
    {
        return heap[1];
    }
};

template<typename T>
class Heap_max
{
private:
    T* heap;
    int len;
public:
    Heap_max(int x)
    {
        heap = new T[x];
        len = 0;
    }
    ~Heap_max()
    {
        delete[]heap;
    }
    //打印节点的元素
    void print()
    {
        cout << "the current heap elements are:" << endl;
        for (int i = 1; i <= len; ++i)
            cout << heap[i] << " ";
        cout << endl;
    }
    //向下移动节点
    void maxheapify(int x)
    {
        int biggest = x;
        int l, r;
        T tmp;
        while (true)
        {
            l = x << 1;
            r = l + 1;
            if (l <= len && heap[l] > heap[x]) biggest = l;
            if (r <= len && heap[r] > heap[biggest]) biggest = r;
            if (biggest != x)
            {
                tmp = heap[biggest];
                heap[biggest] = heap[x];
                heap[x] = tmp;
                x = biggest;
            }
            else break;
        }
    }
    //上浮
    void goup(int x)
    {
        int i = x;
        T tmp;
        while (i > 1 && heap[i / 2] < heap[i])
        {
            tmp = heap[i / 2];
            heap[i / 2] = heap[i];
            heap[i] = tmp;
            i = i / 2;
        }
    }
    //插入节点元素(即入队)
    void insert(int x)
    {
        heap[++len] = x;
        goup(len);
    }
    //弹出
    T pop()
    {
        T ret = heap[1];
        heap[1] = heap[len--];
        maxheapify(1);
        return ret;
    }
    T Max()
    {
        return heap[1];
    }
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Heap_max<int> myHeap(100);
    myHeap.insert(10);
    myHeap.insert(5);
    myHeap.insert(15);
    cout << myHeap.pop() << endl;
    cout << myHeap.pop() << endl;
    cout << myHeap.pop() << endl;
 
    return 0;
}












