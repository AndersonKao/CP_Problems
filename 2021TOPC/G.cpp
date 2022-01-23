#include <bits/stdc++.h>
using namespace std;
 

int T, N;
vector<vector<pair<int, int>>> G;
int deg[200005] = {0};
long long seq[200005] = {0};
bool visited[200005];
set<pair<int, int>> S;
long long ans = 0;
long long fito(int K){
    if(K <= 0)
        return 0;
    if(seq[K] != 0)
        return seq[K];
    return seq[K] = K + seq[K-1];
}
void DFS(int v, int len, int pre, int start){
    visited[v] = true;
    bool endpoint = true;
    for(auto u: G[v])
    {
        if(visited[u.first])
            continue;
        endpoint = false;
        if(u.second > pre)
        {
            DFS(u.first, len+1, u.second, start);
        }else{
           //printf("From %d to %d\n", v, u.first);
            //printf("reodd ans = %d\n", ans);
            if(S.find(pair<int, int>(start, v)) != S.end())
            {
                ans += fito(len-1);
                S.emplace(start,v);
            }
            //printf("renew ans = %d\n", ans);
            DFS(u.first, 1, u.second, v);
        }
    }
    if(endpoint){
            if(S.find(pair<int, int>(start,v)) != S.end())
            {
                ans += fito(len-1);
                S.emplace(start, v);
            }
    }
    
}

int main(){
    scanf("%d", &N);
    if(N == 1)
    {
        printf("0\n");
        return 0;
    }else if(N == 2){
        printf("1\n");
        return 0;
    }
    //printf("%d\n", N);
    G.resize(N+1);
    ans = (N-1) * 2;
    int a, b, c;

    seq[0] = 0;
    seq[1] = 1;

    
    for(int t = 0; t < N-1; t++){
        scanf("%d %d %d", &a, &b, &c);
        G[a].emplace_back(b, c);
        G[b].emplace_back(a, c);
        deg[a]++;
        deg[b]++;
        
    }
    queue<int> todo;
    for(int i = 1; i <= N; i++){
        if(deg[i] == 1)
            todo.push(i);
    }
//    printf("going from %d\n", todo.front());
    while(todo.size()){
        std::fill(visited, visited + N + 1, false);
        DFS(todo.front(), 0, 0, todo.front());
        todo.pop();

    }
//    printf("going from %d\n", todo.front());
    printf("%ld\n", ans);

    return 0;
}


/*
6
1 2 2
2 3 1
3 5 7
5 6 4
6 4 3
*/