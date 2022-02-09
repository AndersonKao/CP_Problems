#include <bits/stdc++.h>
using namespace std;

int T;

void solve(){
    
        bool good = true;
        
        stack<char> _stack;
        string str;

        getline(cin, str); // empty string LOL
        for (unsigned i = 0; i < str.length() and str[i] != '\n'; i++)
        {
            switch (str[i]) {
                case '(':
                    _stack.push('(');
                    break;
                case ')':
                    if (_stack.empty() or _stack.top() != '(')
                        good = false;
                    else
                        _stack.pop();
                    break;
                case '[':
                    _stack.push('[');
                    break;
                case ']':
                    if (_stack.empty() or _stack.top() != '[')
                        good = false;
                    else
                        _stack.pop();
                    break;
                default:
                    good = false;
                    break;
            }
        }

        if (!_stack.empty())
            good = false;
        
        cout << (good ? "Yes\n" : "No\n");
}

int main(){
    //cin.tie(0);
    //ios_base::sync_with_stdio(false);
    cin >> T;
    getchar();
    while(T--){
        solve();
    }

    return 0;
}