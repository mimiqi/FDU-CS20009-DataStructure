#ifndef DSTRING_H
#define DSTRING_H

#include <iostream>

const int nInitLen = 1024;

class dString{
    private:
        int nLen;
        char *ch;
    protected:

    public:
        dString();
        ~dString();
        dString(const char *s);
        dString(const dString &str);  
        int getLen( ) const;   // 获得字符串的长度
        bool isEmpty( ) const;   // 判断当前字符串是否为空串
        void empty( );   // 清空当前字符串
        dString getSub(int nPos,  int nCount) const;  // 获得位置nPos开始，长度为nCount的子串
        char operator [] (int nPos) const;  // 操作符重载：获得指定下标的字符
        dString & operator = (const dString &str);  // 操作符重载：字符串赋值
        dString & operator += (const dString &str);  // 操作符重载：字符串拼接
        bool operator == (const dString &str) const;  // 操作符重载：字符串等值判断
        int find_BF(dString &strSub) const;  // 字符串的模式匹配(BF算法)
        int find_KMP(dString &strSub) const;  // 字符串的模式匹配(KMP算法)
        int find_RK(dString &strSub) const;  // 字符串的模式匹配(RK算法)
        int find_BM(dString &strSub) const;  // 字符串的模式匹配(BM算法)
        friend std::ostream & operator<<(std:: ostream &os, const dString &str);
        friend void get_next(dString &strSub, int *next);
        friend void get_good_suffix(const dString &strSub, int *suffix, bool *prefix);
};

#endif