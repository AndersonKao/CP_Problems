// AC
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//#define DB
map<string, int> M;
vector<vector<int>> Graph;
int dis[1005] = {0};
bool visited[1005] = {false};
vector<string> strs;
int main(){
    int N;
    cin >> N;
    Graph.resize(N * 4);
    string str[3];
    M.clear();
    for (int i = 0; i < N; i++){
        for (int j = 0; j < 3; j++){
            cin >> str[j];
            if(M.find(str[j]) == M.end()){
                int index = M.size();
                M[str[j]] = index;
               // M.insert(pair<string, int>(str[j], index));
                strs.push_back(str[j]);
            }
        }
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                if(j == k)
                    continue;
                Graph[M[str[j]]].emplace_back(M[str[k]]);
            }
        }
    }

#ifdef DB
    for (auto data: M){
        cout << data.first << ": " << data.second << endl;
    }
#endif
    sort(strs.begin(), strs.end());
    // Isenbaev not exist
    if(M.find("Isenbaev") == M.end()){
        for (int i = 0; i < strs.size(); i++){
            int index = M[strs[i]];
            cout << strs[i] << " undefined\n";
        }
        return 0;
    }
        // BFS;
    queue<int> Q;
    int source = M["Isenbaev"];
    visited[source] = true;
    Q.push(source);
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        for(auto v: Graph[u]){
            if(visited[v])
                continue;
            visited[v] = true;
            dis[v] = dis[u] + 1;
            Q.push(v);
        }
    }

    for (int i = 0; i < strs.size(); i++){
        int index = M[strs[i]];
        if(index != source && dis[index] == 0){
            cout << strs[i] << " undefined\n";
        }
        else
        cout << strs[i] << " " << dis[index] << endl;
    }

        return 0;
}



