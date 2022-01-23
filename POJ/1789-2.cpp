#include <iostream>
#include <memory.h>
#include <string>
#include <istream>
#include <sstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>
#include <queue>
#include <math.h>
#include <cstdio>
using namespace std;
typedef long long LL;
const int MAXM = 4000000+10;
const int MAXN = 2000+10;

struct Path
{
    int _l,_r;
    double _value;
    bool operator < (const Path & that)const{
        return this->_value < that._value;
    }
}path[MAXM];

string lorry[MAXN];


int Father[MAXN];
int n;

int Get_F(int x)
{
    return Father[x] = (Father[x] == x) ? x : Get_F(Father[x]);
}

void Init()
{
    for (int i = 1;i <= n;i++)
        Father[i] = i;
}

int Get_Len(string a,string b)
{
    int res = 0;
    for (int i = 0;i < 7;i++)
        if (a[i] != b[i])
            res++;
    return res;
}

int main()
{
    while (cin >> n && n)
    {
        Init();
        for (int i = 1; i <= n; i++)
            cin >> lorry[i];
        int pos = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = i+1; j <= n; j++)
            {
                int len = Get_Len(lorry[i], lorry[j]);
                path[++pos]._l = i;
                path[pos]._r = j;
                path[pos]._value = len;
            }
        }
        int sum = 0;
        sort(path + 1, path + 1 + pos);
        for (int i = 1; i <= pos; i++)
        {
            int tl = Get_F(path[i]._l);
            int tr = Get_F(path[i]._r);
            if (tl != tr)
            {
                Father[tl] = tr;
                sum += path[i]._value;
            }
        }
        cout << "The highest possible quality is 1/" << sum << '.' << endl;
    }

    return 0;
}