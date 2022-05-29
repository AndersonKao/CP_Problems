#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
using ll = long long;
template<typename T>
using vec = vector<T>;
using pii = pair<int, int>;

#define debug(x) cout << #x << ": " << x << endl;

int main(){
	int a ,b, c;
	cin >> a >> b >> c;
	if(a <= b && b <= c)
	cout << "Yes\n";
 else	if(c <= b && b <= a)
	cout << "Yes\n";
	else

		cout << "No\n";
	return 0;
}
