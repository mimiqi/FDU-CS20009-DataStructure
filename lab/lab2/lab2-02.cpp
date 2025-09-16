#include <cstdio>
#include <iostream>
#include <assert.h>

using namespace std;

const int defaultSize = 1010;

template <class Type>
class SeqList
{
public:
    SeqList(int size = defaultSize);
    ~SeqList() { delete[] list; }
    void PrintAll();
    int Length() const { return last + 1; }
    int Find(Type x) const;
    int Insert(Type x, int i);
    int Remove(int i);
    int removeDuplicates();
    int IsEmpty() { return last == -1; }
    int IsFull() { return last == maxSize - 1; }
    Type Get(int i);

private:
    Type *list;
    int maxSize;
    int last;
};

template <class Type>
SeqList<Type>::SeqList(int size)
{
    if (size > 0)
    {
        maxSize = size;
        last = -1;
        list = new Type[maxSize];
        if (list == NULL)
        {
            cerr << " Memory Allocation Error " << endl;
            return;
        }
    }
}

template <class Type>
Type SeqList<Type>::Get(int i)
{
    if (i < 0 || i > last)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return list[i];
}

template <class Type>
void SeqList<Type>::PrintAll()
{
    for (int i = 0; i < last; i++)
        cout << list[i] << ' ';
    cout << list[last] << endl;
}

template <class Type>
int SeqList<Type>::Find(Type x) const
{
    for (int i = 0; i <= last; i++)
        if (list[i] == x)
            return i;
    return -1;
}

template <class Type>
int SeqList<Type>::Insert(Type x, int i)
{
    if (i < 0 || i > last + 1)
    {
        cout << "ILLEGAL POSITION ";
        return -1;
    }
    if (last == maxSize - 1)
    {
        cout << "Full ";
        return -1;
    }
    last++;
    for (int j = last; j > i; j--)
        list[j] = list[j - 1];
    list[i] = x;
    return 0;
}

template <class Type>
int SeqList<Type>::Remove(int i)
{
    if (i < 0 || i > last)
        return 1;
    for (int j = i; j < last; j++)
        list[j] = list[j + 1];
    last--;
    return 0;
}

template <class Type>
int SeqList<Type>::removeDuplicates()//时间O(n) 空间O(1)
{
    // todo: 完善方法，成功返回顺序表唯一元素的数量
    if(this->last <= 0) return 0;
    if(this->last == 1) return 1;
    Type *head, *cur, *next;
    int count = 1;
    head = cur = next = list;

    while(next < list + last + 1){
        if(*next != *cur){
            cur++;
            *cur = *next;
            ++count;
        }
        else{
            next++;
        }
    }
    this->last = count - 1;
    return count;
}

int main()
{
    int arr[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};

    SeqList<int> a(sizeof(arr) / sizeof(arr[0]));
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
        a.Insert(arr[i], i);

    int expectedNums[] = {0, 1, 2, 3, 4}; // 长度正确的期望答案

    int k = a.removeDuplicates(); // 调用
    cout << k << endl;

    assert(k == sizeof(expectedNums) / sizeof(expectedNums[0]));

    for (int i = 0; i < k; i++)
    {
        assert(a.Get(i) == expectedNums[i]);
    }

    a.PrintAll();

    return 0;
}