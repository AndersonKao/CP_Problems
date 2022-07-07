#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, k;
int a[11][11];
int ans = 0;

void Dfs(int x, int y, int now) {
	if (x == n + 1) {
		ans += (now >= k);
		return;
	}
	if (!~a[x][y]) {
		for (int i = 0; i <= n; ++ i) {
			if (y == n) Dfs(x + 1, 1, now + (n * (x - 1) + y) * i);
			else Dfs(x, y + 1, now + (n * (x - 1) + y) * i);
		}
	} else {
		if (y == n) Dfs(x + 1, 1, now + (n * (x - 1) + y) * a[x][y]);
		else Dfs(x, y + 1, now + (n * (x - 1) + y) * a[x][y]);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int t;
	cin >> t;
	while ( t -- ) {
		cin >> n >> k;
		for (int i = 1; i <= n; ++ i) {
			for (int j = 1; j <= n; ++ j) {
				char c;
				cin >> c;
				a[i][j] = (c != 'X' ? c - '0' : -1);
			}
		}
		ans = 0;
		Dfs(1, 1, 0);
		cout << ans << "\n";
	}
}