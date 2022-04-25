#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define REP(i,n) for(int i = 0; i < n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define INF 1000005
template<typename T>
using vec = vector<T>;
using pii = pair<int, int>;
using ll = long long;
vec<vec<int>> table;
vec<vec<pii>> adjG;
struct Dsj{
	vec<int> pa;
	int n;
	void Build(int n){
		pa.resize(n);
		this->n = n;
		for (int i = 0; i < n; i++)
			pa[i] = i;
	}
	int getSet(int a){
		if(pa[a] == a)
			return a;
		return pa[a] = getSet(pa[a]);
	}
	bool sameSet(int a, int b){
		return getSet(a) == getSet(b);
	}
	void merge(int a, int b){
		if(sameSet(a, b))
			return;
		pa[a] = getSet(b);
	}
};
int nvertex;
int r, c;
void buildG()
{
	int cur_u = -1, cur_d = -1, up, down;
	int len = 0;
	int limiti, limitj;
	for (int round = 0; round < 2; round++)
	{
		if (round == 0)
			limiti = r, limitj = c;
		else
			limiti = c, limitj = r;

		for (int i = -1; i < limiti; i++)
		{
			cur_u = cur_d = -1;
			len = 0;
			for (int j = 0; j < limitj; j++)
			{
				up = down = -1;
				if (round == 0)
				{
					if (i >= 0)
						up = table[i][j];
					if (i + 1 < limiti)
						down = table[i + 1][j];
				}
				else
				{
					if (i >= 0)
						up = table[j][i];
					if (i + 1 < limiti)
						down = table[j][i + 1];
				}
				if (up != -1 && down != -1)
				{
					if (cur_u != -1)
						adjG[cur_u].eb(len, up), adjG[cur_u].eb(len, down),
						adjG[up].eb(len, cur_u), adjG[down].eb(len, cur_u);
					if (cur_d != -1)
						adjG[cur_d].eb(len, up), adjG[cur_d].eb(len, down),
						adjG[up].eb(len, cur_d), adjG[down].eb(len, cur_d);
					len = 0;
					cur_u = up;
					cur_d = down;
				}
				else if (up != -1)
				{
					if (cur_u != -1)
						adjG[cur_u].eb(len, up), adjG[up].eb(len, cur_u);
					if (cur_d != -1)
						adjG[cur_d].eb(len, up), adjG[up].eb(len, cur_d);
					len = 0;
					cur_u = up;
					cur_d = -1;
				}
				else if (down != -1)
				{
					if (cur_u != -1)
						adjG[cur_u].eb(len, down), adjG[down].eb(len, cur_u);
					if (cur_d != -1)
						adjG[cur_d].eb(len, down), adjG[down].eb(len, cur_d);
					len = 0;
					cur_u = -1;
					cur_d = down;
				}
				else
					len++;
			}
		}
	}
}

pair<pair<ll, int>, int> MST(){
	vec<bool> visited(nvertex, false);
//	cout << "we have " << nvertex << " in MST\n";
	ll ans = 0;
	int edgenum = 0;
	int partition = 0;
	//Dsj DsjT;
	//DsjT.Build(nvertex);
	for (int i = 0; i < nvertex; i++)
	{
		if(visited[i])
			continue;
		partition++;
		ll localans = 0;
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		pq.emplace(0, i);
		while(!pq.empty()) {
			int len, u;
			tie(len, u) = pq.top();
			pq.pop();
			if(visited[u])
				continue;
			visited[u] = true;
//			DsjT.merge(i, u);
			ans += len;
			if(len != 0)
				edgenum++;
			for (auto &edge : adjG[u])
			{
				if(!visited[edge.S])
					pq.emplace(edge.F, edge.S);
			}
		}
		ans+=localans;
	}
	return {{ans, edgenum}, partition};
}

int main()
{
	int cnt = 1;

	while(cin >> r >> c){
		if(!r && !c)
			break;
		if(cnt != 1)
			cout << endl;
		table.clear();
		table.resize(r, vec<int>(c));
		int idx = 0;
		char ch;
		REP(i, r){
			REP(j, c){
				cin >> ch;
				if(ch == '#'){
					table[i][j] = idx++;
				}
				else{
					table[i][j] = -1;
				}
			}
		}

  /*
		REP(i, r){
			REP(j, c){
				if(table[i][j] >= 0)
					cout << " ";
				cout << table[i][j] << " ";
			}
			cout << endl;
		}
		*/
		nvertex = idx;
		adjG.clear();
		adjG.resize(nvertex);
		buildG();
		/*
		int curidx= 0;
		for (auto u : adjG)
		{
			cout << curidx++ << " nei: ";
			for (auto v : u)
			{
				cout << v.S << "'s len= " << v.F << ", ";
			}
			cout << endl;
		}
		*/
		pair<pair<ll,int>, int> ans = MST();
		cout << "City " << cnt++ << endl;

  
		if(ans.F.S == 0){
			if(ans.S == 1 || ans.S == 0)
				cout << "No bridges are needed.\n";
			else
				cout << "No bridges are possible.\n";
		}
		else
		{
			cout << ans.F.S;
			if(ans.F.S == 1)
				cout << " bridge";
			else
				cout << " bridges";
			cout << " of total length " << ans.F.F << endl;
		}
		if (ans.S != 1 && ans.S != 0)
			cout << ans.S << " disconnected groups\n";
	}
	return 0;
}
