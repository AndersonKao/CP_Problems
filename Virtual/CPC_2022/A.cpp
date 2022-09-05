#include <bits/stdc++.h>
using namespace std;
#define LC(x) (2*x+1)
#define RC(x) (2*x+2)
struct segT{
	vector<int> seq; // if [L,R] contains light
	vector<int> tag; // if [L,R] all set to light -> 1, dark -> 2.
	int N;
	void Build(int N){
		this->N = N;
		seq.resize(4*N, 1);
		tag.resize(4*N, 1);
	}
	void push(int idx){
		int li = LC(idx), ri = RC(idx);
		if(tag[idx] == 2){
			seq[li] = seq[ri] = 0;		
			tag[li] = tag[ri] = 2;
		}
		else if(tag[idx] == 1){
			seq[li] = seq[ri] = 1;		
			tag[li] = tag[ri] = 1;
		}
		tag[idx] = 0;
		seq[idx] = 0;
	}
	void pull(int idx){
		int li = LC(idx), ri = RC(idx);
		if(tag[li] && tag[ri] && tag[li] == tag[ri])
			tag[idx] = tag[li];
		else
			tag[idx] = 0;
	
		if(seq[li] || seq[ri])
			seq[idx] = 1;
		else
			seq[idx] = 0;
	}

	void Modify(int l, int r, int val){
//		cout << "toggole " << l << " to " << r << " to " << val << ".\n";
		if(r < l)
			return;
		modify(l, r, 0, N-1, 0, val);
	}
	void modify(int l, int r, int L, int R, int idx, int val){
		if(R < l || r < L)
			return;
//		cout << "modify " << L << ", " << R << endl;
		if(l <= L && R <= r){
			seq[idx] = val;
			tag[idx] = (val == 1 ? 1 : 2);
			return ;
		}
		int M = (L+R) >> 1;
		push(idx);
		modify(l, r, L, M, LC(idx), val);
		modify(l, r, M+1, R, RC(idx), val);
		pull(idx);
	}
	bool Query(int l, int r){
		if(r < l)
			return false;
		return query(l, r, 0, N-1, 0);
	}
	bool query(int l, int r, int L, int R, int idx){
		if(R < l || r < L)
			return false;
		if(l <= L && R <= r){
			return seq[idx];
		}
		int M = (L+R) >> 1;
		push(idx);
		bool ans = query(l, r, L, M, LC(idx)) || query(l, r, M+1, R, RC(idx));
		pull(idx);
		return ans;
	}
	void Print(){
		print(0, N-1, 0);
	}
	void print(int l, int r, int idx){
		//cout << l << " to " << r << ", seq: " << seq[idx] << ", tag " << tag[idx] << endl;
		if(l >= r){
			return;
		}
		int m = (l+r) >> 1;
		print(l, m, LC(idx));
		print(m+1, r, RC(idx));
	}
};
struct wall{
	int x1, x2, y;
};

int main(){
	int T;
	cin >> T;
	while(T--){
		int n, q;
		cin >> n >> q;
		vector<wall> walls(q);
		for(int i = 0; i < q; i++){
			cin >> walls[i].x1 >> walls[i].x2 >> walls[i].y;
		}
		auto cmp  = [](wall & w, wall& w2){
			return w.y < w2.y;
		};
		sort(walls.begin(), walls.end(), cmp);
		segT mT;
		mT.Build(n+2);
		mT.Print();
		for(int i = 0; i < q; i++){
			wall &w = walls[i];
//			cout << "doing " << w.x1 << ", " << w.x2 << ", " << w.y << endl;
			bool has = mT.Query(w.x1, w.x2);
			
			if(has){
//				cout << "has\n";
				mT.Modify(w.x1 + 1, w.x2 - 1, 0);
//				cout << i << ": ------------------\n";
//				mT.Print();
				mT.Modify(w.x1, w.x1, 1);
//				cout << i << ": ------------------\n";
//				mT.Print();
				mT.Modify(w.x2, w.x2, 1);
			}
//			cout << i << ": ------------------\n";
//			mT.Print();
		}
		int ans = 0;
		for(int i = 1; i <= n; i++){
			ans += (int)mT.Query(i, i);
		}
		cout << ans << endl;
	}
	return 0;
}
