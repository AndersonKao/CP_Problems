#include <bits/stdc++.h>
using namespace std;

int T;
string str;
using Iter = list<char>::iterator;
void solve(){
    list<char> myL;
    Iter it = myL.end();

    for (int i = 0; i < str.length(); i++){
        switch (str[i])
        {
        case '[':
            it = myL.begin();
            break;
        case ']':
            it = myL.end();
            break;
        default:
            myL.insert(it, str[i]);
            break;
        }
    }
    for(auto &p: myL)
        cout << p;
    cout << endl;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    
    while(cin >> str){
        solve();
    }

    return 0;
}
