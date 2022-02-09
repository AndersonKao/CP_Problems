#include <bits/stdc++.h>
using namespace std;

int T;

string str;
void solve(){
    getline(cin, str);
    bool solve = true;

    stack<char> S;
    for (int i = 0; i < str.length() && str[i] != '\n'; i++){
        switch (str[i])
        {
        case '[':
            S.emplace(str[i]);
            break;
        case '(':
            S.emplace(str[i]);
            break;
        case ']':
            if(S.empty() || S.top() != '['){
                solve = false;
                break;
            }else
                S.pop();
            break;
        case ')':
            if(S.empty() || S.top() != '('){
                solve = false;
                break;
            }else
                S.pop();
            break;
        default:
            break;
        }
    }
    if(!S.empty())
        solve = false;
    cout << (solve ? "Yes\n" : "No\n");
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> T;
    getchar();
    while(T--){
        solve();
    }
    return 0;
}