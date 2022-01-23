#include<iostream>
#include<sstream>
#include<algorithm>
#define N 500001
using namespace std;
int k,cnt;
int a[N];
char p;
string str;
stringstream ss;
bool determine(int x){
	int cost = 0, step = 0;
	for(int i=0;i<cnt;i++){
		cost += a[i];
		if(cost > x){
			cost = a[i];
			step++;
		}
	}
	return ++step <= k;
}
int divide(int l, int r){
	//左閉右閉 
	if(l == r) return l;
	int mid = (l + r) / 2;
	if(determine(mid)) return divide(l, mid);
	return divide(mid + 1, r);
}
int main(){
	// cin.tie(0);
	// ios_base::sync_with_stdio(0);
	cin >> k;
	// EOF 輸入 
    
	while(cin >> k >> str){
		ss.clear();
		ss.str(str + 'R'); //終點當作R 
		int Max = 0; //R-R之間最遠的距離 
		cnt = 0;
		//a : 走到下一個R距離多少 
		for(int i=1; ss>>p; i++){
			if(p == 'R'){
				a[cnt++] = i;
				Max = max(Max,i);
				i = 0;
			}
        }
        // atsushi
        // cout << "cnt = " << cnt << '\n';
        // for (int i = 0; i < cnt; i++){
        //      cout << "a[" << i << "]= " << a[i] << " ";
        // }
        // cout << '\n';

        cout << divide(Max, N) << '\n';
	}
}