#include <bits/stdc++.h>
using namespace std;

int T;

void solve(){

}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    long long a;
    cin >> a;
    if(a < 0 && a % 10)
        cout << (a / 10) - 1 << endl;
    else
        cout << (a / 10)  << endl;

    return 0;
}