#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iterator>
int subsequenceMatching_BF(std::string &s, std::vector<std::string> &words){//时间O(n × m × w_avg) 空间O(1)
    int ans = 0;
    auto it = words.begin();
    while(it != words.end()){
        int s_len = s.length();
        int w_len = it->length();
        if(w_len > s_len){
            ++it;+
        }
        else{
            bool flag = false;
            int i = 0, j = 0;
            while(i < s_len && j < w_len){
                if(s[i] == (*it)[j]){
                    ++i;
                    ++j;
                }
                else{
                    ++i;
                }
                if(j == w_len){
                    flag = true;
                    break;
                }
            }
            if(flag == true){
                ++ans;
            }
            ++it;
        }
    }
    return ans;
}

int subsequenceMatching_(std::string &s, std::vector<std::string> &words){//时间O(n*m + w_size) 空间O(m × w_avg)
    int ans = 0;
    std::vector<std::vector<std::pair<std::string, int>>> group;
    group.resize(26);

    for(auto &word : words){
        group[word[0] - 'a'].push_back(std::make_pair(word, word.length()));
    }

    for(auto it = s.begin(); it != s.end(); ++it){
        // 先收集当前组中所有需要处理的元素,直接在原group组上进行处理会导致迭代器失效，指向意料之外的地址。
        std::vector<std::pair<std::string, int>> to_process;
        for(auto &word : group[*it - 'a']){
            to_process.push_back(word);
        }
        
        // 清空当前组
        group[*it - 'a'].clear();
        
        // 处理收集到的元素
        for(auto &word : to_process){
            if(word.second == 1){
                ++ans;
            }
            else{
                --word.second;
                if(word.first.length() > 1){
                    word.first = word.first.substr(1);
                    group[word.first[0] - 'a'].push_back(word);
                }
            }
        }
    }
    return ans;
}
int main(){
    std::string s = "abcde";
    std::vector<std::string> words = {"a", "bb", "acd", "ace"};
    //std::cout << subsequenceMatching_BF(s, words) << std::endl;
    std::cout << subsequenceMatching_(s, words) << std::endl;
    return 0;
}