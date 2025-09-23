#include "circleList.h"
#include <iostream>

template<typename T>
circleListNode<T>::circleListNode(circleListNode<T> *ptr){
    this->link = ptr;
}

template<typename T>
circleListNode<T>::circleListNode(const T& val, circleListNode<T> *ptr){
    this->data = val;
    this->link = ptr;
}

template<typename T>
circleList<T>::circleList(const T& x){//构造函数
    this->first = new circleListNode<T>();
    this->first->link = new circleListNode<T>(x);
    this->last = this->first->link;
    this->last->link = this->first->link;
}

template<typename T>
circleList<T>::circleList(circleList<T> &l){//复制构造函数
    this->first = new circleListNode<T>();
    circleListNode<T> *srcptr = l.first->link;  // 从第一个实际节点开始
    circleListNode<T> *dstptr = this->first;
    do {
        dstptr->link = new circleListNode<T>(srcptr->data);
        this->last = dstptr->link;
        dstptr = dstptr->link;
        srcptr = srcptr->link;
    } while(srcptr != l.first->link);  // 直到回到起点
    this->last->link = this->first->link;
}

template<typename T>
circleList<T>::~circleList(){//析构函数
    makeEmpty();
}

template<typename T>
int circleList<T>::length() const{//计算长度
    if(isEmpty()) return 0;
    int count = 1;
    circleListNode<T> *p = this->first->link;
    while(p != this->last){
        ++count;
        p = p->link;
    }
    return count;
}

template<typename T>
bool circleList<T>::isEmpty() const{//判断是否为空
    if(this->first->link == nullptr){
        return true;
    }
    return false;
}

template<typename T>
bool circleList<T>::isHead(circleListNode<T> *p) const{//判断是否为头节点
    return p == this->first;
}

template<typename T>
circleListNode<T> *circleList<T>::gethead() const{//获取头节点
    return this->first;
}

template<typename T>
circleListNode<T> *circleList<T>::getNext(circleListNode<T> *p) const{//获取下一个节点
    if(p == nullptr){
        return nullptr;
    }
    return p->link;
}

template<typename T>
void circleList<T>::setHead(circleListNode<T> *p){//设置头节点
    if(p == nullptr){
        return;
    }
    circleListNode<T> *q = this->first;
    while(q->link != p){
        q = q->link;
    }
    this->last = q;
    this->first->link = p;
}

template<typename T>
circleListNode<T> *circleList<T>::search(const T& val) const{//查找值为val的节点
    if(this->isEmpty()){
        return nullptr;
    }
    circleListNode<T> *p = this->first->link;
    do{
        if(p->data == val){
            return p;
        }
        p = p->link;
    }while(p != this->last->link);
    return nullptr;
}

template<typename T>
circleListNode<T> *circleList<T>::locate(int i) const{//查找第i个节点
    if(this->isEmpty()){
        return nullptr;
    }
    circleListNode<T> *p = this->first->link;
    int count = 1;
    while(count != i){
        p = p->link;
        ++count;
    }
    return p;
}

template<typename T>
bool circleList<T>::insert(int i, const T& x){//将原先第i个节点及以后节点后移，插入新节点成为第i个节点
    if(i == this->length() + 1){
        this->inputRear(x);
        return true;
    }
    if(i == 1){
        this->inputFront(x);
        return true;
    }
    if(i < 1 || i > this->length() + 1){
        return false;
    }
    if(i > 1){
        circleListNode<T> *p = this->locate(i - 1);
        circleListNode<T> *q = this->locate(i);
        circleListNode<T> *newNode = new circleListNode<T>(x);
        newNode->link = q;
        p->link = newNode;
        return true;
    }
    return false;
}

template<typename T>
bool circleList<T>::remove(int i, const T& x){//删除第i个节点
    if(i < 1 || i > this->length()){
        return false;
    }
    if(i < this->length()){
        circleListNode<T> *p = this->locate(i - 1);
        circleListNode<T> *q = this->locate(i + 1);
        delete p->link;
        p->link = q;
        return true;
    }
    if(i == this->length()){
        circleListNode<T> *p = this->locate(i - 1);
        delete p->link;
        p->link = this->first->link;
        this->last = p;
        return true;
    }
    return false;
}

template<typename T>
void circleList<T>::inputFront(const T& x){//前插
    circleListNode<T> *newNode = new circleListNode<T>(x);
    if(isEmpty()){
        this->first->link = newNode;
        this->last = newNode;
        newNode->link = newNode;
    } else {
        newNode->link = this->first->link;
        this->first->link = newNode;
        this->last->link = newNode;
    }
}

template<typename T>
void circleList<T>::inputRear(const T& x){//后插
    circleListNode<T> *newNode = new circleListNode<T>(x);
    if(isEmpty()){
        this->first->link = newNode;
        this->last = newNode;
        newNode->link = newNode;
    } else {
        newNode->link = this->first->link;
        this->last->link = newNode;
        this->last = newNode;
    }
}

template<typename T>
void circleList<T>::output(){//输出
    if(this->isEmpty()){
        std::cout << "The list is empty." << std::endl;
        return;
    }
    circleListNode<T> *p = this->first->link;
    int count = 0;
    do {
        std::cout << count + 1 << "{Data: " << p->data << " Self-Link: " << p << " Next-Link " << p->link << " }" << std::endl;
        count++;
        p = p->link;
    } while(p != this->first->link);
}

