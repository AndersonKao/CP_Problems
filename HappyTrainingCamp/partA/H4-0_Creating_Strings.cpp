#include <bits/stdc++.h>
using namespace std;

int T;

void solve(){

}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    string str;
    cin >> str;
    vector<char> V;
    for(auto ch: str){
        V.emplace_back(ch);
    }
    sort(V.begin(), V.end());
    int ans = 0;
    do{
        ans++;
    }
    while (next_permutation(V.begin(), V.end()));
    sort(V.begin(), V.end());
    cout << ans << endl;
    do{
        for(auto &ch: V)
            cout << ch;
        cout << endl;
    } while (next_permutation(V.begin(), V.end()));

    return 0;
}