#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, treeorder_statistics_node_update>;
*/
#define REP0(i, n) for (int i = 0; i < n; i++)
#define REP(i, a, b) for(int i = a; i <= b; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define ln '\n'
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;

int count(string& str, int pos){
	int res = 0;
	for(int i = pos - 2; i <= pos; i++){
		if(i < 0 || i + 2 >= str.length()) continue;
		if(str[i] == 'A' && str[i+1] == 'B' && str[i+2] == 'C') res++;
	}
	return res;
}

int main(){
	yccc;		
	int n, m;
	cin >> n >> m;
	string str;
	cin >> str;
	int cur = 0;
	for(int i = 0; i < str.length(); i++){
		if(i < 0 || i + 2 >= str.length()) continue;
		if(str[i] == 'A' && str[i+1] == 'B' && str[i+2] == 'C') cur++;
	}

	while(m--){
		int k; char ch;
		cin >> k >> ch;
		k--;
		cur -= count(str, k);
		str[k] = ch;
		cur += count(str, k);
		cout << cur << endl;;
	}

	return 0;
}

