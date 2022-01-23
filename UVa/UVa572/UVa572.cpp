#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int direc[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
char table[102][102];
void flood_fill(int sr, int sc){ // source row, source column
    queue<pair<int , int>> Q;
    Q.emplace(sr, sc);
    table[sr][sc] = '*';
    
    while (Q.size() || !Q.empty())
    {
        int r = Q.front().first;
        int c = Q.front().second;
        Q.pop();
        for (int i = 0; i < 8; i++){
            int kr = r + direc[i][0];
            int kc = c + direc[i][1];

            if(table[kr][kc] == '*')
                continue;
            table[kr][kc] = '*';
            Q.emplace(kr, kc);
        }
    }
}
/*
*******
*******
*******
**@*@**
*******
*@@****
*******
5 X 5 
0 ~ n-1, 0 ~ m -1
1 ~ n 0 ~ m
n + 2 by m + 2
0 ~ n+1, 0 ~ m + 2
*******
*****@*
***@*@*
**@**@*
*****@*
*@@**@*
*******
*/
int main()
{
    int rnum, cnum;
    while(cin >> rnum >> cnum){
        if(rnum == 0 && cnum == 0)
            break;
        // init
        memset(table, '*', sizeof(table));
        // input
        for (int i = 1; i <= rnum; i++){
            for (int j = 1; j <= cnum; j++){
                cin >> table[i][j];
            }
            getc(stdin);
        }
        /*
        **@**
        ***@@
        **@*@
        */
        int ANS = 0;
        // check
        for (int i = 1; i <= rnum; i++){
            for (int j = 1; j <= cnum; j++){
                if(table[i][j] == '*')
                    continue;
                // going to flood fill
                flood_fill(i, j);
                ANS++;
            }
        }
        
        cout << ANS << endl;
    }
    return 0;
}