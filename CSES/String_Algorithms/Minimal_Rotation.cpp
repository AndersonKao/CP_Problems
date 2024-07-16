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

//O(nlgn) to build suffix array(sort cyclic shifts)
void sort_cyclic_shifts(string & s, vector<int> &p) {
	int n = (int)s.size();
	const int alphabet = 256;
	vector<int> c(n), cnt(max(n, alphabet), 0);
	
	for(int i=0;i<n;i++) cnt[s[i]]++;
	for(int i=1;i<alphabet;i++) cnt[i]+=cnt[i-1];
	for(int i=n-1;i>=0;i--) p[--cnt[s[i]]] = i;
	
	c[p[0]] = 0;
	int classes = 1;
	for(int i=1;i<n;i++) {
		if(s[p[i]] != s[p[i-1]]) classes++;
		c[p[i]] = classes-1;
	}
 
	vector<int> pn(n), cn(n);
	for(int h = 0; (1 << h) < n; h++){
		for(int i = 0; i < n; i++) {
			pn[i] = p[i] - (1 << h);
			if(pn[i] < 0) pn[i]+=n;
		}
		fill(cnt.begin(), cnt.begin() + classes, 0);
		
		for(int i=0;i<n;i++) cnt[c[pn[i]]]++;
		for(int i=1;i<classes;i++) cnt[i]+=cnt[i-1];
		for(int i=n-1;i>=0;i--) p[--cnt[c[pn[i]]]] = pn[i];
		
		cn[p[0]] = 0;
		classes = 1;
		for(int i=1;i<n;i++) {
			int val = (p[i] + (1 << h));
			int valp = (p[i-1] + (1 << h));
			pii cur = pii(c[p[i]], c[(val >= n ? val - n : val)]);
			pii prev = pii(c[p[i-1]], c[valp >= n ? valp - n : valp]);
			if(cur != prev) classes++;
			cn[p[i]] = classes - 1;
		}
		c.swap(cn);
	}
}

int main(){
	yccc;		
	string str;
	cin >> str;
	vec<int> SA(str.length());
   	sort_cyclic_shifts(str, SA);
	/*
	for(int i = 0; i < SA.size(); i++){
		cout << i << ": " << str.substr(SA[i]);
		if(SA[i] > 0){
			cout << str.substr(0, SA[i]);
		}
		cout << endl;
	}
	*/
	for(int i = SA[0]; i < str.length(); i++){
		cout << str[i];
	}
	for(int i = 0; i < SA[0]; i++){
		cout << str[i];
	}
	cout << endl;
	
	return 0;
}

