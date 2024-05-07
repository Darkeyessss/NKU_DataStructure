/*根据下面的假设，重新编写类 maxHeap的方法。
1）在创建堆时，创建者应该提供两个元素maxElement和minElement。堆中没有元素比
maxElement大，也没有元素比minElement小。
2)一个n元素的堆需要一个数组 heap[0:2n+1]
3）n个元素按本节所描述的方法存储在 heap[1:n]中
4）maxElement 存储在 heap[0]中
5）minElement 存储在 heap[n+1:2n+1]中。
这些假设应该使 push 和PopMax 的代码简化。通过实验将本练习的实现与本节的实现做比较。*/
#include <iostream>
#include <vector>
using namespace std;
class MaxHeap
{
private:
    int *heap;
    int maxElement;
    int minElement;
    int count = 0;

public:
    MaxHeap(int n, int ma, int mi)
    {
        // 初始化堆
        heap = new int[2 * n + 2];
        maxElement = ma;
        minElement = mi;
        heap[0] = maxElement;
        for (int i = n + 1; i <= 2 * n + 1; i++)
        {
            heap[i] = minElement;
        }
    }

    void push(int e)
    {
        // Push
        if (e > maxElement || e < minElement)
        {
            cout << "超出范围" << endl;
            return;
        }
        else
        {
            count++;
            int i = count;
            heap[i] = e;
            // 维持顺序
            while (i > 1 && heap[i] > heap[i / 2])
            {
                swap(heap[i], heap[i / 2]);
                i /= 2;
            }
        }
    }

    void PopMax()
    {
        // Pop
        if (count <= 0)
        {
            cerr << "堆是空的" << endl;
            return;
        }
        int last = heap[count];
        count--;
        int i = 1, ic = 2; // ic是左孩子
        while (ic <= count)
        {
            // count the max element of children
            if (ic < count && heap[ic] < heap[ic + 1])
                ic++;
            if (last > heap[ic])
                break;          // find the element
            heap[i] = heap[ic]; // update
            i = ic;
            ic *= 2;
        }
        heap[i] = last;
    }
    void print()
    {
        for (int i = 1; i <= count; i++)
        {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    MaxHeap test(10, 100, -100);
    int n;
    for (int i = 0; i < 10; i++)
    {
        // cin >> n;
        test.push(i);
    }

    for (int i = 0; i < 10; i++)
    {
        test.print();
        test.PopMax();
    }
    return 0;
}