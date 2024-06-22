
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

int main() {
	yccc;
	ll sx, sy, tx, ty;
	cin >> sx >> sy >> tx >> ty;
	if (sx > tx)
	{
		swap(sx, tx); swap(sy, ty);
	}
	ll dx = abs(tx-sx);
	ll dy = abs(ty- sy);
	ll ans =  dx + dy;

	ans -= min(dx, dy);

	if(dx > dy){
		
		sx += dy;
		sy = ty;

		ll tod = 0;
		ll oddx = (sx & 1) == 1;
		ll oddy = (sy & 1) == 1;
		bool case1 = (oddx && oddy) || (!oddx && !oddy);
	//ll case2 = !case1;
		dx = tx - sx;

		if(case1)
		{
			if(dx & 1)
			{
				ans -= (dx+1)/2;
			}
			else
			{
				ans -= dx / 2;
			}
		}
		else{

			ans -= dx / 2;
		}
	}
	cout << ans << endl;
	return 0;
	

}
