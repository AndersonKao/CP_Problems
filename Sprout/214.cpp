// AC 2020/08/12 10:55:45
#include <iostream>
using namespace std;
bool table[105][105];
int anstable[105][105];
int main(){
    int N, M;
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> table[i][j];
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            for(int k = -1; k <= 1; k++){
                for(int y = -1; y <= 1; y++){
                    if(i + k >= 0 && i + k < N && j + y >= 0 && j + y < M && (k | y)){
                        if(table[i+k][j+y]){
                            anstable[i][j]++;
                        }
                    }
                }
            }
        }
    }
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cout << anstable[i][j] << (j == M-1 ? '\n' : ' ');
        }
    }
    return 0;
}