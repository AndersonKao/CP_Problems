#include <bits/stdc++.h>
using namespace std;
#define al(x) x.begin(), x.end()
#define eb emplace_back
#define F first
#define S second
#define LC(x) (x * 2 + 1)
#define RC(x) (x * 2 + 2)
#define debug(x) cout << #x << ": " << x << endl;
struct segT{
	vector<int> seq; // if there's 1 in this range
	vector<int> tag; // these range all set to
	int N;
	void Build(int n){
		N = n;	
		seq.clear();
		tag.clear();
		seq.resize(4*N, 0);
		tag.resize(4*N, -1);
		build(0, N-1, 0);
	}
	void build(int l, int r, int idx){
		if(l == r){
			seq[idx] = 0;
			tag[idx]= 0;
			return;
		}
		int M = (l+r) >> 1;
		build(l, M, LC(idx));
		build(M+1, r, RC(idx));
	}
	void push(int idx){
		int li = LC(idx), ri = RC(idx);
		if(tag[idx] != -1)
			tag[li] = tag[ri] = tag[idx];
		if(tag[idx] == 1)
			seq[li] = seq[ri] = 1;	
		if(tag[idx] == 0)
			seq[li] = seq[ri] = 0;	
		tag[idx] = -1;
	}
	void pull(int idx){
		int li = LC(idx), ri = RC(idx);
		if(seq[li] || seq[ri]){
			seq[idx] = 1;
		}
		if(tag[li] == tag[ri]){
			tag[idx] = tag[li];
		}
		else
			tag[idx] = -1;
	}
	void Modify(int l, int r, int val){
		if(l <= r)
			modify(l, r, 0, N-1, 0, val);
	}
	void modify(int l, int r, int L, int R, int idx, int val){
		if(l <= L && R <= r){
			seq[idx] = val;
			tag[idx] = val;
			return;
		}
		if(r < L || R < l)
			return;
		push(idx);
		int M = (L+R) >> 1;
		modify(l, r, L, M, LC(idx), val);
		modify(l, r, M+1, R, RC(idx), val);
		pull(idx);
	}
	int Query(int l, int r){
		if(l <= r)
			return query(l, r, 0, N-1, 0);
		else
			return -1;
	}
	int query(int l, int r, int L, int R, int idx){
		if(r < L || R < l)
			return -1;	
//		debug(idx);
//		cout << "visit " << l << ", " << r << endl;
		if(l <= L && R <= r && tag[idx] == 1){
			return R;
		}
		if(L == R){
			if(seq[idx] == 1){
				return L;
			}
			else
				return -1;
		}
		if(seq[idx] == 0)
			return -1;
		push(idx);
		int M = (L + R) >> 1;	
		int li = LC(idx), ri = RC(idx);
		int ans = -1;
		if(M <= r && seq[ri]){
			ans = query(l, r, M+1, R, RC(idx));	
		}
		if(ans == -1 && l <= M && seq[li]){
			ans = query(l, r, L, M, LC(idx));
		}
		pull(idx);
		return ans;
	}
};
using pii = pair<int, int>;
using ll = long long;
int main(){
	int caseN = 1;
	int m,n,w;	
	while(cin >> m >> n >> w){
		if(m == 0 && n == 0 && w == 0)
			break;	
		segT mT;	
		mT.Build(n);
		vector<vector<pii>> walls(m);
		ll walln = 0;
		for(int i = 0; i < w; i++){
			int x1, x2, y1, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			walls[y1].eb(x1, x2);
			walln += x2 - x1 + 1;
		}
		for(int i =0; i < m; i++){
			sort(al(walls[i]));
		}
		ll ans = n;
		mT.Modify(0, n-1, 1);
		if(walls[m-1].size()){
			mT.Modify(0, walls[m-1].back().S, 0);
			ans -= (walls[m-1].back().S + 1);
		}
		int prev = ans;
		for(int ri = m-2; ri >= 0; ri--){
			vector<pii>& curw = walls[ri];
#ifdef Dri
			debug(ri);
			debug(ans);
			debug(curw.size());
#endif
			if(curw.size() == 0){
				if(walls[ri+1].size() == 0){
					ans += prev;
				}
				else{
					int pos = mT.Query(0, n-1);
//					debug(pos);
					if(pos != -1){
						ans += (prev = (pos + 1));
						mT.Modify(0, pos, 1);
						mT.Modify(pos + 1, n-1, 0);
					}
					else{
						mT.Modify(0, n-1, 0);
						break;
					}
				}
				continue;
			}
			for(int wi = 0; wi < curw.size(); wi++){
				int l = (wi == 0 ? 0 : curw[wi-1].S + 1);
				int r = curw[wi].F - 1;
#ifdef Dwi
				cout << wi << ": " << l << " to " << r << endl;
#endif
				if(l <= r){
					int pos = mT.Query(l, r);
#ifdef Dwi
					debug(pos);
#endif
					if(pos != -1){
						ans += (pos - l + 1);
						mT.Modify(l, pos, 1);
						mT.Modify(pos + 1, r, 0);
#ifdef Dwi
						//debug(ans);
#endif
					}
					else
						mT.Modify(l, r, 0);
				}
				l = curw[wi].F, r = curw[wi].S;
				mT.Modify(l, r, 0);
			}
			
			int l = curw.back().S + 1, r = n-1;
			int pos = mT.Query(l, r);	
#ifdef Dwi
			cout << "last: " << l << " to " << r << endl;
			debug(pos);
#endif
			if(pos != -1){
				ans += (pos - l + 1);
				mT.Modify(l, pos, 1);
				mT.Modify(pos + 1, r, 0);
			}
			else
				mT.Modify(l, r, 0); 
		}	
		//debug(ans);
		cout << "Case " << caseN++ << ": ";
		cout << (long long)m * n - ans - walln<< endl;
	}
	return 0;
}
