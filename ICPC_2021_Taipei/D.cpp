#include <bits/stdc++.h>
using namespace std;

#define LL long long
LL K;
int D;

LL seq[20];
LL modseq[17][17];
// i * 10 ^ j MOD K;
bool pos[1<<16][200] = {false};
// # of 1 means considering frist # nubmer

LL getrem(LL rem, LL tom){
	rem -= tom;
	if(rem < 0) rem += K;
	return rem;
}

LL Getans(LL target){
	int bitnum = D;
	int curRem = target;	
	int curset = (1<<D)-1;
	LL ans = 0;
	LL tmp = 1;
	for(int i = 1; i < D; i++)
		tmp *= 10;
	while(bitnum--){
		for(int i = 0; i < D; i++){
			if(!(curset & (1 << i)))
				continue;
			LL tode = getrem(curRem, modseq[i][(bitnum)]);
			LL askset = curset ^ (1 << i);
			if(pos[askset][tode]){
				curset = askset;
				curRem = tode;	
				ans += seq[i] * tmp;
				tmp /= 10;
				break;
			}
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> D >> K;
	for(int i = 0; i < D; i++)
		cin >> seq[i];
	pos[0][0] = true;
	sort(seq, seq + D, greater<int>());
	LL tmp = 1;
	for(int i = 0; i < D; i++){
		for(int j = 0; j < D; j++){
			modseq[j][i] = seq[j] * tmp % K;
		}
		tmp *= 10;
	}
	for(int sh = 0; sh < D; sh++){
		pos[1 << sh][modseq[sh][0]] = true;		
	}
	LL limit = (1 << D); 
	for(LL i = 1; i < limit; i++){
		int bitnum = 0;
		for(int j = 0; j < D; j++)
			if(i & (1 << j)) bitnum++;
		if(bitnum == 1) continue;
		for(int sh = 0; sh < D; sh++){
			LL mask = (1 << sh);
			if(i & mask){
				LL set = i ^ mask;
				for(int rem = 0; rem < K; rem++){
					pos[i][rem] = pos[i][rem] || pos[set][getrem(rem, modseq[sh][bitnum-1])];
				}
			}
		}
	} 

	for(int i = K-1; i >= 0; i--){
		if(pos[(1 << D) - 1][i] == true){
			cout << Getans(i) << endl;	
			break;
		}
	}
	return 0;
}
