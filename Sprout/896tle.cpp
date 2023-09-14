// AC 2020/06/30 20:33:50
#include <iostream>
#include <algorithm>
using namespace std;

int walletNum, packageNum;
int wallets[10];
int originPackeages[10];
int packages[10];
bool usedPackage[10] = {false};
int MinAns = INT32_MAX;

void dfs(int curAns, int Curdepth){ // Curdepth 放到第幾個皮夾
    if(Curdepth == walletNum){
        MinAns = min(MinAns, curAns);
        return ;
    }
    if(curAns >= MinAns)
        return;
    for(int i = 0; i < packageNum; i++){
        if(packages[i] >= wallets[Curdepth]){
            packages[i] -= wallets[Curdepth];
            if(!usedPackage[i])
                curAns++;
            usedPackage[i] = true;
            
            dfs(curAns, Curdepth + 1);

            packages[i] += wallets[Curdepth];
            if(packages[i] == originPackeages[i]){
                usedPackage[i] = false;
                curAns--;
            }
        }
    }
}


int main(){
    
    cin >> walletNum >> packageNum;
    for(int i = 0; i < walletNum; i++){
        cin >> wallets[i];
    }
    
    for(int i = 0; i < packageNum; i++){
        cin >> packages[i];
        originPackeages[i] = packages[i];
    }
    dfs(0, 0);

    if(MinAns == INT32_MAX)
        cout << "-1\n";
    else
        cout << MinAns << "\n";
    return 0;
}
/*
10 10
1 1 1 1 1 1 1 1 1 1
1 2 3 4 5 6 7 8 9 10
*/