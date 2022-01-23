#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr(i,j,k) for(int i=j;i<k;i++)
#define f(n) fr(i,0,n)
#define f1(n) fr(i,1,n+1)
#define pb push_back
#define F first
#define S second
#define all(x) x.begin(), x.end()
const int mod = 998244353;
const int maxn = 200005;

void go() {
  int n;
  cin >> n;
  map<int,vector<pair<int,int>>>mp;
  for (int i = 0 ; i < n - 1 ; i ++) {
    int x, y, a;
    cin >> x >> y >> a;
    mp[a].push_back({x, y});
  }
  map<int,ll>ans;
  
  for (auto &i : mp) {
    map<int,ll>chg;
    for (auto &j : i.S) {
        if (chg.count(j.F)) {
            chg[j.F]++;
        }
        else {
            chg[j.F] = ans[j.F] + 1;
        }
        chg[j.F] += ans[j.S];
        if (chg.count(j.S)) {
            chg[j.S]++;
        }
        else {
            chg[j.S] = ans[j.S] + 1;
        }
        chg[j.S] += ans[j.F];
    }
    for (auto &i : chg) {
        ans[i.F] = i.S;
    }
  }
  long long sum = 0;
  for (auto &i : ans) {
    sum += i.S;
  }
  cout << sum << '\n';
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int c = 0;
    int t;
    if (!c) {
        t = 1;
    }
    else {
        cin >> t;
    }
    while (t--) {
        go();
    }
    
}