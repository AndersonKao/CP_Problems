#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
#define F first
#define S second

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using p = pair<T, T>;

vec<vec<char>> _map;

ll binpow(int a, int r) {
	ll ret = 1;

	do {
		if (r % 2) ret *= a;
		a *= a;
	} while (r >>= 1);

	return ret;
}

void white(int r, int c, int lev) {
	
	int w = binpow(3, lev-1);

	for (int i = r + w; i < r + 2 * w; i++) {
		for (int k = c + w; k < c + 2 * w; k++) {
			_map[i][k] = ' ';
		}
	}

	if (lev != 1) {
		// white....
		white(r, c, lev-1);
		white(r+w, c, lev-1);
		white(r+2*w, c, lev-1);
		white(r, c+w, lev-1);
		white(r+2*w, c+w, lev-1);
		white(r, c+2*w, lev-1);
		white(r+w, c+2*w, lev-1);
		white(r+2*w, c+2*w, lev-1);
		for (int i = 0; i < 2; i++){
			for (int j = 0; j < 2; j++){
				if (i == 1 && j == 1)
					continue;
				white(r + w * i, c + w * j, lev - 1);
			}
		}
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

	int n;
	cin >> n;

	int _size = binpow(3, n);
	
	_map.resize(_size);
	for (int i = 0; i < _size; i++)
		_map[i].resize(_size, '#');
	
	white(0, 0, n);

	for (int i = 0; i < _size; i++) {
		for (int k = 0; k < _size; k++) {
			cout << _map[i][k];
		}
		cout << endl;
	}
}
