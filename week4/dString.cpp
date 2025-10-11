#include "dString.h"
#include <iostream>
#include <string.h>
#include <algorithm>
#include <math.h>
dString::dString(){
    this->ch = new char[nInitLen + 1];
    this->ch[0] = '\0';
    this->nLen = 0;
}

dString::~dString(){
    delete[] this->ch;
}

dString::dString(const char *s){
    this->nLen = strlen(s);
    this->ch = new char[nLen + 1];
    strcpy(this->ch, s);
    this->ch[nLen] = '\0';
}

dString::dString(const dString &str){
    this->nLen = str.nLen;
    this->ch = new char[nLen + 1];
    strcpy(this->ch, str.ch);
}

int dString::getLen() const{
    return this->nLen;
}

bool dString::isEmpty() const{
    return this->nLen == 0;
}

void dString::empty(){
    this->nLen = 0;
    this->ch[0] = '\0';
}

dString dString::getSub(int nPos, int nCount) const{
    if(nPos < 0 || nPos >= this->nLen){
        std::cerr << "Invalid position" << std::endl;
        return dString();
    }
    if(nCount < 0){
        std::cerr << "Invalid count" << std::endl;
        return dString();
    }
    if(nPos + nCount > this->nLen){
        nCount = this->nLen - nPos;
        std::cout << "Caution: nCount is too large, set to " << nCount << std::endl;
    }
    dString ans;
    ans.nLen = nCount;
    ans.ch = new char[nCount + 1];
    strncpy(ans.ch, this->ch + nPos, nCount);
    ans.ch[nCount] = '\0';
    return ans;
}

char dString::operator[](int nPos) const{
    int length = this->nLen;
    if(nPos < 0 || nPos >= length){
        std::cerr << "Invalid position" << std::endl;
        return '\0';
    }
    return this->ch[nPos];
}

dString & dString::operator=(const dString &str){
    if(this == &str){
        std::cerr << "String assignment to itself" << std::endl;
        return *this;
    }
    else{
        delete[] this->ch;
        this->ch = new char[str.nLen + 1];
        strcpy(this->ch, str.ch);
        this->nLen = str.nLen;
        return *this;
    }
}

dString & dString::operator+=(const dString &str){
    this->nLen += str.nLen;
    char *newCh = new char[this->nLen + 1];
    strcpy(newCh, this->ch);
    strcat(newCh, str.ch);
    newCh[this->nLen] = '\0';
    delete[] this->ch;
    this->ch = newCh;
    return *this;
}

bool dString::operator==(const dString &str) const{
    return strcmp(this->ch, str.ch) == 0;
}

int dString::find_BF(dString &strSub) const{
    int t_len = this->nLen;
    int s_len = strSub.nLen;
    for(int i = 0; i <= t_len - s_len; ++i){
        bool flag = true;
        for(int j = 0; j < s_len; ++j){
            if(this->ch[i + j] != strSub.ch[j]){
                flag = false;
                break;
            }
        }
        if(flag == true){
            return i;
        }
    }
    return -1;
}

int dString::find_KMP(dString &strSub) const{
    int s_len = this->nLen;
    int p_len = strSub.nLen;
    int *next = new int[p_len];
    get_next(strSub, next);
    int i = 0;
    int j = 0;
    while(i < s_len && j < p_len){
        if(j == -1 || this->ch[i] == strSub.ch[j]){
            ++i;
            ++j;
        }
        else{
            j = next[j];
        }
    }
    if(j == p_len){
        return i - j;
    }
    return -1;
}

void get_next(dString &strSub, int *next){
    int s_len = strSub.getLen();
    next[0] = -1;
    int fast = 0;
    int slow = -1;
    while(fast < s_len){
        if(slow == -1 || strSub.ch[fast] == strSub.ch[slow]){
            next[++fast] = ++slow;
        }
        else{
            slow = next[slow];  
        }
    }
}

int hash(const char *ch, int len){
    int ans = 0;
    for(int i = 0; i < len; ++i){
        ans = ans * 2 + (ch[i] - 'a');
    }
    return ans % 1000007;
}

int rehash(int hash_val, char fore, char next, int len){
    int ans = hash_val;
    ans = ans - (fore - 'a') * pow(2, len - 1);
    ans = ans * 2 + (next - 'a');
    ans = ans % 1000007;
    return ans;
}

