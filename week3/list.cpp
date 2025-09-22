#include "list.h"

template<typename T>
listNode<T>::listNode(listNode<T> *ptr){
    link = ptr;
}

template<typename T>
listNode<T>::listNode(const T& val, listNode<T> *ptr){
    data = val;
    link = ptr;
}

template<typename T>
list<T>::list(){
    first = new listNode<T>();
}

template<typename T>
list<T>::list(const T& val){
    first = new listNode<T>(val);
}

template<typename T>
list<T>::list(list<T> &l){
    T value;
    first = new listNode<T>();
    listNode<T> *srcptr = l.first;
    listNode<T> *dstptr = first;
    while(srcptr->link != nullptr){
        value = srcptr->link->data;
        dstptr->link = new listNode<T>(value);
        dstptr = dstptr->link;
        srcptr = srcptr->link;
    }
    dstptr->link = nullptr;
}

template<typename T>
list<T>::~list(){
    makeEmpty();
}

template<typename T>
void list<T>::makeEmpty(){
    listNode<T> *p;
    while(first->link != nullptr){
        p = first->link;
        first->link = p->link;
        delete p;
    }
}

template<typename T>
int list<T>::length() const{
    listNode<T> *p = first->link;
    int count = 0;
    while(p != nullptr){
        ++count;
        p = p->link;
    }
    return count;
}

template<typename T>
listNode<T> *list<T>::getHead() const{
    return first;
}

template<typename T>
listNode<T> *list<T>::search(const T& val) const{
    listNode<T> *p = first->link;
    while(p != nullptr){
        if(p->data == val){
            return p;
        }
        p = p->link;
    }
    return nullptr;
}

template<typename T>
listNode<T> *list<T>::locate(int i) const{
    int count = 0;
    listNode<T> *p = first->link;
    while(p != nullptr){
        ++count;
        if(count == i){
            return p;
        }
    }
    return nullptr;
}

template<typename T>
bool list<T>::getData(int i, T& x) const{
    listNode<T> *p = locate(i);
    if(p == nullptr){
        return false;
    }
    else{
        x = p->data;
        if(x == p->data){
            return true;
        }
    }
    return false;
}

template<typename T>
bool list<T>::setData(int i, const T& x){
    listNode<T> *p = locate(i);
    if(p == nullptr){
        return false;
    }
    p->data = x;
    if(x == p->data){
        return true;
    }
    return false;
}

template<typename T>
bool list<T>::insert(int i, const T& x){
    if(i < 1 || i > this->length() + 1){
        std::cerr << "Invalid position" << std::endl;
        return false;
    }

    else if(i == 1){
        listNode<T> *newNode = new listNode<T>(x);
        newNode->link = first->link;
        first->link = newNode;
    }

    else if(i == this->length() + 1){
        listNode<T> *newNode = new listNode<T>(x);
        listNode<T> *p = first;
        while(p->link != nullptr){
            p = p->link;
        }
        p->link = newNode;
        newNode->link = nullptr;
    }
    
    else{
        listNode<T> *pre = locate(i - 1);
        listNode<T> *cur = pre->link;
        listNode<T> *newNode = new listNode<T>(x);
        pre->link = newNode;
        newNode->link = cur;
    }

    return true;
}

template<typename T>
bool list<T>::remove(int i){
    if(i < 1 || i > this->length()){
        std::cerr << "Invalid position" << std::endl;
        return false;
    }
    else if(i == 1){
        listNode<T> *p = first->link;
        first->link = p->link;
        delete p;
    }
    else if(i == this->length()){
        listNode<T> *p = locate(i - 1);
        listNode<T> *cur = p->link;
        p->link = nullptr;
        delete cur;
    }
    else{
        listNode<T> *pre = locate(i - 1);
        listNode<T> *cur = pre->link;
        pre->link = cur->link;
        delete cur;
    }
    return true;
}

template<typename T>
bool list<T>::isEmpty() const{
    return first->link == nullptr;
}

template<typename T>
bool list<T>::isFull() const{
    return false;
}

