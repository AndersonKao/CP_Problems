#include <iostream>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;
stack<int> box;
int coins[1005];
int Num,Ans,Tmp;
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
void dp(int Price){
    if(Price == 0){
        Ans = Ans < Tmp ? Ans :Tmp;
        // cout << "find solution\nboxsize = " << box.size() << endl ;
        // cout << Ans << endl;
        return;
    }else if(Price < 0){
        return;
    }
    for(int i = 0;i<Num;i++){
        Tmp++;
        dp(Price-coins[i]);
        Tmp--;
    }
}
int main(){
    int T,Tar; // Tar means Target;
    cin >> T;
    while(T--){
        while(!box.empty())
            box.pop();
        Ans = 99999999;
        Tmp = 0;
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
        dp(Tar);
        
        cout << Ans << endl;
        

    }

    return 0;
}