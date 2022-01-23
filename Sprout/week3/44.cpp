// AC 2019/12/13 23:38:37
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
typedef struct
{
    int x, y;
} Coord;
char table[102][102];
bool efind = false;
Coord dir[4] = {{1,0},{-1,0},{0,1},{0,-1}};
void flood_fill(queue<Coord>* a,int x,int y){
    table[x][y] = '#';
    for(int i=0;i<4;i++){
        int new_x = x + dir[i].x, new_y = y + dir[i].y;
        if(table[new_x][new_y] == '@')
        {
            efind = true;
            break;
        }
        else if(table[new_x][new_y] == '.')
        {
            table[new_x][new_y] = '#';
            (*a).push({new_x,new_y});
        }
    }
}
int main()
{
    int row;
    while (cin >> row)
    {
        queue<Coord>* todo = new queue<Coord>;
        if (row == 0)
            break;
        for (int i = 0; i < row; i++)
            scanf("%s", table[i]);
        efind = false;
        int len = strlen(table[0]);
        Coord start;
        start.x = 0;
        start.y = 0;
        for (int i = 1; i < row; i++)
        {
            for (int j = 1; j < len; j++)
                if (table[i][j] == 'K')
                {
                    start.x = i;
                    start.y = j;
                    break;
                }
            if (start.x)
                break;
        }
        
        flood_fill(todo,start.x,start.y);
        int count = 1;
        while(!efind){
            int limit = (*todo).size();
            for(int i=0;i<limit;i++){
                    //Node nex = todo.front();
                    flood_fill(todo,(*todo).front().x,(*todo).front().y);
                    (*todo).pop();
                    //cout << "lets go to x" << nex.x << " y:" << nex.y << "\n";

            }
            count++;
            if((*todo).empty() && !efind){
                cout << "= =\"\n";
                break;
            }
        }
        if(efind)
            cout << count << "\n";
        delete(todo);
    }
    return 0;
}

void dfs(int start){
    for( four direction)
    {

        dfs(start, i);
    }
}
/*

*/
/*
6
########
#..1K12#
#.#2##3#
#.#3#.4#
#..456@#
########
########
#..1K12#
#......#
#......#
#......#
########
*/
/*
5  
########
#K######
########
###...@#
########
= ="
6
######
#...##
#.#..#
#K#.@#
######
######
7
3
####
#K@#
####
1
6
########
#...K#.#
#.#.##.#
#.#.#..#
#.....@#
########
*/