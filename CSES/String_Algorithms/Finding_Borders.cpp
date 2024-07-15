
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


// f[i]: failure function, the length of longest proper prefix of P[0..i] that is also the suffix of P[0..i]
// T for Text, P for Pattern
vec<int> KMP(const string& P) {
    vec<int> f(P.size(), 0);
    for (int i = 1; i < P.size(); ++i) {
		int len = f[i-1];
        while (len > 0 && P[len] != P[i])
            len = f[len-1];
        if (P[len] == P[i])
            ++len;
        f[i] = len;
    }
    return f;
}

// find S in T in O(|S| + |T|) time O(|S|) space
vec<int> KMP_match(vec<int> fofS, const string& S, const string& T) {
    vec<int> res; // start from these points
    int n = S.size();

    int len = 0;
    for (int j = 0; j < T.size(); ++j) {
        while (len > 0 && T[j] != S[len]) {
            len = fofS[len-1];
		}

        if (T[j] == S[len]){
			len++;
		}

        if (len == n) {
            res.eb(j - len + 1);
			len = fofS[len - 1];
		}
    }
    
    return res;
}


// we set pi[0] = 0, and if (i+1) % ((i+1) - prefix[i]) == 0,
// the minimum circular string length will be (i+1) - prefix[i],
// otherwise it will be (i+1) (no circular).
// ex. abcabcabcabcabc = abc*5.

int main() {
	yccc;
	string str;
	cin >> str;
	vec<int> fail = KMP(str);

	vec<int> ans;
	int len = (int)str.length();
	while(len > 0){
		len = fail[len-1];
		if(len > 0)
			ans.eb(len);
	}

	for(int i = ans.size()-1; i >= 0; i--){
		cout << ans[i] << (i == 0 ? '\n' : ' ');
	}

	return 0;
}
