#include "stack.h"
#include <iostream>

template<class T>
Array_Stack<T>::Array_Stack(int sz){
    maxSize = sz;
    elements = new T[sz];
    top = -1;
}

template<class T>
Array_Stack<T>::~Array_Stack(){
    delete [] elements;
    std::cout << "Array_Stack deleted." << std::endl;
}

template<class T>
int Array_Stack<T>::push(T val){
    if(this->isFull()){
        std::cerr << "This Array_Stack is full." << std::endl;
        return -1;  // 失败时返回-1
    }
    else{
        elements[++top] = val;
        return top;
    }
}

template<class T>
T Array_Stack<T>::pop(){
    if(this->isEmpty()){
        std::cerr << "This Array_Stack is empty." << std::endl;
        return T();  // 返回默认构造的值
    }
    else{
        T ans = elements[top];
        --top;
        return ans;
    }
}

template<class T>
T Array_Stack<T>::getTop(){
    if(this->isEmpty()){
        std::cerr << "This Array_Stack is empty." << std::endl;
        return T();  // 返回默认构造的值
    }
    else{
        T ans = elements[top];
        return ans;
    }

}

template<class T>
void Array_Stack<T>::makeEmpty(){
    this->top = -1;
}

template<class T>
bool Array_Stack<T>::isEmpty(){
    return this->top == -1;
}

template<class T>
bool Array_Stack<T>::isFull(){
    return this->top == this->maxSize - 1;
}

template<class T>
int Array_Stack<T>::getSize(){
    return this->top + 1;
}

template<class T>
DoubleStack<T>::DoubleStack(int sz){
    this->maxSize = sz;
    this->space = new T[sz];
    t[0] = b[0] = -1;
    t[1] = b[1] = this->maxSize;
}

template<class T>
DoubleStack<T>::~DoubleStack(){
    delete [] space;
    std::cout << "DoubleStack deleted." << std::endl;
}

template<class T>
int DoubleStack<T>::push(T x, int i){
    if(this->isFull()){
        std::cerr << "target stack is full." << std::endl;
        return -1;  // 失败时返回-1
    }
    else{
        if(i == 0){
            space[++t[0]] = x;
            return t[0];
        }
        if(i == 1){
            space[--t[1]] = x;
            return t[1];
        }
        return -1;  // 无效索引时返回-1
    }
}

template<class T>
T DoubleStack<T>::pop(int i){
    if(this->isEmpty(i)){
        std::cerr << "target stack is empty." << std::endl;
        return T();  // 返回默认构造的值
    }
    else{
        if(i == 0){
            return space[t[0]--];
        }
        if(i == 1){
            return space[t[1]++];
        }
        return T();  // 无效索引时返回默认值
    }
}

template<class T>
T DoubleStack<T>::getTop(int i){
    if(this->isEmpty(i)){
        std::cerr << "target stack is empty." << std::endl;
        return T();  // 返回默认构造的值
    }
    else{
        if(i == 0){
            return space[t[0]];
        }
        if(i == 1){
            return space[t[1]];
        }
        return T();  // 无效索引时返回默认值
    }
}

template<class T>
void DoubleStack<T>::makeEmpty(int i){
    if(i <= -1 || i >= 2){
        std::cerr << "Invalid index." <<std::endl;
    }
    else{
        if(i == 0){
            t[0] = b[0];
        }
        if(i == 1){
            t[1] = b[1];
        }
    }
}

template<class T>
bool DoubleStack<T>::isEmpty(int i){
    if(i <= -1 || i >= 2){
        std::cerr << "Invalid index." <<std::endl;
        return true;  // 无效索引时返回true（视为空）
    }
    else{
        if(t[i] == b[i]){
            return true;
        }
        return false;
    }
}

template<class T>
bool DoubleStack<T>::isFull(){
    if(t[0] + 1 == t[1]){
        return true;
    }
    return false;
}

