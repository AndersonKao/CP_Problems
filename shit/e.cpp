#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<long long> _list(n), pre(n + 1);
    for (auto &i : _list)
        cin >> i;

    for (int i = 1; i <= n; i++)
    {
        pre[i] = pre[i - 1] + _list[i - 1];
    }

    set<int> dnum;
    dnum.insert(-1);
    dnum.insert(n);

    long long local = (pre[n] - pre[0]) * n;
    long long total = local;

    map<long long, int> Local;
    Local[local]++;

    vector<string> que(q);
    vector<int> qnum(q);

    for (int i = 0; i < q; i++) {
        cin >> que[i];
        
        if (que[i] == "D")
            cin >> qnum[i];
}
    for (int i = 0; i < q; i++)
    {
        if (que[i] == "D")
        {
            int num = qnum[i];

            // if (*dnum.lower_bound(num) == num)
            //     continue;

            auto itL = *prev(dnum.upper_bound(num));
            auto itR = *dnum.upper_bound(num);

            if (!(itL + 1 == num and itR - 1 == num))
                dnum.insert(num);

            auto it = Local.find((pre[itR] - pre[itL + 1]) * (itR - 1 - (itL + 1) + 1));

            if (it->second == 1)
            {
                Local.erase(it);
            }
            else
            {
                it->second--;
            }

            Local[(pre[num] - pre[itL + 1]) * (num - 1 - (itL + 1) + 1)]++;
            Local[(pre[itR] - pre[num + 1]) * (itR - 1 - (num + 1) + 1)]++;

            total -= (pre[itR] - pre[itL + 1]) * (itR - 1 - (itL + 1) + 1);
            total += (pre[num] - pre[itL + 1]) * (num - 1 - (itL + 1) + 1);
            total += (pre[itR] - pre[num + 1]) * (itR - 1 - (num + 1) + 1);
        }
        else if (que[i] == "QS")
        {
            cout << total << '\n';
        }
        else
        {
            cout << Local.rbegin()->first << '\n';
        }
    }
}