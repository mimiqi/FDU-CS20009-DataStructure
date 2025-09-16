#include <cstdio>
#include <iostream>
using namespace std;

#define ERROR -1
#define defaultSize 10010

template <class Type>
class SeqList
{
public:
    SeqList(int size = defaultSize); // 构造函数
    ~SeqList() { delete[] list; }    // 析构函数
    void PrintAll();
    int Length() const { return last + 1; }
    int IsEmpty() { return last == -1; }
    int IsFull() { return last == maxSize - 1; }
    Type Get(int i);

    int Find(Type x) const;
    int Insert(Type x, int i);
    int Remove(int i);
    int RemoveBetween(Type x, Type y);

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
    if(this->last == -1){
        cout << "No Valid Element." << endl;
        return;
    }
    for (int i = 0; i < last; i++)
        cout << list[i] << ' ';
    cout << list[last] << endl;
    return;
}

template <class Type>
int SeqList<Type>::Find(Type x) const//时间O(n) 空间O(1)
{
    // here is your code
    for(int i = 0; i <= this->last; ++i){
        if(this->list[i] == x){
            return i;
        }
    }
    return ERROR;
}

template <class Type>
int SeqList<Type>::Insert(Type x, int i)//时间O(n) 空间O(1)
{
    // here is your code
    if(i < 0 || i > this->last + 1){
        cout << "ILLEGAL POSITION " << endl;
        return false;
    }
    
    if(this->last == maxSize - 1){
        cout << "Full " << endl;
        return false;
    }

    if(i == this->last + 1){
        this->list[this->last + 1] = x;
        ++this->last;
        return true;
    }
    else{
        for(int j = this->last; j >= i; --j){
            this->list[j + 1] = this->list[j]; 
        }
        this->list[i] = x;
        ++this->last;
        return true;
    }
}

template <class Type>
int SeqList<Type>::Remove(int i)//时间O(n) 空间O(1)
{
    // here is your code
    if(i < 0 || i > this->last){
        cout << "POSITION " << i << " IS EMPTY " << endl;
        return false;
    }
    
    for(int j = i; j < this->last; ++j){
        this->list[j] = this->list[j + 1];
    }
    --this->last;
    return true;
}

template <class Type>
int SeqList<Type>::RemoveBetween(Type x, Type y)//时间O(n) 空间O(n)
{
    // here is your code
    if(x > y){
        cout << "Invalid Range" << endl;
        return false;
    }

    Type* temp = new Type[this->maxSize];
    int cur = -1;
    for(int i = 0; i <= this->last; ++i){
        if(this->list[i] < x || this->list[i] > y){
            temp[++cur] = this->list[i];
        }
    }
    int ans = this->last - cur;
    for(int i = 0; i <= cur; ++i){
        this->list[i] = temp[i];
    }
    this->last = cur;
    delete[] temp;
    return ans;
}

int main()
{
    SeqList<int> a(5);
    int n;
    cin >> n; // 输入插入长度
    for (int i = 0; i < n; i++)
    { // 逐个输入顺序表中的值
        int temp;
        cin >> temp;
        if (a.Insert(temp, i) == -1)
            cout << "Insertion Error: " << temp << " is not in." << endl;
    }
    //a.PrintAll();
    cin >> n; // 输入查找长度
    for (int i = 0; i < n; i++)
    {
        int temp, p;
        cin >> temp;
        p = a.Find(temp);
        if (p == -1)
            cout << "Finding Error: " << temp << " is not in." << endl;
        else
            cout << temp << " is at position " << p << "." << endl;
    }
    //a.PrintAll();

    cin >> n; // 输入删除长度
    for (int i = 0; i < n; i++)
    {
        int temp, p;
        cin >> temp;
        if (a.Remove(temp) == -1)
            printf("Deletion Error.\n");
    }
    //a.PrintAll();
    int x, y;
    cin >> x;
    cin >> y;
    int k = a.RemoveBetween(x, y);
    a.PrintAll();
    cout << k << endl;
    return 0;
}