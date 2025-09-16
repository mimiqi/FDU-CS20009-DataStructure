#ifndef SEQUENTIALLIST_H
#define SEQUENTIALLIST_H

const int defaultSize = 1000;

template<class Type>
class SeqList{
    public:
    SeqList(int size = defaultSize);//构造函数
    ~SeqList();//析构函数
    int length() const;//计算顺序表长度
    int find(Type &x);//查找
    bool append(Type &x);//插入
    bool removeIndex(int i);//删除顺序表中第i个元素
    bool isEmpty();//判断顺序表是否为空
    bool isFull();//判断顺序表是否已满
    Type get(int i);//获取顺序表中第i个元素
    void printAll();//打印顺序表

    private:
    void printElements() const; // 私有方法：打印元素
    Type *list;//顺序表的数组
    int maxSize;//顺序表的最大长度
    int last;//顺序表的最后一个元素的位置
};

#endif