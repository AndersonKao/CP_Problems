#include <bits/stdc++.h>
using namespace std;

int T;

void solve(){
    string str;
    cin >> str;
    string ans(str);
    for (unsigned i = 0; i < str.length(); i++)
    {
        string tmp = str.substr(i) + str.substr(0, i);
        //cout << tmp << endl;
        if(tmp < ans)
            ans = tmp;
    }
    cout << ans << endl;
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