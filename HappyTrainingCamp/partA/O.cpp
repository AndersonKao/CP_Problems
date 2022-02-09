#include <bits/stdc++.h>
using namespace std;

int T;

void add_str(string &str1, string &str2){
    int minLen = min(str1.length(), str2.length());
    if(str1.length() < str2.length()){
        swap(str1, str2);
    }
    bool carry = false;
    string ans("");
    int i;
    for (i = 0; i < str1.length(); i++){
        int cur;
        if(i < str2.length())
            cur = (str1[i] - '0') + (str2[i] - '0') + carry;
        else
            cur = str1[i] - '0' + carry;
        //cout << "i= " << i << " cur = " << cur << endl;
        if(cur > 9){
            carry = true;
            cur -= 10;
        }else
            carry = false;
        
        ans += char(cur + '0');
    }
    if(carry)
        ans += "1";
    int j;
    for (j = 0; j < ans.length(); j++){
        if(ans[j] != '0')
            break;
    }
    cout << ans.substr(j) << endl;
}

void solve(){
    string str1, str2;
    cin >> str1 >> str2;
    add_str(str1, str2);
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