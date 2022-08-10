// WA 2019-10-21 13:47:16
#include <stdio.h>
#include <string.h>


int main()
{
    int RT, TK, RK;
    scanf("%d%d%d", &RT, &TK, &RK);
    int sum = (RT + TK + RK) / 2;

    printf("%d %d %d\n", sum - TK, sum - RK, sum - RT);

    return 0;
}
