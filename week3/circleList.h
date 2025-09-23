#ifndef CIRCLELIST_H
#define CIRCLELIST_H

template<typename T>
class circleList;  // 前向声明

template<typename T>
class circleListNode;

template<typename T>
circleListNode<T> *Josephus(circleList<T> &l, int n, int m);  // 前向声明

template<typename T>
class circleListNode{
    friend class circleList<T>;
    friend circleListNode<T> *Josephus<T>(circleList<T> &l, int n, int m);  // 声明为友元
    private:
        T data;
        circleListNode<T> *link;
    public:
        circleListNode(circleListNode<T> *ptr = nullptr);
        circleListNode(const T& val, circleListNode<T> *ptr = nullptr);
        T getData() const;
};

template<typename T>
class circleList{
    friend circleListNode<T> *Josephus<T>(circleList<T> &l, int n, int m);  // 声明为友元
    private:
        circleListNode<T> *first;
        circleListNode<T> *last;
    public:
        circleList(const T& x);//构造函数
        circleList(circleList<T> &l);//复制构造函数
        ~circleList();//析构函数
        void makeEmpty();//清空链表
        int length() const;//计算长度
        bool isEmpty() const;//判断是否为空
        bool isHead(circleListNode<T> *p) const;//判断是否为头节点
        circleListNode<T> *gethead() const;//获取头节点
        circleListNode<T> *getNext(circleListNode<T> *p) const;//获取下一个节点
        void setHead(circleListNode<T> *p);//设置头节点
        circleListNode<T> *search(const T& val) const;//查找值为val的节点
        circleListNode<T> *locate(int i) const;//查找第i个节点
        bool insert(int i, const T& x);//将原先第i个节点及以后节点后移，插入新节点成为第i个节点
        bool remove(int i, const T& x);//删除第i个节点
        void inputFront(const T& x);//前插
        void inputRear(const T& x);//后插
        void output();//输出
};

#endif