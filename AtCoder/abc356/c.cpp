
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

int ans = 0;
int N, M, K;
int cur[15] = {0};
int keys[105][15] = {0};
int num[105] = {0};
char result[105] = {0};

bool test()
{
	/*
	cout << "combinations: ";
	for(int i = 0; i < N; i++)
	{
		cout << cur[i] << " ";
	}
	cout << endl;
	*/
	for(int i = 0; i < M; i++){
		int reals = 0;
		for(int j = 0; j < num[i]; j++)
		{
			reals += cur[keys[i][j]];
		}
	//	cout << i << "-th reals = " << reals << endl;
		if( (reals >= K) != (result[i] == 'o') ){
	//		cout << (reals >= K)  << " but " << (result[i] == 'o') << endl;
			return false;
		}
	}
	return true;
}

void DFS(int depth)
{
	if(depth == N)
	{
		if(test())
		{
			ans++;
	//		cout << "OK!\n";
		}
		return;
	}
	DFS(depth+1);
	cur[depth] = 1;
	DFS(depth+1);
	cur[depth] = 0;
}


int main() {
	yccc;
	cin >> N >> M >> K;

	for(int i = 0; i < M; i++){
		cin >> num[i];
		for(int j = 0; j < num[i]; j++)
		{
			cin >> keys[i][j];
			keys[i][j]--;
		}
		cin >> result[i];
	}
	DFS(0);

	cout << ans << endl;

	return 0;
}