template<class T>
void DoubleStack<T>::print(){
    std::cout << "stack[0]: " ;
    if(this->isEmpty(0)){
        std::cout << "is empty." << std::endl;
    }
    else{
        for(int i = b[0] + 1; i <= t[0]; ++i){
            std::cout << space[i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "stack[1]: " ;
    if(this->isEmpty(1)){
        std::cout << "is empty." << std::endl;
    }
    else{
        for(int i = b[1] - 1; i >= t[1]; --i){
            std::cout << space[i] << " ";
        }
        std::cout << std::endl;
    }
}

// ==================== Linked_Stack_Node 实现 ====================

template<class T>
Linked_Stack_Node<T>::Linked_Stack_Node(const T& val, Linked_Stack_Node<T> *ptr) : data(val), link(ptr) {
    // 构造函数：初始化数据和链接指针
}

template<class T>
Linked_Stack_Node<T>::~Linked_Stack_Node() {
    // 析构函数：节点删除时不需要特殊处理
    // 因为链表结构由Linked_Stack管理
}

template<class T>
T Linked_Stack_Node<T>::getData() {
    return this->data;
}

// ==================== Linked_Stack 实现 ====================

template<class T>
Linked_Stack<T>::Linked_Stack() {
    this->top = nullptr;  // 初始时栈顶为空
}

template<class T>
Linked_Stack<T>::~Linked_Stack() {
    this->makeEmpty();  // 清空栈，释放所有节点
    std::cout << "Linked_Stack deleted." << std::endl;
}

template<class T>
void Linked_Stack<T>::push(T val) {
    // 创建新节点，新节点的link指向当前栈顶
    Linked_Stack_Node<T> *newNode = new Linked_Stack_Node<T>(val, this->top);
    this->top = newNode;  // 更新栈顶指针
}

template<class T>
T Linked_Stack<T>::pop() {
    if(this->isEmpty()) {
        std::cerr << "Linked_Stack is empty." << std::endl;
        return T();  // 返回默认构造的值
    }
    else {
        Linked_Stack_Node<T> *temp = this->top;  // 保存当前栈顶节点
        T data = temp->getData();                // 获取数据
        this->top = this->top->link;             // 更新栈顶指针
        delete temp;                             // 删除原栈顶节点
        return data;
    }
}

template<class T>
T Linked_Stack<T>::getTop() {
    if(this->isEmpty()) {
        std::cerr << "Linked_Stack is empty." << std::endl;
        return T();  // 返回默认构造的值
    }
    else {
        return this->top->getData();
    }
}

template<class T>
void Linked_Stack<T>::makeEmpty() {
    while(!this->isEmpty()) {
        this->pop();  // 逐个弹出所有元素
    }
}

template<class T>
bool Linked_Stack<T>::isEmpty() {
    return this->top == nullptr;
}

template<class T>
bool Linked_Stack<T>::isFull() {
    // 链表实现的栈理论上不会满（除非内存耗尽）
    // 这里返回false表示不会因为栈满而无法入栈
    return false;
}

template<class T>
int Linked_Stack<T>::getSize() {
    int count = 0;
    Linked_Stack_Node<T> *current = this->top;
    while(current != nullptr) {
        count++;
        current = current->link;
    }
    return count;
}


int main(){
    Array_Stack<int> as(10);
    for(int i = 0; i < 5; ++i){
        as.push(i);
    }
    std::cout << as.pop() << " supposed to be 4" << std::endl;
    std::cout << as.getTop() << " supposed to be 3" << std::endl;
    std::cout << std::boolalpha << as.isEmpty() << " supposed to be false" << std::endl;
    std::cout << std::boolalpha << as.isFull() << " supposed to be false" << std::endl;
    std::cout << as.getSize() << " supposed to be 4" << std::endl;

    std::cout << "---DoubleStack test---" <<std::endl;
    DoubleStack<int> ds(10); 
    for(int i = 0; i < 5; ++i){
        ds.push(i, 0);
    }

    for(int i = 9; i > 6; --i){
        ds.push(i, 1);
    }

    std::cout << ds.pop(0) << " supposed to be 4" <<std::endl;
    std::cout << ds.getTop(0) << " supposed to be 3" <<std::endl;
    std::cout << std::boolalpha << ds.isEmpty(1) << " supposed to be false" << std::endl;
    std::cout << std::boolalpha << ds.isFull() << " supposed to be false" << std::endl;
    ds.print();
    
    std::cout << "---LinkedStack test---" << std::endl;
    Linked_Stack<int> ls;
    for(int i = 0; i < 5; ++i){
        ls.push(i);
    }
    std::cout << ls.pop() << " supposed to be 4" << std::endl;
    std::cout << ls.getTop() << " supposed to be 3" << std::endl;
    std::cout << std::boolalpha << ls.isEmpty() << " supposed to be false" << std::endl;
    std::cout << std::boolalpha << ls.isFull() << " supposed to be false" << std::endl;
    std::cout << ls.getSize() << " supposed to be 4" << std::endl;
}