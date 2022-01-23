#include <iostream>
using namespace std;
char table[105][105];
bool tabletrue[105][105];
int rowN, colN;
// void dfs(int row, int col){
    
//     if(row == rowN && col == colN){
//         tabletrue[row][col] = true;
//     }
    
    
    
//     dfs(row-1, col);
//     dfs(row, col-1);
// }

int main(){
    int T;
    cin >> T;
    while(T--){
        cin >> rowN >> colN;
        for(int i = 1; i <= rowN; i++){
            for(int j = 1; j <= colN; j++){
                cin >> table[i][j];
            }
        }
        int ans = 0;
        for(int i = 1; i <= rowN; i++){
            if(table[i][colN] == 'R')
                ans++;
        }
        for(int i = 1; i <= colN; i++){
            if(table[rowN][i] == 'D')
                ans++;
        }
        cout << ans << endl;
        // for(int i = 1; i <= rowN; i++){
        //     for(int j = 1; j <= colN; j++){
        //         cout << table[i][j];
        //     }
        //     cout << endl;
        // }
    }
    return 0;
}