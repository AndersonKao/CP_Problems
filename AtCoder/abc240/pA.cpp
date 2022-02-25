#include <bits/stdc++.h>
using namespace std;


int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int A, B;
    cin >> A >> B;
    if((A + 1) % 10 == B % 10 || (A-1) % 10 == B % 10)
        cout << "Yes\n";
    else
        cout << "No\n";
    return 0;
}