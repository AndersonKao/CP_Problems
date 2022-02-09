#include <bits/stdc++.h>
using namespace std;

int cnt = 0;
bool print;
void move(int front, int to, int where, int N)
{
    if(N == 1){
        cnt++;
        if(print)
            cout << front << " " << to << endl;
        return;
    }

    move(front, where, to, N-1);
    move(front, to, where, 1);
    move(where, to, front, N - 1);
}

int main()
{
    int N;
    cin >> N;
    print = false;
    move(1, 3, 2, N);
    cout << cnt << endl;
    print = true;
    move(1, 3, 2, N);

    return 0;
}