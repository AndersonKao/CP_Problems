// AC 2020/05/15 22:55:44
#include <iostream>
using namespace std;

void EzSort(int N, int const **ptr_array){ // 儲存指標的陣列
    for(int i = 0; i < N; i++){
        for(int j = i; j > 0;j--){
            if( *(ptr_array[j]) < *(ptr_array[j-1]) ){
                const int *c = ptr_array[j];
                ptr_array[j] = ptr_array[j-1];
                ptr_array[j-1] = c;
            }
        }
    }
}

int main() {
    int N, arr[1000], *ptr[1000];
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> arr[i];
        ptr[i] = &(arr[i]);
    }
    EzSort(N, (int const **)ptr);
    for (int i = 0; i < N; i++) {
        std::cout << *(ptr[i]) << (i == N - 1 ? '\n' : ' ');
    }
}
