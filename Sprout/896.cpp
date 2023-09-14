#include <iostream>
#include <algorithm>
using namespace std;



int walletNum, packageNum;
int wallets[10];
int packages[10];
bool used[10] = {false};
int MinAns = 0;


int main(){
    cin >> walletNum >> packageNum;
    for(int i = 0; i < walletNum; i++){
        cin >> wallets[i];
    }
    
    for(int i = 0; i < packageNum; i++){
        cin >> packages[i];
    }
    sort(wallets, wallets + walletNum);
    sort(packages, packages + packageNum);
    int wIndex = 0;
    while(wIndex != walletNum){
        int i;
        for(i = packageNum - 1; i >= 0; i--){
            if(packages[i] - wallets[wIndex] >= 0){
                packages[i] -= wallets[wIndex];
                if(!used[i]){
                    used[i] = true;
                    MinAns++;
                }
                wIndex++;
                break;

            }
        }
        if(i < 0)
            break;
    }
    if(wIndex != walletNum)
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