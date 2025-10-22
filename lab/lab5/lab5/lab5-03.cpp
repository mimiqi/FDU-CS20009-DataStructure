#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

class MyCircularQueue
{
private:
    vector<int> data;  // 存储队列数据的数组
    int head;          // 队首指针
    int tail;          // 队尾指针
    int size;          // 队列当前元素个数
    int capacity;      // 队列容量

public:
    // 构造器，设置队列长度为k
    MyCircularQueue(int k)//时间O(k) 空间O(k)
    {
        if(k <= 0){
            cerr << "Invalid size of queue" << endl;
            exit(1);
        }
        capacity = k;
        data.resize(k);
        head = 0;
        tail = 0;
        size = 0;
    }

    // 向循环队列插入一个元素
    bool enQueue(int value)//时间O(1) 空间O(1)
    {
        if(isFull()){
            return false;  // 队列已满，无法插入
        }
        data[tail] = value;
        tail = (tail + 1) % capacity;  // 循环到下一个位置
        size++;
        return true;
    }

    // 从循环队列中删除一个元素
    bool deQueue()//时间O(1) 空间O(1)
    {
        if(isEmpty()){
            return false;  // 队列为空，无法删除
        }
        head = (head + 1) % capacity;  // 循环到下一个位置
        size--;
        return true;
    }

    // 从队首获取元素
    int Front()//时间O(1) 空间O(1)
    {
        if(isEmpty()){
            return -1;
        }
        return data[head];
    }

    // 获取队尾元素
    int Rear()//时间O(1) 空间O(1)
    {
        if(isEmpty()){
            return -1;
        }
        // 队尾指针指向下一个空位置，需要回退一位
        int rearIndex = (tail - 1 + capacity) % capacity;
        return data[rearIndex];
    }

    // 检查循环队列是否为空
    bool isEmpty()//时间O(1) 空间O(1)
    {
        return size == 0;
    }

    // 检查循环队列是否已满
    bool isFull()//时间O(1) 空间O(1)
    {
        return size == capacity;
    }
};

void testCircularQueue() {
    cout << "=== 测试循环队列实现 ===" << endl;
    
    // 测试1：基本操作
    cout << "\n1. 基本操作测试 (容量=3):" << endl;
    MyCircularQueue q(3);
    
    cout << "isEmpty(): " << boolalpha << q.isEmpty() << " (期望: true)" << endl;
    cout << "isFull(): " << boolalpha << q.isFull() << " (期望: false)" << endl;
    
    // 测试2：入队操作
    cout << "\n2. 入队操作测试:" << endl;
    cout << "enQueue(1): " << boolalpha << q.enQueue(1) << " (期望: true)" << endl;
    cout << "Front(): " << q.Front() << " (期望: 1)" << endl;
    cout << "Rear(): " << q.Rear() << " (期望: 1)" << endl;
    
    cout << "enQueue(2): " << boolalpha << q.enQueue(2) << " (期望: true)" << endl;
    cout << "Front(): " << q.Front() << " (期望: 1)" << endl;
    cout << "Rear(): " << q.Rear() << " (期望: 2)" << endl;
    
    cout << "enQueue(3): " << boolalpha << q.enQueue(3) << " (期望: true)" << endl;
    cout << "isFull(): " << boolalpha << q.isFull() << " (期望: true)" << endl;
    cout << "Front(): " << q.Front() << " (期望: 1)" << endl;
    cout << "Rear(): " << q.Rear() << " (期望: 3)" << endl;
    
    // 测试3：队列已满时的入队
    cout << "\n3. 队列已满测试:" << endl;
    cout << "enQueue(4): " << boolalpha << q.enQueue(4) << " (期望: false)" << endl;
    
    // 测试4：出队操作
    cout << "\n4. 出队操作测试:" << endl;
    cout << "deQueue(): " << boolalpha << q.deQueue() << " (期望: true)" << endl;
    cout << "Front(): " << q.Front() << " (期望: 2)" << endl;
    cout << "Rear(): " << q.Rear() << " (期望: 3)" << endl;
    cout << "isFull(): " << boolalpha << q.isFull() << " (期望: false)" << endl;
    
    // 测试5：循环特性
    cout << "\n5. 循环特性测试:" << endl;
    cout << "enQueue(4): " << boolalpha << q.enQueue(4) << " (期望: true)" << endl;
    cout << "Front(): " << q.Front() << " (期望: 2)" << endl;
    cout << "Rear(): " << q.Rear() << " (期望: 4)" << endl;
    
    // 测试6：清空队列
    cout << "\n6. 清空队列测试:" << endl;
    cout << "deQueue(): " << boolalpha << q.deQueue() << " (期望: true)" << endl;
    cout << "deQueue(): " << boolalpha << q.deQueue() << " (期望: true)" << endl;
    cout << "isEmpty(): " << boolalpha << q.isEmpty() << " (期望: false，还有1个元素)" << endl;
    cout << "Front(): " << q.Front() << " (期望: 4)" << endl;
    cout << "Rear(): " << q.Rear() << " (期望: 4)" << endl;
    
    // 继续清空
    cout << "deQueue(): " << boolalpha << q.deQueue() << " (期望: true)" << endl;
    cout << "isEmpty(): " << boolalpha << q.isEmpty() << " (期望: true)" << endl;
    cout << "Front(): " << q.Front() << " (期望: -1)" << endl;
    cout << "Rear(): " << q.Rear() << " (期望: -1)" << endl;
    
    // 测试7：空队列出队
    cout << "\n7. 空队列出队测试:" << endl;
    cout << "deQueue(): " << boolalpha << q.deQueue() << " (期望: false)" << endl;
    
    cout << "\n=== 测试完成 ===" << endl;
}

int main()
{
    testCircularQueue();
    return 0;
}