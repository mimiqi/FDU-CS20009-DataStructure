#include <cstdio>
#include <iostream>
#include <stack>
using namespace std;

class MyQueue
{
private:
    stack<int> s1;
    stack<int> s2;

public:
    MyQueue()
    {
        s1 = stack<int>();
        s2 = stack<int>();
    }

    void push(int x)//时间O(1) 空间O(1)
    {
        s1.push(x);
    }

    int pop()//时间O(n) 空间O(1)
    {
        if(!s2.empty()){
            int ans = s2.top();
            s2.pop();
            return ans;
        }
        else{
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
            int ans = s2.top();
            s2.pop();
            return ans;
        }
    }

    int peek()//时间O(n) 空间O(1)
    {
        if(!s2.empty()){
            return s2.top();
        }
        else{
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
            return s2.top();
        }
    }

    bool empty()//时间O(1) 空间O(1)
    {
        if(s1.empty() && s2.empty()){
            return true;
        }
        return false;
    }
};

int main()
{
    MyQueue q;
    q.push(1);
    q.push(2);
    cout << q.peek() << endl; // returns 1
    cout << q.pop() << endl;  // returns 1
    q.push(3);
    cout << q.pop() << endl;   // returns 2
    cout << q.pop() << endl;   // returns 3
    cout << boolalpha << q.empty() << endl; // returns true
    return 0;
}