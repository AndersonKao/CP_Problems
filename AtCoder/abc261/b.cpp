#include <bits/stdc++.h>
using namespace std;

char table[1001][1001];
int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> table[i][j];

    bool sol = true;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++){
            if(i == j) 
                continue;
            if(table[i][j] == 'D'){
                if(table[j][i] != 'D')
                    sol = false;
            }
            else{
                if(table[i][j] == 'W' && table[j][i] != 'L')
                    sol = false;
                if(table[i][j] == 'L' && table[j][i] != 'W')
                    sol = false;
            }
        }
    }
    if(sol)
        cout << "correct\n";
    else
        cout << "incorrect\n";
    return 0;
}