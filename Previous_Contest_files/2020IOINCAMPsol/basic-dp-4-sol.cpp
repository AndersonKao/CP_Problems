#include <iostream>
#include <string>
using namespace std;
#define MAXN 132000
int N;
int table[20][20];
long long ans[MAXN][20] = {0};
int main(){
    cin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            cin >> table[i][j];
    }
    for(int i = 0; i < N; i++){
        ans[1 << i][i] = 1;
    }
    // for(int i = 0; i < MAXN; i++){
    //     for(int j = 0; j < N; j++)
    //         if(ans[i][j])
    //             cout << i << " " << j << endl;
    // }
    for(int i = 1; i < (1 << N); i++){ // set 
        for(int j = 0; j < N; j++){
            if(i & (1 << j))
                for(int k = 0; k < N; k++){
                    if(j != k && table[j][k])
                        ans[i][j] += ans[i - (1 << j)][k];
                }
        }
    }
    long long Fans = 0;
    for(int i = 0; i < N; i++){
        Fans += ans[(1 << N) -1][i];
    }
    cout << Fans << endl;
    return 0;
}