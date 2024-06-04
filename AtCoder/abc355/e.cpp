
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

int ask(int i, int j)
{
	cout << "? " << i << " " << j << endl;
	int ans;
	cin >> ans;
	return ans;
}

int main() {
	yccc;
	int N, L, R;
	cin >> N >> L >> R;
	int i, j;

	int Lrem, Rrem;

	if (R == 0)
	{
		cout << ask(0, 0) << endl;
		return 0;
	}

	if(L == 0)
	{
		Lrem = ask(0, 0); 
	}
	else
	{
		for(int i = 1; (1 << i) <= L; i++)
		{
			if (L & (1 << i) != 0)
			{
				Lrem += ask(i, 0);
			}
		}
	}
	
	for(int i = 1; i <= R; (i<<=1))
	{
		
	}


	bool sol = false;
	while(sol == false)
	{

	}
}
