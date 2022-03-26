#include <bits/stdc++.h>
using namespace std;

#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define REP(i, n) for(int i = 0; i < n; i++)
#define RC(i) (i * 2 + 1)
#define LC(i) (i * 2 + 2)



struct segT{
	int seq[800000];
	int data[200000];
	int n;
	segT(){};
	segT(int n): n(n){

	}	
	void build(int l, int r, int index){
		if(l == r){
			seq[index] = data[l];
			return;
		}

		int M = (l + r) >> 1;
		
		build(l, M, LC(index));
		build(M + 1, r, RC(index));
		seq[index] = min(seq[LC(index)], seq[RC(index)]);
	}
	int Query(int l, int r){
		return query(l, r, 0, n-1, 0);
	}
	int query(int l, int r, int L, int R, int index){
		if(l <= L && r >= R){
			return seq[index];
		}
		if(l > R || r < L)
			return numeric_limits<int>::max();
		int M = (L + R) >> 1;

		return min(query(l, r, L, M, LC(index)), query(l, r, M+1,R, RC(index)));
	}
};

segT* mT;


int main(){
	
//	yccc;
	int n, q;
	
	cin >> n >> q;
	mT = new segT(n);	
	REP(i, n){
		cin >> mT->data[i];
	}
	mT->build(0, n - 1, 0); 
	int qL, qR;
	REP(i, q){
		cin >> qL >> qR;
		qL--, qR--;
		cout << mT->Query(qL, qR) << endl;
	}
	
	

	return 0;
}
