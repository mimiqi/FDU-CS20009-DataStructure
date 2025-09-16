#include "sequentialList.h"
#include <iostream>



template<class Type>
SeqList<Type>::SeqList(int size){
    if(size <= 0 || size > defaultSize){
        std::cerr << "Invalid size" << std::endl;
        return;
    }
    this->maxSize = size;
    this->last = -1;
    this->list = new Type[this->maxSize];
    if(this->list == nullptr){
        std::cerr << "Memory allocation failed" << std::endl;
    }
}

template<class Type>
SeqList<Type>::~SeqList(){
    std::cout << "-----Start-----" << std::endl;
    std::cout << "SeqList destroyed" << std::endl;
    for(int i = 0; i < this->last; ++i){
        std::cout << this->list[i] << " ";
    }
    std::cout << this->list[this->last] << std::endl;
    if(this->list != nullptr){
        delete[] this->list;
        this->list = nullptr;
    }
    std::cout << "------End------" << std::endl;
    
}

template<class Type>
int SeqList<Type>::length() const{
    return this->last + 1;
}

template<class Type>
int SeqList<Type>::find(Type &x){
    for(int i = 0; i <= this->last; ++i){
        if(this->list[i] == x){
            return i;
        }
    }
    return -1;
}

template<class Type>
bool SeqList<Type>::append(Type &x){
    if(this->last == this->maxSize - 1){
        std::cerr << "This seqList is full. Failed to append." << std::endl;
        return false;
    }
    this->list[this->last + 1] = x;
    ++this->last;
    return true;
}

template<class Type>
bool SeqList<Type>::removeIndex(int i){
    if(i < 0 || i > this->last){
        std::cerr << "Invalid position. Failed to remove." << std::endl;
        return false;
    }

    for(int j = i; j < this->last; ++j){
        this->list[j] = this->list[j + 1];
    }
    --(this->last);
    return true;
}

template<class Type>
bool SeqList<Type>::isEmpty(){
    return this->last == -1;
}

template<class Type>
bool SeqList<Type>::isFull(){
    return this->last == this->maxSize - 1;
}

template<class Type>
Type SeqList<Type>::get(int i){
    if(i < 0 || i > this->last){
        std::cerr << "Invalid position. Failed to get." << std::endl;
        return -1;
    }
    return this->list[i];
}

template<class Type>
void SeqList<Type>::printAll(){
    if(this->last == -1){
        std::cerr << "No valid element." << std::endl;
        return;
    }
    std::cout << "Printing all elements: " << std::endl;
    for(int i = 0; i < this->last; ++i){
        std::cout << this->list[i] << " ";
    }
    std::cout << this->list[this->last] << std::endl;
    std::cout << "Printing end." << std::endl;
    return;
}


int main(){
    std::cout << "Input the size of the seqList: " << std::endl;
    int n;
    std::cin >> n;
    SeqList<int> a(n);
    std::cout << "Input " << n << " elements " << std::endl;
    for(int i = 0; i < n; ++i){
        int temp;
        std::cin >> temp;
        a.append(temp);
    }
    std::cout << "Length: " << a.length() << std::endl;
    std::cout << "Is Empty: " << a.isEmpty() << std::endl;
    std::cout << "Is Full: " << a.isFull() << std::endl;
    std::cout << "Get: " << a.get(0) << std::endl;
    a.printAll();

    std::cout << "Input an integer to find: " << std::endl;
    int temp;
    std::cin >> temp;
    bool flag1 = a.find(temp);
    std::cout << "Find " << temp << " :" << flag1 << std::endl;
    
    if(flag1){
        std::cout << "RemoveIndex " << temp << " :" << a.removeIndex(temp) << std::endl;
        std::cout << "Input an integer to append: " << std::endl;
        std::cin >> temp;
        std::cout << "Append " << temp << " : " << a.append(temp) << std::endl;
        a.printAll();
    }
    

    return 0;
}