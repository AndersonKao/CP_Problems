// AC 2019/12/10 14:03:28
#include <iostream>
#include <queue>
using namespace std;
char table[1005][1005];
struct flo{
    int x, y;
};
int ans;
queue<flo> k;
flo direct[4] = {{1,0},{-1,0},{0,1},{0,-1}};
void dp(int x,int y){
    if(table[x][y] == '#')
        return;
    else
        table[x][y] = '#';
    // cout << "going to x:" << x << "y:" << y << endl;
    for(int i=0;i<4;i++){
        if(table[x+direct[i].x][y + direct[i].y] == '.'){
           k.push({x+direct[i].x,y+direct[i].y});
        }
    }
    while(!k.empty()){
        flo tmp = k.front();
        k.pop();
        dp(tmp.x,tmp.y);
    }
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int row, col;
        ans = 0;
        cin >> row >> col;
        for (int i = 0; i <= row + 1; i++)
            for (int j = 0; j <= col + 1; j++)
                if (i >= 1 && i <= row && j >= 1 && j <= col)
                    cin >> table[i][j];
                else
                    table[i][j] = '#';
        while(!k.empty())
            k.pop();
        for(int i=1;i<=row;i++)
            for(int j=1;j<=col;j++){
                if(table[i][j] == '.'){
                    // cout << "let's go" << i << " " << j << "\n";
                    dp(i,j);
                    ans++;
                }
                
            }
        cout << ans << "\n";
    }
    return 0;
}
/*
8 8
#.##.#.#
.##.##.#
#.#..###
#.###...
#.##..#.
#.###...
...#####
.##.##.#
*/