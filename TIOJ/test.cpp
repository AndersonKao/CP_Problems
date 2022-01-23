#include "lib1995.h"
#define lo(x, y) 31 - __builtin_clz(y - x + 1)
using namespace std;
int s1[2500000], n, m;
int l[1000006], r[1000006];
bitset<1000006> ok;
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d %d", &l[i], &r[i]), l[i]--, --r[i];
    for (int i = 0; i < n; i++)
        scanf("%d", &s1[i]);
    for (int i = 0; i < m; i++)
        if (lo(l[i], r[i]) == 0)
            l[i] = s1[l[i]], ok[i] = 1;
    for (int i = 1; (1 << i) <= n; i++)
    {
        for (int j = 0; j + (1 << i) <= n; j++)
            s1[j] = (max(s1[j], s1[j + (1 << (i - 1))]));
        for (int j = 0; j < m; j++)
            if (lo(l[j], r[j]) == i && !ok[j])
                l[j] = max(s1[l[j]], s1[r[j] - (1 << i) + 1]), ok[j] = 1;
    }
    for (int i = 0; i < m; i++)
        printf("%d\n", l[i]);
}
