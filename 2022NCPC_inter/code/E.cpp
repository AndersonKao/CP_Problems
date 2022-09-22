#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
#define F first
#define S second

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using p = pair<T, T>;

priority_queue<int, vec<int>, greater<int>> pq;
queue<p<int>> que;
vec<vec<int>> _list;
deque<deque<bool>> vis, ans, go;

int gx[4] = {0, -1, 0, 1};
int gy[4] = {1, 0, -1, 0};
void dfs1(int i, int k) {
//  cout << i << ' ' << k << ' ' << _list[i][k] << endl;
// cout << flush;
	if (vis[i][k]) return;
	vis[i][k] = true;
	que.emplace(i, k);

	for (int z = 0; z < 4; z++) {
		if (_list[i+gx[z]][k+gy[z]] == _list[i][k]) {
			dfs1(i+gx[z], k+gy[z]);
		} else {
			pq.emplace(_list[i+gx[z]][k+gy[z]]);
		}
	}
}

	int r, c;
void dfs2(int i, int k, int val) {
	if (i <= 0 or i > r) return;
	if (k <= 0 or k > c) return;

	if (!ans[i][k]) return;
	ans[i][k] = false;

	for (int z = 0; z < 4; z++) {
		if (_list[i+gx[z]][k+gy[z]] >= val) {
			dfs2(i+gx[z], k+gy[z], _list[i+gx[z]][k+gy[z]]);
		}
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

	cin >> r >> c;

	_list.resize(r+2);
	for (auto &i : _list)
		i.resize(c+2);

	vis.resize(r+2);
	for (auto &i : vis)
		i.resize(c+2);

	ans.resize(r+2);
	for (auto &i : ans)
		i.resize(c+2, true);

	go.resize(r+2);
	for (auto &i : go)
		i.resize(c+2);
	
	for (int i = 1; i < r+1; i++)
		for (int k = 1; k < c+1; k++) {
			cin >> _list[i][k];

			go[i][k] = _list[i][k] < 0;
			_list[i][k] = abs(_list[i][k]);
		}
	
	for (int i = 1; i < r+1; i++) {
		for (int k = 1; k < c+1; k++) {
			if (!vis[i][k]) {
				dfs1(i, k);

				if (pq.top() > _list[i][k] and go[i][k] == true) {
					dfs2(i, k, _list[i][k]);
				}

				while (pq.size()) pq.pop();
			}
		}
	}

	for (int i = 1; i <= r; i++)
		for (int k = 1; k <= c; k++) {
			cout << (ans[i][k] ? "Y" : "N") << " \n"[k == c];
		}
}
