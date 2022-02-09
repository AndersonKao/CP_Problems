#include <bits/stdc++.h>
using namespace std;


unsigned N;
void printb(unsigned G){
    int bit = 1 << (N-1);
    while(bit){
        if(bit & G)
            printf("1");
        else
            printf("0");
        bit >>= 1;
    }
    printf("\n");
}

int main(){
    cin >> N;
    for (int i = 0; i < 1 << N; i++){
        printb(i ^ (i / 2));
    }

        return 0;
}