#include <iostream>
#include <cstring>
#include <utility>
#include <queue>
using namespace std;
//int Rnum, Ynum, Bnum, Onum, Gnum, Pnum, Dnum;
char map[1002][1002];
bool Rvisited[1002][1002];
bool Bvisited[1002][1002];
bool Yvisited[1002][1002];

// E means empty
int dir[8][2] = {{1,0},{-1,0},{0,1},{0,-1}, {1,1}, {1, -1}, {-1, 1}, {-1,-1}};
char colorAdd(char color1, char color2);

struct flood{
    int x, y;
    int level;
    char color;
};

int main(){
    int T;
    cin >> T;
    int Width;
    while(T--){

        queue<pair<int, int>> Q;
        queue<int> roundQ;
        queue<char> colorQ;
        //queue<flood> generalQ;

        int x, y;
        char color;
        // init
        memset(map, 'E', sizeof(map));
        memset(Rvisited, 0, sizeof(Rvisited));
        memset(Yvisited, 0, sizeof(Yvisited));
        memset(Bvisited, 0, sizeof(Bvisited));
        cin >> Width;
        // create obstacle around map;
        for (int i = 0; i <= Width + 1; i++){
            Rvisited[i][0] = Yvisited[i][0] = Bvisited[i][0] = true;
            Rvisited[i][Width + 1] = Yvisited[i][Width+1] = Bvisited[i][Width + 1] = 'T';
            if (i == 0 || i == Width+1){
                for (int j = 0; j <= Width; j++)
                    Rvisited[i][j] = Yvisited[i][j] = Bvisited[i][j] = true;
            }
        }
        for (int i = 0; i < 3; i++)
        {
            cin >> color >> x >> y;
            x++;
            y++;
            map[x][y] = color;
            switch (color)
            {
            case 'R':
                Rvisited[x][y] = true;
                break;
            case 'Y':
                Yvisited[x][y] = true;
                break;
            case 'B':
                Bvisited[x][y] = true;
                break;
            default:
                break;
            }
            Q.push(pair<int, int>(x , y));
            roundQ.push(0);
            colorQ.push(color);
            //Q.emplace(x, y);
        }

        char asking;
        int ANS = 0, Cur = 0;
        int round = 0;
        cin >> asking;
        if(asking == 'Y' || asking == 'R' || asking == 'B')
            Cur = 1;
        while(!Q.empty()){
            while(!Q.empty() && roundQ.front() == round){
                x = Q.front().first;
                y = Q.front().second;
                char dye = colorQ.front();
                colorQ.pop();
                Q.pop();
                roundQ.pop();

                for (int i = 0; i < 8; i++){
                    int x2 = x + dir[i][0];
                    int y2 = y + dir[i][1];
                    if(dye == 'R'){
                        if(Rvisited[x2][y2])
                        continue;
                        Rvisited[x2][y2] = true;
                    }
                    else if(dye == 'Y'){
                        if(Yvisited[x2][y2])
                        continue;
                        Yvisited[x2][y2] = true;
                    }
                    else if(dye == 'B'){
                        if(Bvisited[x2][y2])
                        continue;
                        Bvisited[x2][y2] = true;
                    } 
                    if(map[x2][y2] == asking)
                        Cur--;
                    map[x2][y2] = colorAdd(dye, map[x2][y2]);
                    if(map[x2][y2] == asking)
                        Cur++;
                    Q.emplace(x2, y2);
                        roundQ.push(round + 1);
                        colorQ.push(dye);
                }
            }
            ANS = max(ANS, Cur);
            round++;
            /* debug
            for (int i = 1; i <= Width; i++){
                for (int j = 1; j <= Width; j++)
                cout << map[i][j] << " ";
                cout << endl;
            }
            cout << asking << " ANS: " << ANS << " Cur: " << Cur << endl;
            */
        }
        
        cout << ANS << endl;
    }
}
char colorAdd(char color1, char color2){
    if(color1 == 'T' || color2 == 'T')
        return 'T';
    if(color1 == 'E' || color2 == 'E')
        return (color1 == 'E' ? color2 : color1);
    switch (color1)
    {
    case 'Y':
        switch (color2)
        {
        case 'R':
            return 'O';
            break;
        case 'B':
            return 'G';
            break;
        case 'Y':
            return 'Y';
            break;
        default:
            return 'D';
            break;
        }
        break;
    case 'B':
        switch (color2)
        {
        case 'R':
            return 'P';
            break;
        case 'B':
            return 'B';
            break;
        case 'Y':
            return 'G';
            break;
        default:
            return 'D';
            break;
        }
        break;
    case 'R':
        switch (color2)
        {
        case 'R':
            return 'R';
            break;
        case 'B':
            return 'P';
            break;
        case 'Y':
            return 'O';
            break;
        default:
            return 'D';
            break;
        }
        break;
    default:
        if(color1 != color2)
            return 'D';
        return color1;
        break;
    }
}