#include <iostream>
#include <cmath>
#define n2 pow(2,n)
#define uu 0
#define lu 1
#define ll 2
#define ul 3

using namespace std;
int n;
int a[4][2] = {{ul, -1}, {uu, ul}, {ll, lu}, {ll, lu}};
int mem[31][4]={0};
int safe;

int rec(int n, int state)
{
    if(!n) return 1;

    if(state == uu && mem[n-1][state]) return mem[n-1][state];
    else if(state == uu)
    {
        mem[n-1][state] = rec(n-1, a[state][0]);
    } 

    if(!mem[n-1][state])  
    {
        mem[n-1][state] = rec(n-1, a[state][0]) + rec(n-1, a[state][1]);
    }

    return mem[n-1][state];
}

int main()
{
    while(cin >> n)
    {
        if(n < 3) cout << 0 << "\n";
        safe = rec(n-2, uu) + rec(n-2, lu) + rec(n-2, ll) + rec(n-2, ul);
        cout << n2 - safe << "\n";
    }
}