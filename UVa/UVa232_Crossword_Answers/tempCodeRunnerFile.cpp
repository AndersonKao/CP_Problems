#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
//#define _for(i, a, b) for (int i = (a), i < (b), i++)
int counter = 1;
using namespace std;
void printc() { cout << counter << ". "; }

struct opening
{
    int r, c;
    int squen;
    bool down = false;
    bool across = false;
};

using namespace std;
#define MAXN 12

int main()
{

    
    int row, column;
    
    //while (true)
    //{
    int T = 0;
    while (cin >> row && row != 0)
    {   
        
        int OpenNum = 0;
        
        opening allo[100];
        cin >> column;
        if(T>0)
            cout << '\n';
        T++;
        char table[row][column + 1];
        for (int i = 0; i < row; i++)
        {
            scanf("%s", table[i]);
        }
        // for (int i = 0; i < row; i++)
        // {
        //     printf("%s\n", table[i]);
        //
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
            {
                if (table[i][j] == '*')
                    continue;
                bool chaneg = false;
                if (i > 0 && table[i-1][j] == '*')
                {
                    allo[OpenNum].r = i;
                    allo[OpenNum].c = j;
                    allo[OpenNum].down = true;
                    //allo[OpenNum].across = false;
                    allo[OpenNum].squen = OpenNum;
                    chaneg = true;
                }
                else if (i == 0)
                {
                    allo[OpenNum].r = i;
                    allo[OpenNum].c = j;
                   //allo[OpenNum].across = true;
                    allo[OpenNum].down = true;
                    allo[OpenNum].squen = OpenNum;
                    chaneg = true;
                }
                if (j > 0 && table[i][j-1] == '*')
                {
                    allo[OpenNum].r = i;
                    allo[OpenNum].c = j;
                    allo[OpenNum].across = true;
                    //allo[OpenNum].down = false;
                    allo[OpenNum].squen = OpenNum;
                    chaneg = true;
                }
                else if (j == 0)
                {
                    allo[OpenNum].r = i;
                    allo[OpenNum].c = j;
                    allo[OpenNum].across = true;
                    //allo[OpenNum].down = false;
                    allo[OpenNum].squen = OpenNum;
                    chaneg = true;
                }
                if (chaneg)
                    OpenNum++;
        }
        // for (int i = 0; i < OpenNum;i++)
        // {
        //     if(!allo[OpenNum].across)
        //         continue;
        //     else if(allo[OpenNum].across)
        //     {
        //         cout << allo[OpenNum].squen << '.';
        //         int i = 0;
        //         while(true)
        //         { 

        //             if(table[allo[OpenNum].r][allo[OpenNum].c] == '*')
        //                 break;
        //             cout << table[allo[OpenNum].r][allo[OpenNum].c + i];
        //         }
        //         cout << endl;
        //     }
        // }
            // for (int i = 0; i < OpenNum; i++)
            // {
            //     cout << allo[i].squen << '\n'
            //          << allo[i].r << " " << allo[i].c << " \n";
            //     if(allo[i].across)
            //         cout << "across\n";
            //     if(allo[i].down)
            //         cout << "down\n";
            // }
        cout << "puzzle #" << T << ":\n" << "Across\n";
        for (int i = 0; i < OpenNum;i++)
        {
            if(allo[i].across)
            {
                cout << "  "<< allo[i].squen + 1 <<'.' ;
                for (int j = allo[i].c;j<column;j++)
                {
                    if(table[allo[i].r][j] == '*')
                        break;
                    cout << table[allo[i].r][j];
                }
                cout << '\n';
            }
        }
        cout << "Down\n";
        for (int i = 0; i < OpenNum;i++)
        {
            if(allo[i].down)
            {
                cout << "  " << allo[i].squen + 1 << '.' ;
                for (int j = allo[i].r;j<row;j++)
                {
                    if(table[j][allo[i].c] == '*')
                        break;
                    cout << table[j][allo[i].c];
                }

                cout << '\n';
            }
        }
        
    }

    return 0;
}