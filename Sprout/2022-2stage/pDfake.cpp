#include <bits/stdc++.h>
using namespace std;

int main(){
    int N, Q;
    while (cin >> N >> Q) {
        vector<int> V(N);
        for(int& e: V){
            cin >> e;
        }
        while(Q--){
            int l, r;
            cin >> l >> r;
            int ans = 0;
            for(int& e: V){
                if(l <= e && e <= r)
                    ans++;
            }
            cout << ans << endl;
        }
    }
    return 0;
}