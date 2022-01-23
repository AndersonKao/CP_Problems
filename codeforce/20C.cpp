#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <queue>
using namespace std;
#define LL long long int
#define INF INT64_MAX
#define edge pair<LL, int> // first for dis, second for index


vector<vector<edge>> G;
vector<LL> shortestpath;
vector<int> predecessor;
priority_queue<edge> pq;
int main(){
    int N, M;
    cin >> N >> M;
    G.resize(N + 1);
    shortestpath.resize(N + 1, INF);
    predecessor.resize(N + 1, -1);
    for(int i = 0; i < M; i++){
        int st, end, len;
        cin >> st >> end >> len;
        G[st].push_back(edge(len, end));
        G[end].push_back(edge(len, st));
    }

    pq.push(edge(shortestpath[0] = 0, 0));
    while(pq.size()){
        int path, index;
        tie(path, index) = pq.top();
        pq.pop();

        if(path > shortestpath[index]) continue;
        for(auto it: G[index]){
            if(shortestpath[it.second] <= path + it.first)
                continue;
            shortestpath[it.second] = path + it.first;
            predecessor[it.second] = index;
            pq.push(edge(shortestpath[it.second], it.second));
        }
    }

    return 0;
}