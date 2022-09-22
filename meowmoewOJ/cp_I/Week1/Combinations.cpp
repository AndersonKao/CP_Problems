#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
int n, m;
int seq[22], A[22];
void recur(int i, int id){
	if(id == m){
		REP(j, m){
			cout << seq[j] << (j == m-1 ? "\n" : " ");
		}
		return;
	}
	if(i == n)
		return;
	seq[id] = A[i];
	recur(i+1, id+1); 
	recur(i+1, id);
}

int main(){
	cin >> n >> m;
	REP(i, n)
		cin >> A[i];
	recur(0, 0);
	return 0;
}

