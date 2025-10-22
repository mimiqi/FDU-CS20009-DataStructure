#include <iostream>
#include <stack>
struct Node{
    long long val;
    int tag;
    Node(long long val, int tag) : val(val), tag(tag) {}
};

long long fibonacci(int n){
    Stack <Node> S;
    Node w;  
    long long sum=0;
    // 反复执行直到所有终端结点数据累加完
    do {
        // 向左递归到底，边走边进栈
        while (n>1) { w.n=n;  w.tag=1;  S.Push(w);  n--; }
        sum=sum+n;  // 执行求和    
        while (!S.IsEmpty( )) {
            S.Pop(w);
            // 改为向右递归，F(n)右侧为F(n-2)
            if (w.tag==1) { w.tag=2;  S.Push(w);  n=w.n-2;  break; }
        }
    } while (!S.IsEmpty( ));
    return sum;
}