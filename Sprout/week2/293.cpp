// AC 2019/12/05 11:22:41
#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
using namespace std;
#define INF 0x3f3f3f3f
#define MAXN 100005
vector<int> connect[MAXN];
int nodesize[MAXN];
int ans,balance_size,target,node_num;
int max(int a,int b)
{
	return a>b? a:b;
}
void _init(int num)
{
	for (int i = 0; i < num; i++)
		connect[i].clear();
	balance_size = INF;
}
void dfs(int u, int pa)
{
	nodesize[u] = 1;
	int max_son_size = 0;
	for (int i = 0; i < connect[u].size(); i++)
	{
		int v = connect[u][i];
		if (v != pa)
		{
			dfs(v, u);
			nodesize[u] += nodesize[v];
		}
	}
}
void find_omoi(int k,int pa){
	int max_son = 0;
	for(int i=0;i<connect[k].size();i++){
		
		int v = connect[k][i];
		if(v!=pa){

			find_omoi(v,k);
			max_son = max(max_son,nodesize[v]);
		}
	}
	max_son = max(max_son,node_num-nodesize[k]);
	if(max_son < balance_size ||(max_son == balance_size && k <ans)){
		ans = k;
		balance_size = max_son;
	}
}
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int target_a, target_b;
		cin >> node_num;
		_init(node_num);
		for (int i = 1; i < node_num; i++)
		{
			cin >> target_a >> target_b;
			connect[target_a].push_back(target_b);
			connect[target_b].push_back(target_a);
		}
		target = node_num/2;
		dfs(0, -1);
		find_omoi(0,-1);
		cout << ans << endl;
	}
	return 0;
}
