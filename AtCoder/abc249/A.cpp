
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define al(a) a.begin(), a.end()
#define F first
#define S second
#define eb emplace_back

using ll = long long;
using pii = pair<int, int>;
template<typename T>
using vec = vector<T>;
auto cmp = [](int& a, int& b){
	return a < b;
};



int main(){
	int seq[7];
	REP(i, 7)
		cin >> seq[i];
	int atimes = seq[6] / (seq[0] + seq[2]);
	int btimes = seq[6] / (seq[3] + seq[5]);
	int ar = seq[6] % (seq[0] + seq[2]);
	int br = seq[6] % (seq[3] + seq[5]);
	ar = min(ar, seq[0]);
	br = min(br, seq[3]);
	int adis = (atimes * seq[0] + ar) * seq[1];
	int bdis = (btimes * seq[3] + br) * seq[4];
/*
	cout << adis << ", " << bdis << endl;
	cout << atimes << endl;
	cout << btimes << endl;
	cout << ar << endl;
	cout << br << endl;
*/
	if(adis > bdis)
		cout << "Takahashi\n";
	else if(adis < bdis)
		cout << "Aoki\n";
	else 
		cout << "Draw\n";
	
	return 0;
}
