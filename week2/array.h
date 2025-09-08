#ifndef ARRAY_H
#define ARRAY_H

const int DefaultSize = 30;

template<class Type> class Array{
    public:
    Array(int Size = DefaultSize);//构造函数
    Array(const Array<Type> &x);//复制构造函数
    ~Array();//析构函数
    Array<Type>& operator=(const Array<Type> &x);//数组复制
    Type& operator[](int i);//访问下标为i的数组元素
    Type* operator*() const;//指针转换
    int Length() const;//取数组长度
    void Resize(int newSize);//修改数组长度
    void print() const;
    private:
    Type *elements;//动态数组
    int ArraySize;//数组元素个数
    void GetArray();//动态分配数组的存储空间
};


#endif