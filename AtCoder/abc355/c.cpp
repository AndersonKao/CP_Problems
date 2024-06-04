#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(), a.end()
#define eb emplace_back
#define F first
#define S second

int table[2005][2005];
int ops[200005];
int n, T;

void fill(int round)
{
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			table[i][j] = 0;
	for(int i = 1; i <= round; i++)
	{
		int r = ops[i] / n + 1;
		int c = ops[i] % n;
		if (c == 0){
			c = n;
			r -= 1;
		}	
		table[r][c] = 1;
	}
	/*
	cout << "curtable\n";
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			cout << table[i][j] << (j != n ? ' ': '\n');
			*/
}
bool check()
{
	for( int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++){
			if(table[i][j] == 0)
				break;
			if(j == n)
				return true;
		}
		for(int j = 1; j <= n; j++){
			if(table[j][i] == 0)
				break;
			if(j == n)
				return true;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		if (table[i][i] == 0)
			break;
		if (i == n) return true;
	}

	for(int i = 1; i <= n; i++)
	{
		if (table[i][n - i + 1] == 0)
			break;
		if (i == n) return true;
	}
	return false;
}

int main() {
	yccc;
	cin >> n >> T;
	for (int i = 1; i <= T; i++)
		cin >> ops[i];

	int l = 1, r = T;
	fill(T);
	if(check() == false)
	{
		cout << -1 << endl;
//		cout << "imp" << endl;
		return 0;
	}
	while(l < r)
	{
//		cout << l << ", " << r << endl;
		int mid = ( l+r )/2;
		fill(mid);
		bool bingo = check();
		if(bingo)
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}

	cout << l << endl;	

}
