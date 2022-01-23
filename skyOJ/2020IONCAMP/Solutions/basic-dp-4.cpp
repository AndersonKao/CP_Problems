#include <iostream>
using namespace std;
#define MAXN 131075
int N;
int datas[20][20];
long long ans[MAXN][20];
int main(){
    cin >> N;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            cin >> datas[i][j];
    int counter = 0;
    for(int i = 0; i < MAXN; i <<= 1){
        ans[i][counter++] = 1;
    }
    counter = N - 1;
    for(int i = 0; i < MAXN; i++){

    }

    return 0;
}