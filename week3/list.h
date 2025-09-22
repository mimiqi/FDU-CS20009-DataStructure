#ifndef LIST_H
#define LIST_H

#include <iostream>

template<typename T>
class list;  // 前向声明

template<typename T>
class listNode {
    friend class list<T>;  // 声明list<T>为友元类
private:
    T data;
    listNode<T> *link;
public:
    listNode(listNode<T> *ptr = nullptr);  // 构造函数
    listNode(const T& val, listNode<T> *ptr = nullptr);  // 构造函数
};

template<typename T>
class list {
private:
    listNode<T> *first;
public:
    list();  // 构造函数
    list(const T& val);  // 构造函数
    list(list<T> &l);  // 复制构造函数
    ~list();  // 析构函数
    void makeEmpty();  // 清空链表
    int length() const;  // 计算长度
    listNode<T> *getHead() const;  // 返回附加头节点地址
    listNode<T> *search(const T& val) const;  // 查找值为val的节点
    listNode<T> *locate(int i) const;  // 查找第i个元素的地址
    bool getData(int i, T& x) const;  // 获取第i个元素的值并放在x中
    bool setData(int i, const T& x);  // 设置第i个元素的值
    bool insert(int i, const T& x);  // 在第i个位置插入x
    bool remove(int i);  // 删除第i个元素
    bool isEmpty() const;  // 判断链表是否为空
    bool isFull() const;  // 判断链表是否已满
    void sort();  // 排序
    void inputFront(const T& val);  // 前插
    void inputRear(const T& val);  // 尾插
    void output();  // 输出
    list<T> & operator=(list<T> &l);  // 赋值运算符
};


#endif