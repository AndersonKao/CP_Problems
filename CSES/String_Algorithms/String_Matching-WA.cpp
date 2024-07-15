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
 
// T for Text, P for Pattern
vec<int> KMP(const string& P) {
    vec<int> f(P.size(), -1);
    int len = f[0] = -1;
    for (int i = 1; i < P.size(); ++i) {
        while (len != -1 && P[len + 1] != P[i])
            len = f[len];
        if (P[len + 1] == P[i])
            ++len;
        f[i] = len;
    }
    return f;
}
 
// find S in T
vec<int> KMP_match(vec<int> fail, const string& S, const string& T) {
    vec<int> res; // start from these points
    int n = S.size();
 
    int i = -1;
    for (int j = 0; j < T.size(); ++j) {
        while (i != -1 && T[j] != S[i + 1]) 
            i = fail[i];
 
        if (T[j] == S[i + 1]) i++;
        if (i == n - 1) 
            res.eb(j - n + 1), i = fail[i];
    }
    
    return res;
}
 
// Counting the number of occurrences of each prefix
/*
void prefix_occur(){
    vector<int> ans(n + 1);
    for (int i = 0; i < n; i++)
        ans[pi[i]]++;
    for (int i = n-1; i > 0; i--)
        ans[pi[i-1]] += ans[i];
    for (int i = 0; i <= n; i++)
        ans[i]++;
}
*/
 
// we set pi[0] = 0, and if (i+1) % ((i+1) - prefix[i]) == 0,
// the minimum circular string length will be (i+1) - prefix[i],
// otherwise it will be (i+1) (no circular).
// ex. abcabcabcabcabc = abc*5.
 
int main() {
	yccc;
 
	string n, m;
	cin >> n >> m;
	vec<int> fail = KMP(n); // should be string m.
	vec<int> match = KMP_match(fail, m, n);
	cout << match.size();
 
	return 0;
}
