#include <cstdio>
#include <iostream>

class PolyLinkedList;

class TermNode
{
    friend class PolyLinkedList;
    friend TermNode *PolyAdd(TermNode *ah, TermNode *bh);
    // friend TermNode *PolyMul(TermNode *ah, TermNode *bh);

public:
    TermNode() : coef(0), exp(0), link(nullptr) {}
    TermNode(float c, int e) : coef(c), exp(e), link(nullptr) {}
    void print(){
        std::cout << "coef: " << coef << " exp: " << exp << std::endl;
    }
private:
    float coef; // 系数
    int exp;    // 指数
    TermNode *link;
};

class PolyLinkedList
{
public:
    PolyLinkedList() : head(nullptr) {}
    PolyLinkedList(TermNode *head) : head(head) {}

    ~PolyLinkedList()
    {
    }

    // 返回链表头指针
    TermNode *getHead() const
    {
        return head;
    }

    void InitFrom2DArray(float terms[][2], int size)
    {
        head = nullptr;
        TermNode *tail = nullptr;

        // 依次遍历给定的terms数组
        for (int i = 0; i < size; ++i)
        {
            float coef = terms[i][0];
            int exp = terms[i][1];

            TermNode *newTerm = new TermNode(coef, exp);
            if (head == nullptr)
            {
                // 如果链表为空，则新节点为头结点
                head = newTerm;
                tail = newTerm;
            }
            else
            {
                // 否则将新节点连接到链表的末尾
                tail->link = newTerm;
                tail = newTerm;
            }
        }
    }

    // 打印多项式
    void PrintPoly() const
    {
        TermNode *current = head;
        if (current == nullptr)
        {
            std::cout << "0" << std::endl; // 如果链表为空，输出0
            return;
        }

        bool firstTerm = true;
        while (current != nullptr)
        {
            float coef = current->coef;
            int exp = current->exp;
            if (!firstTerm && current->coef > 0)
                std::cout << " + "; // 为正数的项前加上"+"符号
            else if (current->coef < 0)
            {
                std::cout << " - "; // 为负数的项前加上"-"符号
                coef = -coef;       // 系数取绝对值
            }

            if (coef != 1 || exp == 0)
            {
                std::cout << coef;
            }

            // 输出变量部分
            if (exp != 0)
            {
                std::cout << "x";
                if (exp != 1)
                {
                    std::cout << "^" << exp; // 只在指数不为 1 时显示幂次
                }
            }

            current = current->link;
            firstTerm = false;
        }
        std::cout << std::endl;
    }

private:
    TermNode *head;
};

TermNode *PolyAdd(TermNode *ah, TermNode *bh)//时间O(n) 空间O(1)
{
    // here is your code
    TermNode *head = new TermNode();
    TermNode *cur = head;

    if(ah == nullptr && bh == nullptr){
        return head;
    }
    else if(ah == nullptr){
        head = bh;
        return head;
    }
    else if(bh == nullptr){
        head = ah;
        return head;
    }

    while(ah != nullptr && bh != nullptr){
        if(ah->exp > bh->exp){
                cur->link = bh;
                cur = cur->link;
                bh = bh->link;
        }
        else if(ah->exp < bh->exp){
                cur->link = ah;
                cur = cur->link;
                ah = ah->link;
        }
        else if(ah->exp == bh->exp){
            if(ah->coef + bh->coef == 0){
                ah = ah->link;
                bh = bh->link;
            }
            else{

                    cur->link = ah;
                    ah->coef += bh->coef;
                    cur = cur->link;
                    ah = ah->link;
                    bh = bh->link;
            }
        }
    }
    
    if(ah != nullptr){
        cur->link = ah;
    }
    else{
        cur->link = bh;
    }
    return head->link;
}

int main()
{
    // 测试两个空多项式
    PolyLinkedList empty1, empty2;
    std::cout << "Empty Polynomial Test:" << std::endl;
    std::cout << "Empty Polynomial 1: ";
    empty1.PrintPoly();
    std::cout << "Empty Polynomial 2: ";
    empty2.PrintPoly();
    
    TermNode *emptyResult = PolyAdd(empty1.getHead(), empty2.getHead());
    std::cout << "Sum of Empty Polynomials: ";
    PolyLinkedList emptyResultPoly(emptyResult);
    emptyResultPoly.PrintPoly();
    std::cout << std::endl;

    // 创建两个多项式链表
    PolyLinkedList poly1, poly2;

    // 初始化第一个多项式 (1.8 + 2.0x^1000)
    float terms1[][2] = {{1.8, 0}, {2, 1000}};
    int size1 = sizeof(terms1) / sizeof(terms1[0]);
    poly1.InitFrom2DArray(terms1, size1);

    // 初始化第二个多项式 (1.2 + 51.3x^50 + 3.7x^101)
    float terms2[][2] = {{1.2, 0}, {51.3, 50}, {3.7, 101}};
    int size2 = sizeof(terms2) / sizeof(terms2[0]);
    poly2.InitFrom2DArray(terms2, size2);

    // 打印初始多项式
    std::cout << "Non-empty Polynomial Test:" << std::endl;
    std::cout << "Polynomial 1: ";
    poly1.PrintPoly();

    std::cout << "Polynomial 2: ";
    poly2.PrintPoly();

    // 相加两个多项式
    TermNode *result = PolyAdd(poly1.getHead(), poly2.getHead());

    std::cout << "Sum of Polynomials: ";
    PolyLinkedList resultPoly(result);
    resultPoly.PrintPoly();

    return 0;
}