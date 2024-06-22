
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

int main() {
	yccc;
	int n;
	cin >> n;
	int c[200];
	for(int i = 0;i < 2*n; i++){
		cin >> c[i];
	}
	int ans = 0;
	for(int co = 1; co <= n; co++){
		int a = -1, b = -1;
		for(int i = 0; i < 2*n; i++){
			if(c[i] == co){
				if(a == -1)
				{
					a = i;
				}
				else
				{
					b = i;
				}
			}
		}
		if(b - a == 2){
			ans++;
		}
	}
	cout << ans;
	return 0;
}
