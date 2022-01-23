#include <iostream>
#include <algorithm>
using namespace std;
bool table[4][4];

bool ans1[3][3] = {
    {0, 0, 1},
    {0, 1, 1},
    {1, 1, 0},
};

bool ans2[3][4] = {
    {0, 0, 1, 0},
    {0, 1, 1, 1},
    {1, 1, 0, 1},
};
int fsol1(){
    int ANS = 1000;
    int cur = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(table[i][j] != ans1[i][j])
                cur++;
        }
    }
    ANS = min(ANS, cur);
    cur = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(table[i][j] != ans1[3-i][j])
                cur++;
        }
    }
    ANS = min(ANS, cur);
    cur = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(table[i][j] != ans1[i][3-j])
                cur++;
        }
    }
    ANS = min(ANS, cur);
    cur = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(table[i][j] != ans1[3-i][3-j])
                cur++;
        }
    }
    ANS = min(ANS, cur);

    return ANS;
}

int fsol2(){
    int ANS = 1000;
    int cur = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            if(table[i][j] != ans1[i][j])
                cur++;
        }
    }
    ANS = min(ANS, cur);
    cur = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            if(table[i][j] != ans1[3-i][j])
                cur++;
        }
    }
    ANS = min(ANS, cur);
    cur = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            if(table[i][j] != ans1[i][4-j])
                cur++;
        }
    }
    ANS = min(ANS, cur);
    cur = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            if(table[i][j] != ans1[3-i][4-j])
                cur++;
        }
    }
    ANS = min(ANS, cur);

    return ANS;
}

int main(){
    int rowN, colN;
    bool alzero = true;
    cin >> rowN >> colN;
    for(int i = 0; i < rowN; i++){
        for(int j = 0; j < colN; j++){
            cin >> table[i][j];
            if(table[i][j]) 
                alzero = false;

        }
    }
    if(rowN >= 4 && colN >= 4){
        cout << "-1\n";
        return 0;
    }
    if(rowN == 3 && colN == 3){
        if(alzero)
            cout << 1 << endl;
        else
            cout << fsol1() << endl;
    }else if(rowN == 3 && colN == 4){
        cout << fsol2() << endl;
    }

    return 0;
}