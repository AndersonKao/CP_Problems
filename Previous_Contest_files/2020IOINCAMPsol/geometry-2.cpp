#include <iostream>
#include <vector>
using namespace std;

int table[20][20] = {0};

int main(){
    int N;
    cin >> N;
    int L,R,U,D;
    for(int i = 0; i < N; i++){
        cin >> L >> R >> U >> D;
        for(int j = L; j < R; j++){
            for(int k = U; k < D; k++){
                table[k][j] = 1;
            }
        }
    }
    int ans = 0;
    for(int j = 0; j < 20; j++){
        for(int k = 0; k < 20; k++){
            if(table[j][k]) ans++;
        }
    }
    cout << ans << endl;
    return 0;
}