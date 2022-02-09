#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;
using Iter = vector<pair<int, int>>::iterator;
int N;

bool cmp(const PII &lhs, const PII &rhs){
    if(lhs.first < rhs.first)
        return true;
    else if(lhs.first > rhs.first)
        return false;
    return lhs.second < rhs.second;
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> N;
    vector<pair<int, int>> V;
    priority_queue<int, vector<int>, greater<int>> Out;
    int a, b;
    for (int i = 0; i < N; i++){
        cin >> a >> b;
        V.emplace_back(a, b);
    }
    sort(V.begin(), V.end(), cmp);
    int curtime = 1;
    int cur = 0;
    int ans = 0;
    for (auto &p : V)
    {
        curtime = p.first;
        cur++;
        while (!Out.empty() && Out.top() < curtime)
        {
            cur--;
            Out.pop();
        }
        Out.emplace(p.second);
        ans = (ans > cur ? ans : cur);
    }
    cout << ans << endl;

    return 0;
}