#include "array.h"
#include <iostream>
#include <algorithm>

template<class Type> 
Array<Type>::Array(int Size){// 带形参的构造函数：建立最大长度为Size的数组
    if(Size <= 0){//invalid size
        std::cerr << "Invalid Array Size" << std::endl;
        this->ArraySize = 0;
        return;
    }
    this->ArraySize = Size;
    GetArray();
}

template<class Type>
void Array<Type>::GetArray(){// 私有函数：动态分配数组的存储空间
    this->elements = new Type[this->ArraySize];
    if(this->elements == NULL){
        std::cerr << "Memory allocation failed" << std::endl;
        this->ArraySize = 0;
        return;
    }
}

template<class Type>
Array<Type>::Array(const Array<Type> &x){// 复制构造函数：复制数组x以建立新数组
    this->ArraySize = x.ArraySize;
    if(this->ArraySize > 0){
        GetArray();
        Type *srcptr = x.elements;
        Type *destptr = this->elements;
        for(int i = 0; i < this->ArraySize; ++i){
            *destptr++ = *srcptr++;//equals to *(destptr++) = *(srcptr++)
        }
    } else {
        this->elements = nullptr;
    }
}

template<class Type>
Type& Array<Type>::operator[](int i){// 访问下标为i的数组元素
    if(i < 0 || i >= this->ArraySize){
        std::cerr << "Array index out of bounds" << std::endl;
        static Type dummy;
        return dummy;
    }
    return this->elements[i];
}

template<class Type>
Array<Type>::~Array(){// 析构函数：释放数组占用的存储空间
    if(this->elements != nullptr){
        delete[] this->elements;
    }
}

template<class Type>
void Array<Type>::Resize(int sz){// 修改数组长度
    if(sz <= 0){
        std::cerr << "Invalid new size" << std::endl;
        return;
    }
    if(sz == this->ArraySize){
        return; // 大小相同，无需修改
    }
    
    Type *newArray = new Type[sz];
    if(newArray == NULL){
        std::cerr << "Memory allocation failed" << std::endl;
        return;
    }
    
    int n = std::min(sz, this->ArraySize);
    Type *srcptr = this->elements;
    Type *destptr = new Array<Type>(sz);
    this->elements = destptr;
    for(int i = 0; i < n; ++i){
        *destptr++ = *srcptr++;
    }
    delete[] this->elements;
    this->ArraySize = sz;
}

template<class Type>
Array<Type>& Array<Type>::operator=(const Array<Type> &x){// 数组复制
    if(x.ArraySize <= 0){
        std::cerr << "Invalid Array Size" << std::endl;
        return *this;
    }
    if(this != &x){
        GetArray();
        int n = std::min(x.ArraySize, this->ArraySize);
        Type *srcptr = x.elements;
        Type *destptr = this->elements;
        for(int i = 0; i < n; ++i){
            *destptr++ = *srcptr++;
        }

        this->ArraySize = n;
        return *this;
    }
    else{
        std::cerr << "Array assignment to itself" << std::endl;
        return *this;
    }
}

template<class Type>
int Array<Type>::Length() const{// 取数组长度
    return this->ArraySize;
}


template<class Type>
std::ostream & operator<<(std::ostream &os, const Array<Type> &array){
    for(int i = 0; i < array.ArraySize; ++i){
        os << "Array[" << i << "] = " << array.elements[i] << std::endl;
    }
    os << "End of an Array" << std::endl;
    os << "-------------------" << std::endl;
    return os;
}


int main(){
    // 方法1: 先创建数组，然后逐个赋值
    Array<int> a(10);
    for(int i = 0; i < 10; i++) {
        a[i] = i + 1;
    }
    
    // 方法2: 使用复制构造函数
    Array<int> b(a);
    
    std::cout << a;
    std::cout << b;
    return 0;
}