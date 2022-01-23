#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int N, M, a, b;
struct Node{
    vector<int> neighbor;
    int deg;
    int Group;
    Node(){
        deg = Group = 0;
    }
};
vector<Node> Graph;
int GroupDegAns[50000] = {0};
int NodeGroup = 0;
void DFS(int N, int groupIndex){
    queue<int> todo;
    todo.push(N);
    Graph[N].Group = groupIndex;
    int node;
    while(!todo.empty()){
        node = todo.front();
        todo.pop();
        if(Graph[node].deg & 1){
            GroupDegAns[groupIndex]++;
        }
        // Graph[node].Group = groupIndex;
        for(auto it: Graph[node].neighbor){
            if(Graph[it].Group == 0){
                Graph[it].Group = groupIndex;
                todo.push(it);
            }
        }
    }
}
int main(){
    cin >> N >> M;
    Graph.resize(N+40);

    while(M--){
        cin >> a >> b;
        Graph[a].neighbor.push_back(b);
        Graph[a].deg++;
        Graph[b].neighbor.push_back(a);
        Graph[b].deg++;
    }
    for(int i = 1; i <= N; i++){
        if(Graph[i].Group == 0){
            NodeGroup++;
            DFS(i, NodeGroup);
        }
    }
    
    int ans = 0;
    for(int i = 1; i <= NodeGroup; i++){
        ans += max(1, GroupDegAns[i] / 2);
    }
    ans++;
    cout << ans << endl;
    return 0;
}