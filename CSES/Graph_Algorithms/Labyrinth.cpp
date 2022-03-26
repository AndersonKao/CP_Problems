// AC 2022-03-01 08:37:34
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
using PII = pair<int, int>;
vector<vector<char>> grid;
PII dir[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
char cdir[4] = {'U', 'D', 'L', 'R'};
vector<vector<bool>> vis;
vector<vector<char>> path;
bool sol = false;
PII operator+(PII a, PII b){
    return PII(a.x + b.x, a.y + b.y);
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    grid.resize(N + 2, vector<char>(M + 2, '#'));
    vis.resize(N + 2, vector<bool>(M + 2, false));
    path.resize(N + 2, vector<char>(M + 2, ' '));

    PII st, ed;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++){
            cin >> grid[i][j];
            if(grid[i][j] == 'A')
                st.x = i, st.y = j;
            else if(grid[i][j] == 'B')
                ed.x = i, ed.y = j;
        }
    queue<PII> Q;
    Q.emplace(st);
    vis[st.x][st.y] = true;
    while(Q.size()){
        PII pos = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++){
            PII npos(pos.x + dir[i].x, pos.y + dir[i].y);
            if(grid[npos.x][npos.y] != '#' && !vis[npos.x][npos.y]){
                Q.emplace(npos);
                vis[npos.x][npos.y] = true;
                path[npos.x][npos.y] = cdir[i];
            }
        }
    }
    if (!vis[ed.x][ed.y])
    {
        cout << "NO\n";
    }
    else
    {
        stack<char> ANS;
        PII cur = ed;

        while (cur != st)
        {
            ANS.emplace(path[cur.x][cur.y]);
            if (ANS.top() == 'U')
                cur = cur + dir[1];
            else if (ANS.top() == 'D')
                cur = cur + dir[0];
            else if (ANS.top() == 'L')
                cur = cur + dir[3];
            else if (ANS.top() == 'R')
                cur = cur + dir[2];
        }
        cout << "YES\n" << ANS.size() << "\n";
        while (ANS.size())
        {
            cout << ANS.top();
            ANS.pop();
        }
        cout << endl;
    }

    return 0;
}