#include <bits/stdc++.h>
using namespace std;

int T;

void solve(){

}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<pair<int, int>> V;
    int a, b;
    for (int i = 0; i < N; i++){
        cin >> a >> b;
        V.emplace_back(a, b);
    }
    sort(V.begin(), V.end());
    int curtime = 1;
    int cur = 0;
    int ans = 0;
    priority_queue<int, vector<int>, greater<int>> S;
    for (auto &p: V){
        curtime = p.first;
        while(!S.empty() && S.top() < curtime){
            cur--;
            S.pop();
        }
        cur++;
        S.emplace(p.second);
        ans = (ans < cur ? cur : ans);
    }
    cout << ans << endl;
    return 0;
}