int dString::find_RK(dString &strSub) const{
    int t_len = this->nLen;
    int s_len = strSub.nLen;
    int s_hash = hash(strSub.ch, s_len);
    int t_hash;
    for(int i = 0; i <= t_len - s_len; ++i){
        if(i == 0){
            t_hash = hash(this->ch, s_len);
        }
        else{
            t_hash = rehash(t_hash, this->ch[i - 1], this->ch[i + s_len - 1], s_len);
        }
        if(t_hash == s_hash){
            bool flag = true;
            for(int k = 0; k < s_len; ++k){
                if(this->ch[i + k] != strSub.ch[k]){
                    flag = false;
                    break;
                }
            }
            if(flag == true){
                return i;
            }
        }
    }
    return -1;
}

void get_good_suffix(const dString &strSub, int *suffix, bool *prefix) {
    int p_len = strSub.nLen;
    
    // 初始化
    for(int i = 0; i < p_len; ++i) {
        suffix[i] = -1;
        prefix[i] = false;
    }
    
    // 计算每个子串的最长匹配前缀位置
    for(int i = 0; i < p_len - 1; ++i) {
        int j = i;
        int k = 0;  // 公共后缀长度
        while(j >= 0 && strSub.ch[j] == strSub.ch[p_len - 1 - k]) {
            --j;
            ++k;
            suffix[k] = j + 1;  // j+1 是匹配的起始位置
        }
        if(j == -1) prefix[k] = true;  // 如果匹配到头，说明是前缀
    }
}

int dString::find_BM(dString &strSub) const {
    int t_len = this->nLen;      // 主串长度
    int p_len = strSub.nLen;     // 模式串长度
    if(p_len == 0) return 0;
    if(t_len == 0) return -1;

    // 构建坏字符规则表
    const int CHAR_SIZE = 256;
    int *bad_char = new int[CHAR_SIZE];
    for(int i = 0; i < CHAR_SIZE; ++i) {
        bad_char[i] = -1;
    }
    for(int i = 0; i < p_len; ++i) {
        bad_char[(unsigned char)strSub.ch[i]] = i;
    }
    
    // 构建好后缀规则表
    int *suffix = new int[p_len];
    bool *prefix = new bool[p_len];
    get_good_suffix(strSub, suffix, prefix);
    
    int i = p_len - 1;    // 主串中比较位置
    while(i < t_len) {
        int j = p_len - 1;
        int k = i;        // 保存主串当前位置
        
        // 从右向左比较
        while(j >= 0 && this->ch[k] == strSub.ch[j]) {
            --k;
            --j;
        }
        
        if(j < 0) {  // 找到匹配
            delete[] bad_char;
            delete[] suffix;
            delete[] prefix;
            return k + 1;
        }
        
        // 计算坏字符规则移动距离
        int bad_char_shift = j - bad_char[(unsigned char)this->ch[k]];
        
        // 计算好后缀规则移动距离
        int good_suffix_shift = 0;
        if(j < p_len - 1) {  // 有好后缀
            int len = p_len - 1 - j;  // 好后缀长度
            if(suffix[len] != -1) {
                // 存在匹配的好后缀
                good_suffix_shift = j - suffix[len] + 1;
            } else {
                // 查找最长的可匹配前缀
                int r;
                for(r = j + 2; r <= p_len - 1; ++r) {
                    if(prefix[p_len - r]) {
                        good_suffix_shift = r;
                        break;
                    }
                }
                if(r == p_len) {
                    good_suffix_shift = p_len;
                }
            }
        }
        
        // 取两个规则中的最大值
        i += std::max(bad_char_shift, good_suffix_shift);
    }
    
    delete[] bad_char;
    delete[] suffix;
    delete[] prefix;
    return -1;
}

std::ostream & operator<<(std::ostream &os, const dString &str){
    os << str.ch;
    return os;
}

int main(){
    dString str1("Hello, World!");
    dString str2("lo,");
    int ans_index = str1.find_BM(str2);
    if(ans_index != -1){
        dString str3 = str1.getSub(ans_index, str2.getLen());
        std::cout << "ans_index: " << ans_index << " " << str3 << std::endl;
    }
    else{
        std::cout << "Not found" << std::endl;
    }

    return 0;
}