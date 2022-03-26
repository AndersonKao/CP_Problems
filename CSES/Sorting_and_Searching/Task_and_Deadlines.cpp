// 2022-02-10 10:52:53
#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;

vector<PII> V;
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    int a, d;
    V.reserve(N);
    for (int i = 0; i < N; i++){
        cin >> a >> d;
        V.emplace_back(a, d);
    }
    sort(V.begin(), V.end());
    long long ans = 0;
    long long cur = 0;
    for(auto& e: V){
        cur += e.first;
        ans += (e.second - cur);
    }
    cout << ans << endl;

    return 0;

}