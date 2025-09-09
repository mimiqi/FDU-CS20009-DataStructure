#define N 100010
#include<cstdio>
#include<iostream>
using namespace std;
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void bubbleSort(int *arr, int arrSize){
    for(int i = 0; i < arrSize - 1; ++i){
        for(int j = i + 1; j < arrSize; ++j){
            if(arr[i] > arr[j]){
                swap(&arr[i], &arr[j]);
            }
        }
    }
    return;
}


int mySortAndCount(int* arr, int arrSize){
    // 此处完善函数，返回不同数字个数k
    // 你可以通过添加新的函数来完成该任务
    bubbleSort(arr, arrSize);
    int count;
    if(arrSize == 0){
        count = 0;
    }
    else{
        count = 1;
    }
    for(int i = 0; i < arrSize - 1; ++i){
        if(arr[i] != arr[i + 1]){
            count++;
        }
    }
    return count;
}


int main() {

    int n, arr[N], k;

    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    k = mySortAndCount(arr, n);

    for(int i = 0; i < n - 1; i++)
        cout << arr[i] << ' ';
    cout << arr[n - 1] << endl;

    cout << "k = " << k << endl;

    // 时间复杂度：O(n²) - 主要由bubbleSort的嵌套循环决定 ∑(i=1,n-1)∑(j=i+1,n)1 = (n-1)n/2 = O(n²)
    // 空间复杂度：O(1) - 只使用常数个额外变量

    return 0;
}