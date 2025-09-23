#ifndef STATICLIST_H    
#define STATICLIST_H

#define maxSize 100

template<typename T>
class staticList;

template<typename T>
class staticListNode{
    friend class staticList<T>;
    private:
        T data;
        int link;

    protected:

    public:
        staticListNode();
        staticListNode(const T& x);
        ~staticListNode();
};

template<typename T>
class staticList{
    private:
        staticListNode<T> element[maxSize];
        int avail;//index of first free node
        int first;//index of first node
    protected:

    public:
        staticList();
        ~staticList();
        void initList();
        int length() const;
        bool isEmpty() const;
        bool isFull() const;
        int search(T x) const;
        int locate(int i) const;
        bool append(T x);
        bool insert(int i, T x);
        bool remove_index(int i);
        bool remove_value(T x);
        T getData(int i) const;  // 获取第i个位置的数据
};



#endif