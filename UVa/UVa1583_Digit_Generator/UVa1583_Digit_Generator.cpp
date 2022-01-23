// 2019-10-21 13:50:40
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define maxn 100000
int main()
{
    int allth[maxn];
    memset(allth,0,sizeof(allth));

    for (int i = 0; i < maxn;i++)
    {
        int x = i, y = i;
        while(x>0)
        {
            y += x % 10;
            x /= 10;
        }
        if(!allth[y])
            allth[y] = i;

    }

    int T, target;
    scanf("%d", &T);
    for (int i = 0; i < T;i++)
    {
        scanf("%d", &target);
        printf("%d\n", allth[target]);
    }

    return 0;
}