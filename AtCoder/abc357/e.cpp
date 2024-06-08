
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(), a.end()
#define eb emplace_back
#define F first
#define S second

ll ans = 0;
int a[200005];
int depth[200005];
ll dp[200005];
bool incycle[200005];
bool instack[200005];
int indeg[200005];
int entry;
bool visited[200005];
int sz;

void dfs(int u, int dep)
{
	instack[u] = true;
	depth[u] = dep;
	visited[u] = true;
	if(visited[a[u]])
	{
		if(incycle[a[u]] == false && instack[a[u]] == true)
		{
			entry = a[u];
			sz = dep - depth[a[u]] + 1;
		}
	}
	else{
		dfs(a[u], dep+1);
	}
	if(entry != -1)
	{
		incycle[u] = true;
		dp[u] = sz;
		if(u == entry)
		{
			entry = -1;
		}
	}
	else{
		dp[u] = dp[a[u]] + 1;		
	}
	ans += dp[u];
	instack[u] = false;
}

int main() {
	yccc;
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		indeg[a[i]]++;
	}

	for(int i = 1; i <= n; i++)
	{
		if(visited[i] == false)
		{
			entry = -1;
			dfs(i, 1);
		}
	}
	/*
	for(int i = 1; i <= n; i++)
	{
		cout << dp[i] << " ";
	}
	cout << endl;

	for(int i = 1; i <= n; i++)
	{
		cout << incycle[i] << " ";
	}
	cout << endl;

	*/

	cout << ans << endl;	

	return 0;
}
