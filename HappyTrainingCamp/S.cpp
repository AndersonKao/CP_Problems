#include <bits/stdc++.h>
using namespace std;

int T;

using Iter = list<char>::iterator;
list<char> myList;
string str;
void solve(){
    Iter it = myList.begin();
    for (int i = 0; i < str.length(); i++){
        switch (str[i])
        {
        case '[':
            it = myList.begin();
            break;
        case ']':
            it = myList.end();
            break;
        default:
            myList.insert(it, str[i]);
            break;
        }

    }
    for(auto &p: myList)
        cout << p;
    cout << endl;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    while(cin >> str){
        myList.clear();
        solve();
    }

    return 0;
}