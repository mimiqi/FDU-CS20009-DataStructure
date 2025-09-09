#define N 10010
#include<cstdio>
#include<iostream>

using namespace std;

int findSpecialInteger(int* arr, int arrSize){
    // 此处完善函数，返回指定元素
    int min_appera_times = arrSize / 4;
    int count = 0;
    for(int i = 0; i < arrSize - 1;){
        if(arr[i] == arr[i + 1]){
            ++count;
            if(count > min_appera_times){
                return arr[i];
            }
            ++i;
        }
        else{
            count = 0;
            ++i;
        }
    }
    return -1;

}

int main() {

    int n, arr[N];

    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    cout << findSpecialInteger(arr, n) << endl;

    // 时间复杂度：O(n) - 主循环内套一个if-else，最坏情况下每次都需要遍历到数组末尾，时间复杂度为O(n)
    // 空间复杂度：O(1) - 只使用常数个额外变量，与输入规模无关

    return 0;
}