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
const int maxn = 200000;
vec<int> seq, uni;
bool inside[maxn];
int main(){
	yccc;		
	int n;
	cin >> n;
	seq.resize(n);
	for(int i = 0; i < n; i++){
		cin >> seq[i];
	}
	copy(al(seq), back_inserter(uni));
	sort(al(uni));
	uni.resize(distance(uni.begin(), unique(al(uni))));
	for(int i = 0; i < n; i++){
		seq[i] = distance(uni.begin(), lower_bound(al(uni), seq[i]));
	}
	queue<int> mq;
	int ans = 0;
	for(int i = 0; i < n; i++){
		if(inside[seq[i]]){
			while(mq.front() != seq[i]){
				inside[mq.front()] = false;
				mq.pop();
			}
			mq.pop();
		}
		mq.push(seq[i]);
		inside[seq[i]] = true;
		ans = max(ans, (int)mq.size());
	}
	cout << ans << endl;


	return 0;
}

