#include <iostream>

void sort(int *a, const int n){
    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            if(a[i] > a[j]){
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

void print(int *a, const int n){
    for(int i = 0; i < n; ++i){
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

int main(){
    int a[] = {1, 1, 4, 5, 1, 4};
    sort(a, 5);
    print(a, 5);
    return 0;
}