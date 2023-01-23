#include <bits/stdc++.h>
using namespace std;
const int maxn = 200000; 
int seq[maxn+2];
int pos[maxn+2];
int main(){
//    cin.tie(0);
//    ios_base::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
 
    int ans = 1;
	pos[N+1] = maxn+1; // for edge case
    for (int i = 1; i <= N; i++){
		cin >> seq[i];
        pos[seq[i]] = i;
    }
    for (int i = 2; i <= N; i++){
        if(pos[i] < pos[i-1])
            ans++;
    }
	for (int i = 0; i < Q; i++){
		int a, b;
		cin >> a >> b;
		if (seq[a] > seq[b]) swap(a, b);

		if(pos[seq[a]] < pos[seq[a]-1]){
			ans -= 1;	
		}
		if(pos[seq[a] + 1] < pos[seq[a]]){
			ans -= 1;	
		}
		if(pos[seq[b]] < pos[seq[b]-1]){
			ans -= 1;	
		}
		if(pos[seq[b] + 1] < pos[seq[b]]){
			ans -= 1;	
		}
		if(seq[a] + 1 == seq[b] && pos[seq[a] + 1] < pos[seq[a]]){
			ans += 1;	
		}
//		cout << "tmp " << ans << endl;
		swap(seq[a], seq[b]);
		swap(pos[seq[a]], pos[seq[b]]);
		swap(a, b);	
		if(pos[seq[a]] < pos[seq[a]-1]){
			ans += 1;	
		}
		if(pos[seq[a] + 1] < pos[seq[a]]){
			ans += 1;	
		}
		if(pos[seq[b]] < pos[seq[b]-1]){
			ans += 1;	
		}
		if(pos[seq[b] + 1] < pos[seq[b]]){
			ans += 1;	
		}
		if(seq[a] + 1 == seq[b] && pos[seq[a] + 1] < pos[seq[a]]){
			ans -= 1;	
		}
		cout << ans << endl;
/*		for(int j = 1; j <= N; j++){
			cout << seq[j] << " \n"[j == N];
		}*/
	}
    return 0;
}
