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
const ll MOD = 1000000007LL;

const int K = 26;
struct Vertex{
	int next[K];
	bool output = false;
	Vertex(){
		fill(begin(next), end(next), -1);
	}
};

vector<Vertex> trie(1);

void add_string(string &s){
	int v = 0;
	for(char ch: s){
		int c = ch - 'a';
		if(trie[v].next[c] == -1){
			trie[v].next[c] = trie.size();
			trie.eb();
		}
		v = trie[v].next[c];
	}
	trie[v].output = true;
}

ll dp[5000];
int main(){
	yccc;		
	string str;
	cin >> str;
	int k;
	cin >> k;
	for(int i = 0; i < k; i++){
		string w;
		cin >> w;
		reverse(al(w));
		add_string(w);
	}
	for(int i = 0; i < (int)str.length(); i++){
		int v = 0;
		//debug(i);
		for(int j = i; j >= 0; j--){
			v = trie[v].next[str[j] - 'a'];
			if(v == -1) break;
			if(trie[v].output == true){
//				cout << "match " << j << ", " << i << endl;
				if(j == 0){
					dp[i] += 1;	
				}
				else{
					dp[i] += dp[j - 1];
				}
			}
			dp[i] %= MOD;
		}		
	}
	/*
	for(int i = 0; i < (int)str.length(); i++)
		cout << dp[i] << " ";
	cout << endl;*/
	cout << dp[str.length()-1] << endl;

	return 0;
}

