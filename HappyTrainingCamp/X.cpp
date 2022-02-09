#include <bits/stdc++.h>
using namespace std;

int T;

vector<string> table;
int rowLen, colLen;
int direc[8][2] = {
    {1, 1},
    {1, 0},
    {1, -1},
    {0, 1},
    {0, -1},
    {-1, 1},
    {-1, 0},
    {-1, -1}
};

bool visited[100][100];
int BFS(int r, int c){
    if(r < 0 || r >= rowLen || c < 0 || c >= colLen || table[r][c] == 'L'){
        return 0;
    }
    queue<pair<int, int>> Q;
    for (int i = 0; i < rowLen; i++)
        for (int j = 0; j < colLen; j++)
            visited[i][j] = false;
    // pitfall
    //memset(visited, false, sizeof(visited));
    // here ?
    visited[r][c] = true;
    Q.emplace(r, c);
    int ans = 1;
    
    while(!Q.empty()){
        int u, v;
        u = Q.front().first;
        v = Q.front().second;
       // cout << "choosing " << u << ", " << v << endl;
        // here?
        // visited[u][v] = true;
        Q.pop();
        int u2, v2;
        for (int i = 0; i < 8; i++){
            u2 = u + direc[i][0];
            v2 = v + direc[i][1];
      //      cout << "testing " << u2 << ", " << v2 << endl;
            if(u2 < 0 || u2 >= rowLen || v2 < 0 || v2 >= colLen || visited[u2][v2])
                continue;
            if(table[u2][v2] == 'W'){
        //        cout << "getcha\n";
                Q.emplace(u2, v2);
                // here ?
                visited[u2][v2] = true;
                ans++;
            }
        }
    }
    return ans;
}

void solve(){
    string str;
    rowLen = colLen = 0;
    while(true){
        getline(cin, str);
        //cout << "tell me shat you get " << str << endl;
        if(isdigit(str[0]))
            break;
        colLen = str.length();
        table.emplace_back(str);
    }
 //   for (auto p: table)
  //     cout << p << endl;
    rowLen = table.size();
    colLen = table[0].length();
//  cout << "rowlen, collen = " << rowLen << " " << colLen << "\n";
    int start_x, start_y;

    while(str != ""){
        stringstream ss(str);
        ss >> start_x >> start_y;
        start_x--;
        start_y--;
//            cout << "start at " << start_x << " " << start_y << endl;
        cout << BFS(start_x, start_y) << endl;
        str = "";
        getline(cin, str);
        //cout << "tell me shat you get " << str << endl;
    };
}

int main(){
    while(scanf("%d\n", &T) != EOF){
        while(T--){
            table.clear();
            solve();
            if(T != 0)
                cout << endl;
        }
    }

    return 0;
}