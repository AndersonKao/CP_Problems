#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
int coins[1005];
int mem[2][1005];
int Num;
bool sovable(int Price){
    if(Price == 0)
        return true;
    if(Price < 0)
        return false;
    int flag = false;
    for(int i=0;i<Num;i++){
        // cout << "going to " << coins[i] << endl << "remaing" << Price-coins[i] << endl;
        if(sovable(Price - coins[i])){
            // cout << "sovalbe!\n";
            flag = true;
            break;
        }
    }
    return flag;
}
int UsingCoin = 0;
void dp(int Price,int decider){
    if(UsingCoin >= Num)
        return;
    cout << "now using Coin" << coins[UsingCoin] << endl;
    int rowindex = decider ? 0 : 1;
    for(int i = 0;i<=Price;i++){
        if(i >= coins[UsingCoin])
            mem[rowindex][i] = mem[decider][i] < mem[rowindex][i - coins[UsingCoin]] + 1 ? mem[decider][i] :mem[rowindex][i - coins[UsingCoin]] + 1;
        else
            mem[rowindex][i] = mem[decider][i];
        cout << mem[rowindex][i] << " ";
    }
    cout << endl;
    UsingCoin++;
    dp(Price,rowindex);
}
int main(){
    int T,Tar,Ans; // Tar means Target;
    cin >> T;
    while(T--){
        Ans = UsingCoin = 0;
        cin >> Num >> Tar;
        for(int i=0;i<Num;i++){
            cin >> coins[i];
        }
        sort(coins,coins+Num);
        if(!sovable(Tar))
        {
            cout << "-1\n";
            continue;
        }
        for(int i=0;i<=Tar;i++){
                mem[0][i] = i; 
            cout << mem[0][i] << " ";
        }
        cout << endl;
        dp(Tar,0);
        int ansrow = Num%2==0 ? 0 : 1;
        cout << mem[ansrow][Tar] << "\n";
        

    }

    return 0;
}