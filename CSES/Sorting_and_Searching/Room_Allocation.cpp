
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

int roomid[200005];
int main() {
	yccc;
	int n;
	cin >> n;
	vector<tuple<int, int, int>> epts; // day, entry, pid
	set<int> rooms;
	for(int i = 0; i < n; i++){
		int st, ed;
		cin >> st >> ed;
		epts.emplace_back(st, 0, i);
		epts.emplace_back(ed, 1, i);
		rooms.emplace(i+1);
	}

	sort(al(epts));
	int i = 0;
	int ans = 0;
	int cur = 0;
	while(i < epts.size())
	{
		int today = get<0>(epts[i]);
		
		while(i < epts.size() && get<0>(epts[i]) == today)
		{
			if(get<1>(epts[i]) == 0){
				cur++;
				roomid[get<2>(epts[i])] = *rooms.begin();
				rooms.erase(rooms.begin());
			}
			else
			{
				cur--;
				rooms.emplace(roomid[get<2>(epts[i])]);
			}
			ans = max(ans, cur);
			i++;
		}
	}
	cout << ans << endl;
	for(int i = 0; i < n; i++){
		cout << roomid[i] << (i == n-1 ? '\n' : ' ');
	}




	return 0;
}
