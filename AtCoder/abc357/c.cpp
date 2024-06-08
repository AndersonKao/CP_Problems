
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

char ans[2000][2000];
int n;

int getpw(int p, int k)
{
	int ans = 1;
	for(int i = 0; i < k; i++)
	{
		ans *= p;
	}
	return ans;
}

void recur(int n, int bi, int bj)
{
	if(n == 0)
	{
		return ;
	}

	int len = getpw(3, n-1);

	for(int i = 0; i < len; i++)
	{
		for(int j = 0; j < len; j++)
		{
			ans[bi+len+i][bj+len+j] = '.';
		}
	}

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			recur(n-1, bi + i * len, bj + j * len);
		}
	}
}


int main() {
	yccc;

	cin >> n;
	int pw = getpw(3, n);
	for(int i = 0; i < pw; i++)
	{
		for(int j = 0; j < pw; j++)
		{
			ans[i][j] = '#';
		}
	}
	recur(n, 0, 0);
	for(int i = 0; i < pw; i++)
	{
		for(int j = 0; j < pw; j++)
		{
			cout << ans[i][j];
		}
		cout << endl;
	}

	return 0;
}
