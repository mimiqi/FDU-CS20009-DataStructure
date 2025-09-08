#include "array.h"
#include <iostream>

template<class Type> 
Array<Type>::Array(int Size){// 带形参的构造函数：建立最大长度为Size的数组
    if(Size <= 0){//invalid size
        std::cerr << "Invalid Array Size" << std::endl;
        this.ArraySize = 0;
        return;
    }
    this.ArraySize = Size;
    GetArray();
}

template<class Type>
Array<Type>::GetArray(){// 私有函数：动态分配数组的存储空间
    this.elements = new Type[this.ArraySize];
    if(this.elements == NULL){
        std::cerr << "Memory allocation failed" << std::endl;
        this.ArraySize = 0;
        return;
    }
}

template<class Type>
Array<Type>::Array(const Array<Type> &x){// 复制构造函数：复制数组x以建立新数组
    this.ArraySize = x.ArraySize;
    GetArray();
    Type *srcptr = x.elements;
    Type *destptr = this.elements;
    for(int i = 0; i < this.ArraySize; ++i){
        *destptr++ = *srcptr++;//equals to *(destptr++) = *(srcptr++)
    }
}

template<class Type>
Array<Type>::operator[](int i){// 访问下标为i的数组元素
    if(i < 0 || i >= this.ArraySize){
        std::cerr << "Array index out of bounds" << std::endl;
        return NULL;
    }
    return this.elements[i];
}

template<class Type>
~Array(){// 析构函数：释放数组占用的存储空间
    delete[] this.elements;
}

template<class Type>
void Array<Type>::Resize(int sz){// 修改数组长度
    if(sz > 0 && sz != this.ArraySize){
        Type *newArray = new Type[sz];
        if(newArray == NULL){
            std::cerr << "Memory allocation failed" << std::endl;
            return;
        }
    }
    int n = min(sz, this.ArraySize);
    Type *srcptr = this.elements;
    Type *destptr = newArray;
    for(int i = 0; i < n; ++i){
        *destptr++ = *srcptr++;
    }
    delete[] this.elements;
    elements = newArray;
    this.ArraySize = sz;
}

template<class Type>
Array<Type>& Array<Type>::operator=(const Array<Type> &x){// 数组复制
    if(x.ArraySize <= 0){
        std::cerr << "Invalid Array Size" << std::endl;
        return *this;
    }
    if(this != &x){
        GetArray();
        int n = min(x.ArraySize, this.ArraySize);
        Type *srcptr = x.elements;
        Type *destptr = this.elements;
        for(int i = 0; i < n; ++i){
            *destptr++ = *srcptr++;
        }
        this.elements = newArray;
        this.ArraySize = n;
        return *this;
    }
    else{
        std::cerr << "Array assignment to itself" << std::endl;
        return *this;
    }
}

template<class Type>
int Array<Type>::Length() const{// 取数组长度
    return this.ArraySize;
}

template<class Type>
void Array<Type>::print() const{
    for(int i = 0; i < this.ArraySize; ++i){
        std::cout << this.elements[i] << " ";
    }
    std::cout << std::endl;
}

int main(){
    Array<int> a(10) {1,2,3,4,5,6,7,8,9,10};
    Array<int> b(a);
    std::cout << "Array b: ";
    b.print();
    return 0;
}