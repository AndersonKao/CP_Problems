// AC 2019-10-21 13:44:11
#include <assert.h>
#include <iostream>
#include <map>
#include <vector>
#define _for(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
const int Gsize = 5;
struct Vector_Self
{
    int x, y;
};

bool youdonthavezero(string k, char ch) //用於判斷是否已經輸入0結尾
{
    _for(i, 0, k.size())
    {
        if (k[i] == ch)
            return false;
    }
    return true;
}
bool shouldiprint = true; //判斷不合法交換則不輸出變換後的圖形
bool areyoufirsttime = true;
int ptimers = 1;
bool areyoutrue(int mx, int my, int x, int y); //判斷是否有不合法交換
int main()
{
    //ios::sync_with_stdio(0);
    //cin.tie(0);

    char table[Gsize][Gsize]; //儲存用的陣列
    string line;              //輸入用
    bool flag = true;         //用於判斷是否該結束
    Vector_Self theonlyone;   //紀錄空白的字元座標([][])
    while (flag)
    {
        //line.erase();
        _for(i, 0, Gsize)
        {
            getline(cin, line);
            if (line == "Z") //判斷是否只輸入Z，需結束程式
            {
                flag = false;
                break;
            }
            if (flag) //假如前面只輸入Z，不執行
            {
                _for(k, 0, Gsize)
                {
                    table[i][k] = line[k];
                    if (line[k] == ' ') //判斷' '
                    {
                        theonlyone.x = k;
                        theonlyone.y = i;
                    }
                    //cout << table[i][k].thing;
                }
                //cout << endl;
            }
        }
        if (!flag) //假如前面只輸入Z，跳出
            break;
        string fuker; //輸入字串用
        line = "";
        //cout << "Entering...";
        while (youdonthavezero(line, '0')) //判斷是否含有0，有則不執行
        {
            getline(cin, fuker);
            line = line + fuker;
            fuker = "";
        }
        //cout << "youentered: " << line << endl;
        int size = line.size();
        _for(i, 0, size) //進字串判斷，一個一個交換位置
        {
            //cout << "empyt at" << theonlyone.x << "," << theonlyone.y << endl;
            int movingx, movingy;
            if (line[i] == 'A')
            {
                movingx = 0;
                movingy = -1;
                if (areyoutrue(movingx, movingy, theonlyone.x, theonlyone.y)) //判斷是否有不合法交換
                {
                    //cout << "movingA" << endl;

                    swap(table[theonlyone.y][theonlyone.x], table[theonlyone.y + movingy][theonlyone.x + movingx]); //與空格交換
                    //更新空格座標
                    theonlyone.y = theonlyone.y + movingy;
                    theonlyone.x = theonlyone.x + movingx;
                }
                else
                    break;
            }
            else if (line[i] == 'B')
            {
                movingx = 0;
                movingy = 1;
                if (areyoutrue(movingx, movingy, theonlyone.x, theonlyone.y))
                {
                    //cout << "movingB" << endl;

                    swap(table[theonlyone.y][theonlyone.x], table[theonlyone.y + movingy][theonlyone.x + movingx]);
                    theonlyone.y = theonlyone.y + movingy;
                    theonlyone.x = theonlyone.x + movingx;
                }
                else
                    break;
            }
            else if (line[i] == 'L')
            {
                movingx = -1;
                movingy = 0;
                if (areyoutrue(movingx, movingy, theonlyone.x, theonlyone.y))
                {
                    //cout << "movingL" << endl;

                    swap(table[theonlyone.y][theonlyone.x], table[theonlyone.y + movingy][theonlyone.x + movingx]);
                    theonlyone.y = theonlyone.y + movingy;
                    theonlyone.x = theonlyone.x + movingx;
                }
                else
                    break;
            }
            else if (line[i] == 'R')
            {
                movingx = 1;
                movingy = 0;
                if (areyoutrue(movingx, movingy, theonlyone.x, theonlyone.y))
                {
                    //cout << "movingR" << endl;

                    swap(table[theonlyone.y][theonlyone.x], table[theonlyone.y + movingy][theonlyone.x + movingx]);
                    theonlyone.y = theonlyone.y + movingy;
                    theonlyone.x = theonlyone.x + movingx;
                }
                else
                    break;
            }
        }

        if (shouldiprint)
        {
            if (areyoufirsttime) //Presentation code
            {
                areyoufirsttime = !areyoufirsttime;
            }
            else
            {
                cout << '\n';
            }
            cout << "Puzzle #" << ptimers++ << ":\n";
            _for(i, 0, Gsize)
            {
                _for(k, 0, Gsize)
                {
                    cout << table[i][k];
                    if(k<Gsize-1)
                        cout << ' ';
                }
                cout << '\n';
            }
        }

        shouldiprint = true;
        line = "";
    }

    return 0;
}
bool areyoutrue(int mx, int my, int x, int y)
{
    //判定合法交換
    if ((x + mx) >= Gsize || (x + mx) < 0)
    {

        if (areyoufirsttime) //Presentation code
        {
            areyoufirsttime = !areyoufirsttime;
        }
        else
        {
            cout << '\n';
        }
        shouldiprint = false;
        //cout << "x:" << x + mx << endl;
        cout << "Puzzle #" << ptimers++ << ":\n";
        cout << "This puzzle has no final configuration.\n";

        return false;
    }

    if ((y + my) >= Gsize || (y + my) < 0)
    {
        if (areyoufirsttime) //Presentation code
        {
            areyoufirsttime = !areyoufirsttime;
        }
        else
        {
            cout << '\n';
        }
        shouldiprint = false;
        //cout << "y:" << y + my << endl;
        cout << "Puzzle #" << ptimers++ << ":\n";
        cout << "This puzzle has no final configuration.\n";
        return false;
    }
    return true;
}