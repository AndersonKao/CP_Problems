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
const int range = 10000;
int main(){
	int n;
	int x, y;
	cin >> n >> x >> y;
	vec<int> A(n);
	for(int&e : A)
		cin >> e;	
	vec<int> xposi(2 * range+ 1, -1);
	vec<int> yposi(2 * range+ 1, -1);
	xposi[0 + range + A[0]] = 0; 
	yposi[0 + range + A[1]] = 1; 
	yposi[0 + range - A[1]] = 1; 
	for(int i = 2; i < n; i++){
		if(i & 1){ // up-down
			vec<int> ny (2*range+1);
			for(int p = -range + range; p <= range + range; p++){
				if(p - A[i] >= 0){
					if(yposi[p - A[i]] == i - 2){
						ny[p] = i;
					}
				}
				if(p + A[i] <= range*2){
					if(yposi[p + A[i]] == i - 2){
						ny[p] = i;
					}
				}
			}
			yposi = ny;
		}
		else{
			vec<int> nx (2*range+1);
			for(int p = -range + range; p <= range + range; p++){
				if(p - A[i] >= 0){
					if(xposi[p - A[i]] == i - 2){
						nx[p] = i;
					}
				}
				if(p + A[i] <= range*2){
					if(xposi[p + A[i]] == i - 2){
						nx[p] = i;
					}
				}
			}
			xposi = nx;
		}
	}
	int tary = (n - 1) - (n & 1); 
	int tarx = tary == (n-1) ? n-2 : n-1; 
	if(xposi[x + range] == tarx && yposi[y + range] == tary){
		cout << "Yes\n";
	}
	else{
		cout << "No\n";
	}

	return 0;
}

