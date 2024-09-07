#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ": " << x << endl;

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

vec<list<pair<int, int>>::iterator> edges;

const int maxn = (1 << 15);

vector<int> G[maxn];

// create a graph, each node have bit string of (n-1)
// De-brujin sequence corroespond to the Euler circuit (node id + next step)

void DFS(int u){
	while(G[u].empty() == false){
		int v = G[u].back();
		G[u].pop_back();
		cout << (v & 1);
		DFS(v);
	}
}

int main(){
	yccc;		
	int n;
	cin >> n;
	if(n == 1){
		cout << "01" << endl;
		return 0;
	}

	for(int u = 0; u < (1 << (n - 1)); u++){
		int v1 = ((u & ((1 << (n-2)) - 1)) << 1);
		int v2 = v1 | 1;
		G[u].eb(v1);
		G[u].eb(v2);
	}
	for(int i = 1; i <= n-1; i++){
		cout << 0;
	}

	DFS(0);

	return 0;
}

