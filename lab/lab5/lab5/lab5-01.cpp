#include <cstdio>
#include <iostream>
#include <string>
#include <stack>
using namespace std;



string removeDuplicates(string s, int k)//时间O(n) 空间O(n)
{
    stack<pair<char, int>> st, sr;
    for(auto &c : s){
        if(st.empty() || c != st.top().first){
            st.push(make_pair(c, 1));
        }
        else{
            st.top().second++;
            if(st.top().second == k){
                st.pop();
            }
        }
    }
    string ans;
    while(!st.empty()){
        sr.push(st.top());
        st.pop();
    }
    while(!sr.empty()){
        ans += string(sr.top().second, sr.top().first);
        sr.pop();
    }
    return ans;
}


int main()
{
    string s = "deeedbbcccbdaabcd";
    int k = 3;
    cout << removeDuplicates(s, k) << endl;
    return 0;
}
