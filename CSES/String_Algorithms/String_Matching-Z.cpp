
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

// Z(k): the length of longest substring of s that begins at k and is a prefix of s.
vector<int> Zalgorithm(string &s) {
	int n = s.size();
	vector<int> z(n, 0);
	int L = 0, R = 0;
	for(int i=1;i<n;i++) {
		z[i] = max(0, min(z[i-L], R-i+1));
		while(i + z[i] < n && s[z[i]] == s[i + z[i]]){
			L = i;
			R = i + z[i];
			z[i]++;
		}
	}
	return z;
}

int main() {
	yccc;

	string n, m;
	cin >> n >> m;
	string str = m + "#" + n;
	vec<int> Z = Zalgorithm(str);
	int ans = 0;
	for(size_t i = m.size()+1; i < str.length(); i++){
		if(Z[i] == (int)m.length()) ans++;
	}
	cout << ans << endl;

	return 0;
}
