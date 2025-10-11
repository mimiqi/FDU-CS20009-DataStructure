#include <iostream>
#include <algorithm>

void get_next(std::string &pattern, int *next);
bool find_KMP(std::string &text, std::string &pattern);

int repeatedStringMatch(std::string &text, std::string &pattern){//时间O(n*(t_len + p_len)) 空间O(p_len + t_len + p_len - 1) 其中n为需要重复的次数(t_len + p_len - 1) / t_len
    bool find = false;
    int ans = 0;
    int t_len = text.length();
    int p_len = pattern.length();
    std::string temp = "";
    do{
        ++ans;
        temp += text;
        if(find_KMP(temp, pattern) == true){
            find = true;
            break;
        }
    }while(temp.length() < t_len + p_len - 1 && !find);
    if(find) return ans;
    else return -1;
}

bool find_KMP(std::string &text, std::string &pattern){//时间O(t_len + p_len) 空间O(p_len)
    int t_len = text.length();
    int p_len = pattern.length();
    int *next = new int[p_len];
    get_next(pattern, next);
    int i = 0;
    int j = 0;
    while(i < t_len && j < p_len){
        if(j == -1 || text[i] == pattern[j]){
            ++i;
            ++j;
        }
        else{
            j = next[j];
        }
    }
    if(j == p_len){
        return true;
    }
    else{
        return false;
    }
    delete[] next;
    return false;
}

void get_next(std::string &pattern, int *next){
    int p_len = pattern.length();
    next[0] = -1;
    int fast = 0;
    int slow = -1;
    while(fast < p_len){
        if(slow == -1 || pattern[fast] == pattern[slow]){
            next[++fast] = ++slow;
        }
        else{
            slow = next[slow];
        }
    }
}

int main(){

    std::string text = "abcd";
    std::string pattern = "cdabcdab";
    std::cout << repeatedStringMatch(text, pattern) << std::endl;

    return 0;

}