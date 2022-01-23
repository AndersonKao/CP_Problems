#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fr(i,j,k) for(int i=j;i<k;i++)
#define f(n) fr(i,0,n)
#define f1(n) fr(i,1,n+1)
#define pb push_back
#define F first
#define S second
#define all(x) x.begin(), x.end()
using namespace std;
const int maxn = 300005;
const int mod = 1e9 + 7;
int b[maxn];
void update(int x) {
    while (x < maxn) {
        b[x]++;
        x += x & (-x);
    }
}
int query(int x) {
    int ret = 0;
    while (x) {
        ret += b[x];
        x -= x & (-x);
    }
    return ret;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int>v(n);
    for (int i = 1 ; i <= n ; i++) {
        int x;
        cin >> x;
        v[x - 1] = i;
    }
    long long ans = 0;
    int cnt = 0;
    for (auto &i : v) {
        ans += cnt - query(i - 1);
        cnt++;
        update(i);
    }
    cout << ans << '\n';
}