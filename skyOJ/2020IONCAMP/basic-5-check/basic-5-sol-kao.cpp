#include <iostream>
#include <vector>
using namespace std;
int colN, rowN;
long long Ans;
bool Table[25][25];
bool checkitout(){
    bool emptyflag = true;
    for(int i = 1; i <= rowN; i++){
        for(int j = 1; j <= colN; j++){
            if(Table[i][j]){
                emptyflag = false;
                break;
            }
        }
    }
    if(emptyflag)
        return true;
    for(int i = 1; i <= rowN; i++){
        for(int j = 1; j <= colN; j++){
            // Up
            if(!Table[i][j])
                continue;
            if(i >= 3){
                if(Table[i-1][j] && ! Table[i-2][j])
                    return false;
            }
            // Down
            if(i <= rowN - 2){
                if(Table[i+1][j] && ! Table[i+2][j])
                    return false;
            }// Left
            if(j >= 3){
                if(Table[i][j-1] && ! Table[i][j-2])
                    return false;
            }// Right
            if(j <= colN-2){
                if(Table[i][j+1] && ! Table[i][j+2])
                    return false;
            }
        }
    }
    return true;
}
void listitout(){
    for(int i = 1; i <= rowN; i++){
        for(int j = 1; j <= colN; j++){
            cout << Table[i][j] << " ";
        }
        cout << endl;
    }
}
void sol(int index_X, int index_Y){
    if(index_X > rowN){
        if(checkitout()){
            Ans++;
            // cout << "this add Ans.\n";
            // listitout();
        }
        return;
    }
    // cout << "Now asking row: " << index_X << " col: " << index_Y << endl;
    
    Table[index_X][index_Y] = 0;
    if(index_Y + 1 <= colN)
        sol(index_X, index_Y+1);
    else
        sol(index_X+1, 1);
    
    Table[index_X][index_Y] = 1;
    if(index_Y + 1 <= colN)
        sol(index_X, index_Y+1);
    else
        sol(index_X+1, 1);
    Table[index_X][index_Y] = 0;
}

int main(){
    int T;
    cin >> T;
    while(T--){
        Ans = 0;
        cin >> rowN >> colN;
        for(int i = 0; i < 25; i++)
            for(int j = 0; j < 25; j++)
                Table[i][j] = 0;
        sol(1,1);
        cout << Ans << endl;
    }
    return 0;
}