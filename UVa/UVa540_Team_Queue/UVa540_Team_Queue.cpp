// UVa540_Team_Queue
// AC 2019-10-20 23:09:19
#include <iostream>
#include <map>
#include <queue>
using namespace std;
int team[1000000] = {0};
const int maxt = 1000 + 10;
int main()
{
    int t, kase = 0;
    while (scanf("%d", &t) == 1 && t)
    {
        for (int i = 0; i <= 1000000; i++)
            team[i] = 0;
        printf("Scenario #%d\n", ++kase);
        // 用陣列log
        for (int i = 0; i < t; i++)
        {
            int n, x;
            scanf("%d", &n);
            while (n--)
            {
                scanf("%d", &x);
                team[x] = i;
            }
        }
        queue<int> q;
        queue<int> q2[maxt];
        while (1)
        {
            int x;
            char str[10];
            scanf("%s", str);
            if (str[0] == 'S')
                break;
            else if (str[0] == 'E')
            {
                scanf("%d", &x);
                int t = team[x];
                if (q2[t].empty())
                    q.push(t);
                q2[t].push(x);
            }
            else if (str[0] == 'D')
            {
                int t = q.front();
                printf("%d\n", q2[t].front());
                q2[t].pop();
                if (q2[t].empty())
                    q.pop();
            }
        }
        printf("\n");
    }

    return 0;
}
