#include <bits/stdc++.h>
using namespace std;

int T;

void solve(){
    int N, Len;
    cin >> N >> Len;
    string strs[50];
    for (int i = 0; i < N; i++)
    {
        cin >> strs[i];
    }
    string ans("");
    int diff = 0;
    for (int i = 0; i < Len; i++){
        int occur[26];
        fill(occur, occur + 26, 0);
        for (int str_i = 0; str_i < N; str_i++){
            occur[strs[str_i][i]- 'A']++;
        }
        int cur = 0;
        char toAdd = ' ';
        for (char ch = 'A'; ch <= 'Z'; ch++){
            if(occur[ch - 'A'] > cur){
                toAdd = ch;
                cur = occur[ch - 'A'];
            }
        }
        ans += toAdd;
        for (char ch = 'A'; ch <= 'Z'; ch++)
            if(toAdd != ch)
                diff += occur[ch - 'A'];
            

    }
    cout << ans << "\n"
         << diff << "\n";
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> T;
    while(T--){
        solve();
    }

    return 0;
}