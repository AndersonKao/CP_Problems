#include <bits/stdc++.h>
using namespace std;

int r, c;
int ans;
vector<bool> status;

bool check()
{
    for (int i = 0; i < r*c; i++)
    {
        if (!status[i])
            continue;

        int tr = i / c;
        int tc = i % c;

        // up.
        if (tr >= 2)
            if (status[i-c] and !status[i-c-c])
                return false;

        // down.
        if (tr <= r-3)
            if (status[i+c] and !status[i+c+c])
                return false;

        // left.
        if (tc >= 2)
            if (status[i-1] and !status[i-2])
                return false;

        // right.
        if (tc <= c-3)
            if (status[i+1] and !status[i+2])
                return false;
    }
    
    return true;
}

void recur(int num)
{
    if (num == r*c)
    {
        if (check())
            ans++;

        return;
    }

    recur(num+1);
    status[num] = 1;
    recur(num+1);
    status[num] = 0;
}

int main()
{
    int n;
    cin >> n;

    while (n--)
    {
        ans = 0;
        cin >> r >> c;

        status.resize(r*c);
        fill(status.begin(), status.end(), 0);

        recur(0);

        cout << ans << endl;
    }
}