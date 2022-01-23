// AC Jul/18/2020 15:31UTC+8
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
string str;

int lcd(int l, int r, char ch){
    if(r - l == 1){
        if(str[l] != ch)
            return 1;
        return 0;
    }
    int count1 = 0, count2 = 0;
    int mid = (l + r) / 2;
    for(int i = l; i < mid; i++)
        if(str[i] != ch)
            count1++;
    
    for(int i = mid; i < r; i++)
        if(str[i] != ch)
            count2++;
    return min(count1 + lcd(mid, r, ch+1), count2 + lcd(l , mid, ch+1));
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--){
        int Len;
        cin >> Len;
        cin >> str;
        cout << lcd(0, str.length(), 'a') << '\n';
    }
    return 0;
}