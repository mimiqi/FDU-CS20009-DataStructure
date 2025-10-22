#ifndef STACK_H
#define STACK_H

#include <iostream>

template<class T>
class Array_Stack{
    private:
        T *elements;
        int maxSize;
        int top;

    public:
        Array_Stack(int sz = 10);
        ~Array_Stack();
        int push(T val);
        T pop();
        T getTop();
        void makeEmpty();
        bool isEmpty();
        bool isFull();
        int getSize();
};

template<class T>
class DoubleStack{
    private:
        int maxSize;
        T *space;
        int t[2], b[2];

    public:
        DoubleStack(int sz = 20);
        ~DoubleStack();
        int push(T x, int i);
        T pop(int i);
        T getTop(int i);
        void makeEmpty(int i);
        bool isEmpty(int i);
        bool isFull();
        void print();
};


// 前向声明
template<class T>
class Linked_Stack_Node;

template<class T>
class Linked_Stack{
    friend class Linked_Stack_Node<T>;
    private:
        Linked_Stack_Node<T> *top;
    public:
        Linked_Stack();
        ~Linked_Stack();
        void push(T val);
        T pop();
        T getTop();
        void makeEmpty();
        bool isEmpty();
        bool isFull();
        int getSize();
};

template<class T>
class Linked_Stack_Node{
    friend class Linked_Stack<T>;
    private:
        T data;
        Linked_Stack_Node<T> *link;
    public:
        Linked_Stack_Node(const T& val, Linked_Stack_Node<T> *ptr = nullptr);
        ~Linked_Stack_Node();
        T getData();
};
#endif