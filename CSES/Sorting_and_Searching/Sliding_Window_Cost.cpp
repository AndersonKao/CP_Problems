
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

multiset<int> lset, rset;
ll lsum, rsum;
size_t n, k;
void insert(int val){
	if(lset.size() == 0 || val > *lset.rbegin()){
		rset.insert(val);
		rsum += val;
	}
	else{
		lset.insert(val);
		lsum += val;
	}
}
void balance(){
	while(lset.size() < (k+1)/2)
	{
		auto rmin = rset.begin();
		lsum += *rmin;
		rsum -= *rmin;
		lset.insert(*rmin);
		rset.erase(rmin);	
	}
	while(lset.size() > (k+1)/2)
	{
		auto lmax= lset.find(*lset.rbegin());
		lsum -= *lmax;
		rsum += *lmax;
		rset.insert(*lmax);
		lset.erase(lmax);	
	}
}

void remove(int val){
	if(val > *lset.rbegin()){
		auto it = rset.find(val);
		rset.erase(it);
		rsum -= val;
	}
	else{
		auto it = lset.find(val);
		lset.erase(it);
		lsum -= val;
	}
}

ll getans()
{
	ll ans = 0;
	if(k & 1)
	{
		ans = rsum - lsum + (*lset.rbegin());
	}
	else{
		ans = rsum - lsum;
	}
	return ans;
}

int main(){
	yccc;		
	cin >> n >> k;
	vec<int> V(n);
	for(size_t i = 0; i < n; i++){
		cin >> V[i];
	}
	lsum = rsum = 0;
	for(size_t i = 0; i < n; i++){
		insert(V[i]);
		if(i >= k-1){
			balance();
			/*
			cout << "left: ";
			for(int a: lset){
				cout << a << " ";
			}
			cout << ", ";
			cout << "right: ";
			for(int a: rset){
				cout << a << " ";
			}
			cout << endl;
			*/
			cout << getans() << (i == n-1 ? '\n' : ' ');
			remove(V[i-k+1]);
		}
	}

	return 0;
}

