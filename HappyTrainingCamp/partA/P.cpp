#include <bits/stdc++.h>
using namespace std;

int T;

void solve(int N, int M){
    vector<long long> V;
    int data;
    for (int i = 0; i < N; i++){
        cin >> data;
        V.emplace_back(data);
    }
    sort(V.begin(), V.end());
    int ans = 0;
    while(M--){
        cin >> data;
        if(upper_bound(V.begin(), V.end(), data) - lower_bound(V.begin(), V.end(), data) == 1)
            ans++;

/*
        if(find(V.begin(), V.end(), data) != V.end()){
            ans++;
        }
*/
    }
    cout << ans << endl;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N, M;
    while(cin >> N >> M){
        if(N == 0 && M == 0)
            break;
        solve(N, M);
    }

    return 0;
}