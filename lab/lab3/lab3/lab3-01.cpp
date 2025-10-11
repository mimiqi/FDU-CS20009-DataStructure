#include <cstdio>
#include <ctime>
#include <iostream>
#define random(a, b) (rand() % (b - a) + a)

template <class Type>
class List;

template <class Type>
class LinkNode
{
    friend class List<Type>;

public:
    LinkNode() { link = nullptr; }
    LinkNode(const Type &value)
    {
        data = value;
        link = nullptr;
    }

private:
    Type data;
    LinkNode<Type> *link;
};

template <class Type>
class List
{
public:
    List() { first = nullptr; }
    List(const Type &value)
    {
        first = new LinkNode<Type>(value);
        first->link = first;
    }
    ~List();
    LinkNode<Type> *Print();

    void Initialize(const Type arr[], int size);
    void Insert(const Type &value);

private:
    LinkNode<Type> *first;
};

template <class Type>
List<Type>::~List()
{
    if (first == nullptr)
        return;

    LinkNode<Type> *current = first;
    LinkNode<Type> *next;

    do
    {
        next = current->link;
        delete current;
        current = next;
    } while (current != first);
}

template <class Type>
LinkNode<Type> *List<Type>::Print()
{
    if (first == nullptr)
    {
        std::cout << "The list is empty." << std::endl;
        return nullptr;
    }

    LinkNode<Type> *current = first;

    do
    {
        std::cout << current->data << " ";
        current = current->link;
    } while (current != first);

    std::cout << std::endl;

    return first;
}

// 初始化循环单调非递减链表
template <class Type>
void List<Type>::Initialize(const Type arr[], int size)
{
    if (size <= 0)
        return;

    first = new LinkNode<Type>(arr[0]);
    LinkNode<Type> *current = first;

    for (int i = 1; i < size; ++i)
    {
        LinkNode<Type> *newNode = new LinkNode<Type>(arr[i]);
        current->link = newNode;
        current = newNode;
    }

    current->link = first;
}

// 插入节点到循环单调非递减链表中
template <class Type>
void List<Type>::Insert(const Type &value)//时间O(n) 空间O(1)
{
    if(first == nullptr){
        first = new LinkNode<Type>(value);
        first->link = first;
        return;
    }

    LinkNode<Type> *cur = first;
    LinkNode<Type> *next = first->link;

    // 找到链表中的最大值和最小值位置
    LinkNode<Type> *maxNode = first;
    LinkNode<Type> *minNode = first;
    LinkNode<Type> *temp = first->link;
    while(temp != first) {
        if(temp->data > maxNode->data) maxNode = temp;
        if(temp->data < minNode->data) minNode = temp;
        temp = temp->link;
    }

    // 如果插入值小于等于最小值，在最小值前插入
    if(value <= minNode->data) {
        while(cur->link != minNode) cur = cur->link;
        LinkNode<Type> *newNode = new LinkNode<Type>(value);
        cur->link = newNode;
        newNode->link = minNode;
        if(minNode == first) first = newNode;
        return;
    }

    // 如果插入值大于等于最大值，在最大值后插入
    if(value >= maxNode->data) {
        LinkNode<Type> *newNode = new LinkNode<Type>(value);
        newNode->link = maxNode->link;
        maxNode->link = newNode;
        return;
    }

    // 在中间位置插入
    cur = first;
    do {
        next = cur->link;
        if(cur->data <= value && value <= next->data) {
            LinkNode<Type> *newNode = new LinkNode<Type>(value);
            newNode->link = next;
            cur->link = newNode;
            return;
        }
        cur = next;
    } while(cur != first);
}

int main()
{

    List<int> myList;
    /*
    int a[] = {6, 9, 1, 4};
    myList.Initialize(a, 4);
    myList.Print();
    myList.Insert(2);
    myList.Print();
    */

    
    int a[] = {3, 4, 1};
    myList.Initialize(a, 3);
    myList.Print();
    myList.Insert(2);
    myList.Print();
    

    int b[] = {3, 4, 1};
    myList.Initialize(b, 3);
    myList.Print();
    myList.Insert(0);
    myList.Print();

    /*
    int *a = new int[0];
    myList.Initialize(a, 0);
    myList.Print();
    myList.Insert(2);
    myList.Print();
    */
    
    return 0;
}