#include <bits/stdc++.h>
using namespace std;
int g[105][105];
int dp[105][105], inq[105][105];
int main() {
    //freopen("in.txt","r+t",stdin);
    //freopen("out2.txt","w+t",stdout);
    int n, m;
    int i, j, k;
    int x, y, cost;
    int cases = 0;
    while(scanf("%d %d", &n, &m) == 2 && n) {
        memset(inq, 0, sizeof(inq));
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= n; j++) {
                g[i][j] = 0xfffffff;
            }
        }
        for(i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            g[x][y] = 1;
        }
        for(k = 1; k <= n; k++)
            for(i = 1; i <= n; i++)
                for(j = 1; j <= n; j++)
                    g[i][j] = min(g[i][j], g[i][k]+g[k][j]);

        for(i = 1; i <= n; i++)
            for(j = 1; j <= n; j++)
                dp[i][j] = 0xfffffff;
        queue<int> X, Y;
        X.push(1), Y.push(1);
        dp[1][1] = 1;
        while(!X.empty()) {
            x = X.front(), X.pop();
            y = Y.front(), Y.pop();
            inq[x][y] = 0;
            printf("%2d %2d %d\n", x, y, dp[x][y]);
            for(i = 1; i <= n; i++) {
                cost = (x != i && y != i);
                if(g[x][i] == 1) {
                    if(dp[i][y] > dp[x][y]+cost) {
                        dp[i][y] = dp[x][y]+cost;
                        if(inq[i][y] == 0) {
                            inq[i][y] = 1;
                            X.push(i), Y.push(y);
                        }
                    }
                }
                if(g[i][y] == 1) {
                    if(dp[x][i] > dp[x][y]+cost) {
                        dp[x][i] = dp[x][y]+cost;
                        if(inq[x][i] == 0) {
                            inq[x][i] = 1;
                            X.push(x), Y.push(i);
                        }
                    }
                }
            }
            if(x != y) {
                if(dp[y][x] > dp[x][y] + g[x][y]-1) {
                    dp[y][x] = dp[x][y] + g[x][y]-1;
                    if(inq[y][x] == 0) {
                        inq[y][x] = 1;
                        X.push(y), Y.push(x);
                    }
                }
            }
            cout << "    ";
            for (j = 1; j <= n; j++)
                cout << setw(3) << j << " ";
            cout << endl;
            for (i = 1; i <= n; i++)
            {
                cout << setw(3) << i << " ";
                for (j = 1; j <= n; j++)
                {
                    if(dp[i][j] == 0xfffffff)
                        cout << "    ";
                    else
                    cout << setw(3) << dp[i][j] << " ";
                }
                cout << endl;
            }
        }
        printf("Network %d\n", ++cases);
        if(dp[2][2] == 0xfffffff)
            puts("Impossible");
        else
            printf("Minimum number of nodes = %d\n", dp[2][2]);
        puts("");
    }
    return 0;
}
/*
11 46
2 4
3 11
10 4
11 11
3 10
9 9
9 7
10 1
6 8
4 9
11 1
6 2
3 9
1 11
5 3
9 6
8 1
3 6
6 1
4 6
4 10
4 4
3 3
7 10
7 6
1 9
7 9
1 8
9 10
4 5
5 2
10 10
1 3
8 9
1 4
5 4
1 7
2 11
5 5
5 11
11 8
10 2
8 4
6 3
9 3
7 1
*/
