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


void re_num(string &str, char []cstr){
	for(size_t i = 18; i >= 0; i--){
		if(i < str.length())
			cstr[i] = str[str.length() - 1 - i];
		else
			cstr[i] = '0';
	}
}

int dp_a[20][10][2][2] = {0};
int dp_b[20][10][2][2] = {0};

void solve(int**** dp, char []number){
	for(size_t i = 18; i>= 0; i--){
		for(size_t d = 0; d <= 9; d++){

		}
	}
}

int main(){
	yccc;		
	string a, b;
	char astr[20], bstr[20];
	cin >> a >> b;
	re_num(a, astr); re_num(b, bstr);





	return 0;
}

