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
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
vec<ll> mval, pval;
int n;
bool check(int K){
	if(K == 0)
		return true;
	// i in [K, 2K]
	vec<ll> Lprofit(n+1, 0); 
	vec<ll> Rprofit(n+1, 0); 
// Left Part
	priority_queue<pair<ll, int>, vec<pair<ll,int>>, greater<pair<ll, int>>> pq; // to steal
	for(int j = 1; j <= K; j++){
		pq.emplace(mval[j] + pval[j], j);
		Lprofit[K] += mval[j];
	}
	for(int i = K+1; i <= 2*K; i++){
		ll res = mval[i] + pval[i];
		Lprofit[i] = Lprofit[i-1];
		if(res > pq.top().F){
			Lprofit[i] -= mval[pq.top().S];	
			Lprofit[i] -= pval[pq.top().S];	
			Lprofit[i] += mval[i];
			pq.pop();
			pq.emplace(res, i);
		}	
		else{
			Lprofit[i] -= pval[i];
		}
	}
// Right Part
	while(pq.size()) pq.pop();

	for(int j = n; j> 2*K; j--){
		pq.emplace(pval[j], j);
	}
	for(int i = 2*K; i > K; i--){
		Rprofit[i-1] = Rprofit[i]; 
		if(pval[i] < pq.top().F){
			Rprofit[i-1] -= pval[i];
		}
		else{
			Rprofit[i-1] -= pq.top().F;
			pq.pop();
			pq.emplace(pval[i], i);
		}
	}
	/*
	debug(K);
	for(int i = K; i <= 2*K; i++){
		cout << i << ": Lprofit= " << Lprofit[i] << ", Rprofit= " << Rprofit[i] << endl;
	}
	*/

	for(int i = K; i <= 2*K; i++){
		if(Lprofit[i] + Rprofit[i] >= 0){
			return true;
		}
	}

	return false;
}

int main(){
	yccc;		
	cin >> n;
	mval.resize(n+1), pval.resize(n+1);
	for(int i = 1; i <= n; i++)
		cin >> mval[i];
	for(int i = 1; i <= n; i++)
		cin >> pval[i];
	vec<int> idx(n);  
	iota(al(idx), 1);
	sort(al(idx), [&](int a, int b){
		return mval[a] > mval[b];
	});
	vec<ll> nmval(n+1), npval(n+1);
	for(int i = 1; i <= n; i++){
		nmval[i] = mval[idx[i-1]];
		npval[i] = pval[idx[i-1]];
	}
	mval = nmval, pval = npval;

	int L = 0, R = n/2;

	while(L < R){
		int M = R - ((R-L) >> 1);
		/*
		debug(L);
		debug(R);
		debug(M);
		*/
		
		if(check(M)){
			L = M;
		}
		else{
			R = M-1;
		}
	}
	cout << L << endl;

	return 0;
}

