// AC
#include <iostream>
using namespace std;
int matrix[11][11];
int matrix2[11][11];
int ansMax[11][11];
int main(){
    int N1, M1;
    int N2, M2;
    cin >> N1 >> M1;
    cin >> N2 >> M2;
    for (int i = 0; i < N1; i++){
        for (int j = 0; j < M1; j++){
            cin >> matrix[i][j];
        }
    }
    for (int i = 0; i < N2; i++){
        for (int j = 0; j < M2; j++){
            cin >> matrix2[i][j];
        }
    }
    int ans;
    for (int i = 0; i < N1; i++){
        for (int j = 0; j < M2; j++){
            ans = 0;
            for (int k = 0; k < M1; k++){
                ans += matrix[i][k] * matrix2[k][j];
            }
            cout << ans;
            if(j == M2-1){
                cout << '\n';
            }else{
                cout << ' ';
            }
        }
    }
        return 0;
}