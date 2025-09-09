#define N 100010
#define K 100010
#include<cstdio>
#include<iostream>

using namespace std;

void rotate(int* nums, int numsSize, int k){
    // 此处完善函数
    int *temp = new int[numsSize];
    for(int i = 0; i < numsSize; ++i){
        temp[(i + k) % numsSize] = nums[i];
    }
    for(int i = 0; i < numsSize; ++i){
        nums[i] = temp[i];
    }
    delete[] temp;
    return;
}

int main() {

    int n, k, nums[N];

    cin >> n >> k;
    for(int i = 0; i < n; i++)
        cin >> nums[i];

    rotate(nums, n, k);

    for(int i = 0; i < n - 1; i++)
        cout << nums[i] << ' ';
    
    cout << nums[n - 1] << endl;

    // 时间复杂度：O(n) - 遍历两次长度为n的数组，时间复杂度为O(n)
    // 空间复杂度：O(n) - 使用了一个长度为n的临时数组，空间复杂度为O(n)

    return 0;
}