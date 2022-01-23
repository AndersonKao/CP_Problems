#include <cstdio>

int main()
{
    int T;
    scanf("%d", &T);
    long long a, b;
    a = b = 0;
    for (int i = 0; i < T; i++)
    {
        scanf("%lld %lld", &a, &b);
        if(a < b || ((a + b) & 1))  
        {
            printf("impossible\n");
        }
        else{
            printf("%lld %lld\n", (a + b) / 2 , (a - b) / 2);
        }
    }
}