template<typename T>
void list<T>::sort(){
    for(int i = 0; i < this->length(); ++i){
        for(int j = i; j < this->length(); ++j){
            if(this->locate(i)->data > this->locate(j)->data){
                std::swap(this->locate(i)->data, this->locate(j)->data);
            }
        }
    }
}

template<typename T>
void list<T>::inputFront(const T& val){
    listNode<T> *newNode = new listNode<T>(val);
    newNode->link = first->link;
    first->link = newNode;
}

template<typename T>
void list<T>::inputRear(const T& val){
    listNode<T> *newNode = new listNode<T>(val);
    listNode<T> *p = first;
    while(p->link != nullptr){
        p = p->link;
    }
    p->link = newNode;
    newNode->link = nullptr;
}

template<typename T>
void list<T>::output(){
    if(this->isEmpty()){
        std::cout << "The list is empty." << std::endl;
        return;
    }
    listNode<T> *p = first->link;
    int count = 0;
    while(p != nullptr){
        std::cout << count + 1 << "{Data: " << p->data << " Self-Link: " << p << " Next-Link " << p->link << " }" << std::endl;
        count++;
        p = p->link;
    }
}

template<typename T>
list<T> & list<T>::operator=(list<T> &l){
    if(this != &l){
        this->makeEmpty();
        listNode<T> *srcptr = l.first;
        listNode<T> *destptr = this->first;
        while(srcptr != nullptr){
            destptr->link = new listNode<T>(srcptr->data);
            destptr = destptr->link;
            srcptr = srcptr->link;
        }
        destptr->link = nullptr;
    }
    else{
        std::cerr << "List assignment to itself" << std::endl;
    }
    return *this;
}

int main() {
    // 测试基本构造函数
    std::cout << "\n=== 测试构造函数 ===" << std::endl;
    list<int> l1;
    std::cout << "空链表测试 - isEmpty(): " << (l1.isEmpty() ? "true" : "false") << std::endl;
    
    // 测试插入操作
    std::cout << "\n=== 测试插入操作 ===" << std::endl;
    l1.inputFront(10);  // 前插
    l1.inputRear(20);   // 后插
    l1.insert(2, 15);   // 中间插入
    std::cout << "插入后的链表：";
    l1.output();  // 应输出：10 15 20
    std::cout << "链表长度：" << l1.length() << std::endl;

    // 测试查找操作
    std::cout << "\n=== 测试查找操作 ===" << std::endl;
    listNode<int>* found = l1.search(15);
    std::cout << "查找15是否成功：" << (found != nullptr ? "true" : "false") << std::endl;
    
    // 测试定位操作
    listNode<int>* second = l1.locate(2);
    int value;
    l1.getData(2, value);
    std::cout << "第2个元素的值：" << value << std::endl;

    // 测试修改操作
    std::cout << "\n=== 测试修改操作 ===" << std::endl;
    l1.setData(2, 25);
    l1.getData(2, value);
    std::cout << "修改后第2个元素的值：" << value << std::endl;

    // 测试排序操作
    std::cout << "\n=== 测试排序操作 ===" << std::endl;
    list<int> l2;
    l2.inputRear(30);
    l2.inputRear(10);
    l2.inputRear(20);
    std::cout << "排序前：";
    l2.output();
    l2.sort();
    std::cout << "排序后：";
    l2.output();

    // 测试复制构造和赋值运算符
    std::cout << "\n=== 测试复制操作 ===" << std::endl;
    list<int> l3(l2);  // 复制构造
    std::cout << "复制构造的链表：";
    l3.output();
    
    list<int> l4;
    l4 = l2;  // 赋值运算符
    std::cout << "赋值运算符复制的链表：";
    l4.output();

    // 测试删除操作
    std::cout << "\n=== 测试删除操作 ===" << std::endl;
    l1.remove(2);
    std::cout << "删除第2个元素后：";
    l1.output();

    // 测试清空操作
    std::cout << "\n=== 测试清空操作 ===" << std::endl;
    l1.makeEmpty();
    std::cout << "清空后isEmpty(): " << (l1.isEmpty() ? "true" : "false") << std::endl;

    return 0;
}