template<typename T>
void circleList<T>::makeEmpty() {
    if(isEmpty()) return;
    
    // 先保存头节点
    circleListNode<T> *header = first;
    // 清空头节点的连接
    first = nullptr;
    last = nullptr;
    
    // 删除头节点
    if(header != nullptr) {
        circleListNode<T> *del = header;
        if(header->link != nullptr){
            header = header->link;
        }
        delete del;
    }
}

template<typename T>
circleListNode<T> *Josephus(circleList<T> &l, int n, int m){
    if(l.isEmpty() || n <= 0 || m <= 0) return nullptr;
    
    circleListNode<T> *p = l.gethead()->link;  // 从第一个实际节点开始
    circleListNode<T> *pre = l.last;  // pre初始化为最后一个节点
    
    for(int i = 1; i < n; ++i){
        for(int j = 1; j < m; ++j){
            pre = p;
            p = p->link;
        }
        pre->link = p->link;
        std::cout << p->data << " is removed" << std::endl;
        delete p;
        p = pre->link;
    }

    return p;  // 返回最后剩下的节点
}

template<typename T>
T circleListNode<T>::getData() const{
    return this->data;
}

int main() {
    // 测试构造函数和输出函数
    std::cout << "\n=== 测试构造函数和输出 ===" << std::endl;
    circleList<int> l1(1);  // 创建循环链表，初始值为1
    std::cout << "初始链表：" << std::endl;
    l1.output();
    std::cout << "链表长度：" << l1.length() << std::endl;

    // 测试前插和后插
    std::cout << "\n=== 测试前插和后插 ===" << std::endl;
    l1.inputFront(0);  // 在头部插入0
    l1.inputRear(2);   // 在尾部插入2
    std::cout << "插入0和2后的链表：" << std::endl;
    l1.output();

    // 测试中间插入
    std::cout << "\n=== 测试中间插入 ===" << std::endl;
    l1.insert(2, 5);  // 在第2个位置插入5
    std::cout << "在位置2插入5后的链表：" << std::endl;
    l1.output();

    // 测试查找函数
    std::cout << "\n=== 测试查找函数 ===" << std::endl;
    circleListNode<int>* found = l1.search(5);
    std::cout << "查找值5是否成功：" << (found != nullptr ? "true" : "false") << std::endl;

    // 测试定位函数
    std::cout << "\n=== 测试定位函数 ===" << std::endl;
    circleListNode<int>* pos = l1.locate(2);
    if(pos != nullptr) {
        std::cout << "第2个位置的节点找到" << std::endl;
    }

    // 测试头节点相关函数
    std::cout << "\n=== 测试头节点相关函数 ===" << std::endl;
    circleListNode<int>* head = l1.gethead();
    std::cout << "获取头节点是否成功：" << (head != nullptr ? "true" : "false") << std::endl;
    std::cout << "是否为头节点：" << l1.isHead(head) << std::endl;
    
    // 测试获取下一个节点
    std::cout << "\n=== 测试获取下一个节点 ===" << std::endl;
    circleListNode<int>* next = l1.getNext(head);
    std::cout << "获取下一个节点是否成功：" << (next != nullptr ? "true" : "false") << std::endl;

    // 测试删除操作
    std::cout << "\n=== 测试删除操作 ===" << std::endl;
    int x;
    bool removeResult = l1.remove(2, x);
    std::cout << "删除第2个位置是否成功：" << (removeResult ? "true" : "false") << std::endl;
    std::cout << "删除后的链表：" << std::endl;
    l1.output();

    // 测试复制构造函数
    std::cout << "\n=== 测试复制构造函数 ===" << std::endl;
    circleList<int> l2(l1);  // 复制l1创建l2
    std::cout << "复制构造的新链表：" << std::endl;
    l2.output();

    // 测试空链表判断
    std::cout << "\n=== 测试空链表判断 ===" << std::endl;
    circleList<int> emptyList(0);
    std::cout << "新链表是否为空：" << (emptyList.isEmpty() ? "true" : "false") << std::endl;

    // 测试边界情况
    std::cout << "\n=== 测试边界情况 ===" << std::endl;
    // 测试在空链表上的操作
    circleList<int> l3(3);
    std::cout << "在空链表上删除节点：" << l3.remove(2, x) << std::endl;
    std::cout << "在无效位置插入节点：" << l3.insert(5, 10) << std::endl;
    
    // 测试在链表首尾位置的操作
    std::cout << "\n=== 测试首尾位置操作 ===" << std::endl;
    l3.insert(1, 1);  // 在首部插入
    l3.insert(l3.length() + 1, 5);  // 在尾部插入
    std::cout << "首尾插入后的链表：" << std::endl;
    l3.output();

    std::cout << "\n=== 测试Josephus问题 ===" << std::endl;
    // 创建一个有5个人的环
    circleList<int> josephusCircle(1);  // 先创建节点1
    for(int i = 2; i <= 10; i++) {
        josephusCircle.inputRear(i);    // 依次添加节点2,3,4,5
    }
    std::cout << "初始环：" << std::endl;
    josephusCircle.output();

    std::cout << "开始约瑟夫问题(n=10, m=7)：" << std::endl;
    circleListNode<int>* survivor = Josephus(josephusCircle, 10, 7);
    if(survivor != nullptr) {
        std::cout << "最后剩下的人是：" << survivor->getData() << std::endl;
    }

    // 验证最终环的状态
    std::cout << "最终环的状态：" << std::endl;
    josephusCircle.output();
    return 0;
}