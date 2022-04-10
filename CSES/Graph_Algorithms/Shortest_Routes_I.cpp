#include <iostream>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

typedef ll long long;
using ll = long long;
const ll MAX = 1000000000000000;
using edge = pair<int, int>;
using pii = pair<int, int>;

template<typename T>
using vec = vector<T>;

vector<vector<edge>> G;
vector<ll>  dis;
int main(){

	int n, m;
	cin >> n >> m;
	G.resize(n);
	dis.resize(n, MAX);
	for(int i = 0; i < m; i++){
		int a, b, c;
		cin >> a >> b >> c;	
		a--, b--;
//		G[a].push_back(make_pair(c, b));
		G[a].emplace_back(c, b);
	}
	
	dis[0] = 0;
	priority_queue<pair<ll, int>, vector<pair<ll ,int>>, greater<pair<ll,int>>> pq;
	// store first = distance from 0, second = vertex index
//	pq.push(pair<int ,int>(dis[0], 0));
	pq.emplace(dis[0], 0);

	while(!pq.empty()){
		pair<ll, int> top = pq.top();
		pq.pop();
		int u = top.second;
		ll dis_u = top.first;
		if(dis_u > dis[u]){
			continue;
		}
		for(pair<int,int> neighbor: G[u]){
			int v = neighbor.second;
			int w = neighbor.first;
			if(dis[v] > dis[u] + w){
				dis[v] = dis[u] + w;	
//				pq.push(pair<int, int>(dis[v], v));
//				pq.push(make_pair(dis[v], v));
				pq.emplace(dis[v], v);
			} 
		}
	}
	for(int i = 0; i < (int)dis.size(); i++){
		cout << dis[i];
		if(i == (int)dis.size() - 1)
			cout << endl;
		else
			cout << " ";
	}


	return 0;
}
