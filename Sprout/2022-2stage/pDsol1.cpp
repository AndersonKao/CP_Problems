#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;

int main(){
    int n, q;
    cin >> n >> q;
    
    int m[n];
    for(int i = 0; i < n; i++)
        cin >> m[i];
    sort(m, m+n);
    
    ll l, r;
    while(q--){
        cin >> l >> r;
        
        auto a = lower_bound(m, m+n, l) - m;
        auto b = upper_bound(m, m+n, r) - m;
        
        cout << ((b-a>0)? (b-a):0) << endl;
    }
    
    
    
    return 0;
}