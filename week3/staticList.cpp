#include "staticList.h"
#include <iostream>
#include <stdexcept>
template<typename T>
staticListNode<T>::staticListNode(){
    this->data = 0;
    this->link = -1;
}

template<typename T>
staticListNode<T>::staticListNode(const T& x){
    this->data = x;
    this->link = -1;
}


template<typename T>
staticListNode<T>::~staticListNode(){

}

template<typename T>
staticList<T>::staticList(){
    for(int i = 0; i < maxSize; ++i){
        element[i] = staticListNode<T>();
    }
    avail = 0;
    first = -1;
}

template<typename T>
staticList<T>::~staticList(){

}

template<typename T>
int staticList<T>::length() const{
    if(first == -1){
        return 0;
    }
    else{
        int count = 0;
        int p = first;
        while(p != -1){
            ++count;
            p = element[p].link;
        }
        return count;
    }
}

template<typename T>
bool staticList<T>::isEmpty() const{
    return avail == 0;
}

template<typename T>
bool staticList<T>::isFull() const{
    return this->length() == maxSize;
}

template<typename T>
int staticList<T>::search(T x) const{
    int p = first;
    if(p == -1){
        std::cerr << "Invalid position" << std::endl;
        return -1;
    }
    else{
        while(p != -1){
            if(element[p].data == x){
                return p;
            }
            else{
                p = element[p].link;
            }
        }
    }
    return -1;
}

template<typename T>
int staticList<T>::locate(int i) const{
    if(this->isEmpty()){
        std::cerr << "Invalid position" << std::endl;
        return -1;
    }
    else if(i > this->length() || i < 1){
        std::cerr << "Invalid position" << std::endl;
        return -1;
    }
    else{
        int count = 1;
        int p = first;
        while(count != i){
            p = element[p].link;
            ++count;
        }
        return p;
    }
}

template<typename T>
bool staticList<T>::append(T x){
    if(this->isFull()){
        std::cerr << "Invalid position" << std::endl;
        return false;
    }
    else if(this->isEmpty()){
        element[0].data = x;
        element[0].link = -1;
        first = 0;
        avail = 1;
        return true;
    }
    else{
        int length = this->length();
        element[length].data = x;
        element[length].link = -1;
        element[length - 1].link = length;
        avail = length + 1;
        return true;
    }
}

template<typename T>
bool staticList<T>::insert(int i, T x){
    int length = this->length();
    if(i < 1 || i > length + 1){
        std::cerr << "Invalid position" << std::endl;
        return false;
    }
    else if(i == 1){
        int pre_first = first;
        first = avail;
        element[first].data = x;
        element[first].link = pre_first;
        ++avail;
        return true;
    }
    else if(i == length + 1){
        this->append(x);
        return true;
    }
    else{
        int pre = this->locate(i - 1);
        element[avail].data = x;
        element[avail].link = element[pre].link;
        element[pre].link = avail;
        ++avail;
        return true;
    }
}

template<typename T>
bool staticList<T>::remove_index(int i){
    if(i < 1 || i > this->length()){
        std::cerr << "Invalid position" << std::endl;
        return false;
    }
    else if(i == first){
        if(element[first].link != -1){
            first = element[first].link;
        }
        else{
            element[first].link = -1;
            first = -1;
            avail = 0;
            return true;
        }
    }
    else if(i == this->length()){
        int pre = this->locate(i - 1);
        element[pre].link = -1;
        return true;
    }
    else{
        int pre = this->locate(i - 1);
        int current = this->locate(i);
        element[pre].link = element[current].link;
        element[current].link = -1;
        return true;
    }
    return false;
}

template<typename T>
T staticList<T>::getData(int i) const {
    int pos = locate(i);
    if(pos == -1) {
        return -1;
    }
    return element[pos].data;
}

template<typename T>
bool staticList<T>::remove_value(T x){
    if(this->isEmpty()){
        std::cerr << "Invalid value" << std::endl;
        return false;
    }
    else{
        // 先找到元素在数组中的位置
        int array_pos = this->search(x);
        if(array_pos == -1){
            std::cerr << "Invalid value" << std::endl;
            return false;
        }
        
        // 找到元素在链表中的位置编号
        int p = first;
        int position = 1;
        while(p != -1 && p != array_pos){
            p = element[p].link;
            ++position;
        }
        
        // 现在position是元素在链表中的位置编号
        return this->remove_index(position);
    }
}

int main(){
    // 创建静态链表
    staticList<int> list;
    
    // 测试isEmpty和append
    std::cout << "Testing isEmpty and append:" << std::endl;
    std::cout << "Is empty? " << (list.isEmpty() ? "Yes" : "No") << std::endl;
    list.append(1);
    list.append(2);
    list.append(3);
    std::cout << "After appending 1,2,3 - Is empty? " << (list.isEmpty() ? "Yes" : "No") << std::endl;
    
    // 测试length
    std::cout << "\nTesting length:" << std::endl;
    std::cout << "Length: " << list.length() << std::endl;
    
    // 测试search
    std::cout << "\nTesting search:" << std::endl;
    std::cout << "Find 2: " << list.search(2) << std::endl;
    std::cout << "Find 4: " << list.search(4) << std::endl;
    
    // 测试locate
    std::cout << "\nTesting locate:" << std::endl;
    std::cout << "Data at position 2: " << list.getData(2) << std::endl;
    
    // 测试insert
    std::cout << "\nTesting insert:" << std::endl;
    list.insert(2, 4);  // 在位置2插入4
    std::cout << "After inserting 4 at position 2" << std::endl;
    for(int i = 1; i <= list.length(); i++) {
        std::cout << "Element at " << i << ": " << list.getData(i) << std::endl;
    }
    
    // 测试remove_index
    std::cout << "\nTesting remove_index:" << std::endl;
    list.remove_index(2);  // 删除位置2的元素
    std::cout << "After removing element at position 2" << std::endl;
    for(int i = 1; i <= list.length(); i++) {
        std::cout << "Element at " << i << ": " << list.getData(i) << std::endl;
    }
    
    // 测试remove_value
    std::cout << "\nTesting remove_value:" << std::endl;
    list.remove_value(3);  // 删除值为3的元素
    std::cout << "After removing value 3" << std::endl;
    for(int i = 1; i <= list.length(); i++) {
        std::cout << "Element at " << i << ": " << list.getData(i) << std::endl;
    }
    
    return 0;
}

