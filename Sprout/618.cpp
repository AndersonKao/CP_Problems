// AC
#include <iostream>
#include <cstring>
using namespace std;

// map info
int map_size;
char map[20][20];

/* 根據現在的位置與接下來的方向指令，判斷下一步合不合法。
	（這個函式可用於 isArrived 裡） */
bool isValid(int current[], char dir);

/* 最終是否可以成功取得口罩 */
bool isArrived(int start[], int end[], char command[]);

/* Your code will be put here */

int main()
{

    char command[100];
    int start[2]; // position: (start[0], start[1])
    int end[2];

    // read map size
    cin >> map_size;

    // read map
    for (int i = 0; i < map_size; i++)
    {
        for (int j = 0; j < map_size; j++)
        {
            cin >> map[i][j];
        }
    }

    // read start and end position
    cin >> start[0] >> start[1];
    cin >> end[0] >> end[1];

    // read command
    cin >> command;

    if (isArrived(start, end, command))
        cout << "Get the mask";
    else
        cout << "Cry";
    return 0;
}
bool isValid(int current[], char dir){
    int movement[2];
    if(dir == 'R'){
        movement[0] = 0;
        movement[1] = 1;
    }else if(dir == 'L'){
        movement[0] = 0;
        movement[1] = -1;
    }else if(dir == 'D'){
        movement[0] = 1;
        movement[1] = 0;
    }else if(dir == 'U'){
        movement[0] = -1;
        movement[1] = 0;
    }
    int nextpos[2];
    nextpos[0] = current[0] + movement[0];
    nextpos[1] = current[1] + movement[1];
    
    if(map[nextpos[0]][nextpos[1]] == 'o'){
        return false;
    }
    current[0] += movement[0];
    current[1] += movement[1];
    return true;
}
bool isArrived(int start[], int end[], char command[]){
    int len = strlen(command);
    int place[2];
    place[0] = start[0];
    place[1] = start[1];
    for (int i = 0; i < len; i++){
        if(!isValid(place, command[i])){
            return false;
        }
        if(place[0] == end[0] && place[1] == end[1])
            return true;
    }
    return false;
}