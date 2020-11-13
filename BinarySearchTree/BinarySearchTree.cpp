#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

#define minus_max −2147483647
#define positive_max 2147483647

inline int min(int a, int b)
{
    if (a < b) return a;
    else return b;
}

class BinarySearchTree
{
public:
    struct node 
    {
        int val = 0;
        node* lchild = nullptr;
        node* rchild = nullptr;
        node* parent = nullptr;
    };
    node* root = nullptr;
    //查找该值是否存在
    bool exist(const int& val)
    {
        auto p = root;
        if (!p) return false;
        while (p)
        {
            if (val == p->val) return true;
            if (val < p->val) p = p->lchild;
            else p = p->rchild;
        }
        return false;
    }
    //查找该值是否存在，若存在就把他存到一个变量中传出
    void find(const int& val, node* tmp)
    {
        auto p = root;
        while (p)
        {
            if (val == p->val)
            {
                tmp = p;
                return;
            }
            else if (val < p->val) p = p->lchild;
            else p = p->rchild;
        }
        p = nullptr;
    }
    //输出查找的路径，*rr,若不存在输出Nothing.
    void ordered_find(const int& val) 
    {
        char ans[100] = { 0 };
        int length = 0;
        ans[length++] = '*';
        for (auto p = root; p;) 
        {
            if (p->val == val) 
            {
                for (int i = 0; i < length; ++i)
                    cout << ans[i];
                cout << '\n';
                return;
            }
            else if (val < p->val) 
            {
                ans[length++] = 'l';
                p = p->lchild;
            }
            else 
            {
                ans[length++] = 'r';
                p = p->rchild;
            }
        }
        printf("Nothing.\n");
    }
    //插入val值
    void insert(const int& val) 
    {
        if (!root) 
        {
            root = new node;
            root->val = val;
            return;
        }
        //寻找
        auto p = root;
        for (; p;) 
        {
            if (p->val == val)
                return;
            if (val < p->val) 
            {
                if (p->lchild)
                    p = p->lchild;
                else 
                {
                    p->lchild = new node;
                    p->lchild->parent = p;
                    p = p->lchild;
                    break;
                }
            }
            else 
            {
                if (p->rchild)
                    p = p->rchild;
                else 
                {
                    p->rchild = new node;
                    p->rchild->parent = p;
                    p = p->rchild;
                    break;
                }
            }
        }
        p->val = val;
    }
    //删去val值
    void erase(const int& val)
    {
        auto p = root;
        for (; p;)
        {
            if (p->val == val)
            {
                //如果是叶子结点则直接删除
                if (!p->lchild && !p->rchild)
                {
                    if (p == root)
                        root = nullptr;
                    else if (p->parent->lchild == p)
                        p->parent->lchild = nullptr;
                    else
                        p->parent->rchild = nullptr;
                    delete p;
                }
                //如果只有左孩子
                else if (p->lchild && !p->rchild)
                {
                    if (p == root)
                    {
                        root = p->lchild;
                        p->lchild->parent = nullptr;
                    }
                    else if (p->parent->lchild == p)
                    {
                        p->parent->lchild = p->lchild;
                        p->lchild->parent = p->parent;
                    }
                    else
                    {
                        p->parent->rchild = p->lchild;
                        p->lchild->parent = p->parent;
                    }
                    delete p;
                }
                //如果只有右孩子
                else if(!p->lchild && p->rchild)
                {
                    if (p == root)
                    {
                        root = p->rchild;
                        p->rchild->parent = nullptr;
                    }
                    else if (p->parent->lchild == p)
                    {
                        p->parent->lchild = p->rchild;
                        p->rchild->parent = p->parent;
                    }
                    else
                    {
                        p->parent->rchild = p->rchild;
                        p->rchild->parent = p->parent;
                    }
                    delete p;
                } 
                //如果两个孩子都有，就在右边找替身
                else 
                {
                    auto q = p->rchild;
                    for (; q->lchild; q = q->lchild);
                    p->val = q->val;
                    if (q->parent->lchild == q)
                        q->parent->lchild = q->rchild;
                    else
                        q->parent->rchild = q->rchild;
                    if (q->rchild)
                        q->rchild->parent = q->parent;
                    delete q;
                }
                return;
            }
            else if (val < p->val)
                p = p->lchild;
            else
                p = p->rchild;
        }
    }
    //删去val值，若无右子树就直接左子树替代，若右子树存在就找替身
    void ordered_erase(const int& val) 
    {
        auto p = root;
        for (; p;) 
        {
            if (p->val == val)
            {
                //如果是叶子结点则直接删除
                if (!p->lchild && !p->rchild) 
                {
                    if (p == root)
                        root = nullptr;
                    else if (p->parent->lchild == p)
                        p->parent->lchild = nullptr;
                    else
                        p->parent->rchild = nullptr;
                    delete p;
                }
                //如果只有左孩子
                else if (p->lchild && !p->rchild) 
                {
                    if (p == root) 
                    {
                        root = p->lchild;
                        p->lchild->parent = nullptr;
                    }
                    else if (p->parent->lchild == p) 
                    {
                        p->parent->lchild = p->lchild;
                        p->lchild->parent = p->parent;
                    }
                    else 
                    {
                        p->parent->rchild = p->lchild;
                        p->lchild->parent = p->parent;
                    }
                    delete p;
                }
                //如果有右孩子
                else if (p->rchild) 
                {
                    auto q = p->rchild;
                    for (; q->lchild; q = q->lchild);
                    p->val = q->val;
                    if (q->parent->lchild == q)
                        q->parent->lchild = q->rchild;
                    else
                        q->parent->rchild = q->rchild;
                    if (q->rchild)
                        q->rchild->parent = q->parent;
                    delete q;
                }
                return;
            }
            else if (val < p->val)
                p = p->lchild;
            else
                p = p->rchild;
        }
    }
    //询问|x-a|的最小值
    int query(const int& val)
    {
        int Min;
        auto p = root;
        Min = abs(p->val - val);
        while (p)
        {
            Min = min(Min, abs(p->val - val));
            if (val == p->val)
                return 0;
            else if (val < p->val)
                p = p->lchild;
            else p = p->rchild;
        }
        return Min;
    }
    //寻找该数的前面最小和后面最大值
    int query_prev(const int& val)
    {
        auto p = root;
        //循环后找到目标的数
        while (p->val != val)
        {
            if (val < p->val)
                p = p->lchild;
            else p = p->rchild;
        }
        if (p->lchild == nullptr) return -1;
        else p = p->lchild;
        while (p->rchild != nullptr)
            p = p->rchild;
        return p->val;
    }
    int query_latter(const int& val)
    {
        auto p = root;
        //循环后找到目标的数
        while (p->val != val)
        {
            if (val < p->val)
                p = p->lchild;
            else p = p->rchild;
        }
        if (p->rchild == nullptr) return 1;
        else p = p->rchild;
        while (p->lchild != nullptr)
            p = p->lchild;
        return p->val;
    }
};

BinarySearchTree myTree;

int main() 
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) 
    {
        int op;
        int temp;
        scanf("\n%d %d", &op, &temp);
        if (op == 0) cout << myTree.query(temp) << '\n';
        else if (op == 1) myTree.insert(temp);
        else myTree.erase(temp);
    }

    return 0;
}
