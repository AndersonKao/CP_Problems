#include <iostream>
#include <vector>
#include <queue>

using namespace std;
const int SIZE = 100;

vector<int> child[SIZE];

void dfs(int node){
	cout << node << " ";
	for(size_t i = 0; i < child[node].size(); ++i)
		dfs(child[node][i]);
}

void bfs(int root){
	queue<int> queue;
	while(!queue.empty()) queue.pop();
	queue.push(root);

	while(!queue.empty()){
		int tmp = queue.front();
		queue.pop();
		cout << tmp << " ";
		for(size_t i = 0; i < child[tmp].size(); ++i)
			queue.push(child[tmp][i]);
	}
}

int main(){
	// build the tree
	child[1].push_back(2);
	child[1].push_back(3);
	child[2].push_back(4);
	child[3].push_back(5);
	child[3].push_back(6);
	
	// DFS
	cout << "DFS: ";
	dfs(1);
	cout << endl;

	// BFS
	cout << "BFS: ";
	bfs(1);
	cout << endl;
	
	return 0;
}

