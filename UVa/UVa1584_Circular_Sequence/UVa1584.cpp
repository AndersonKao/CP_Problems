// AC 2019-10-21 13:51:18
#include <stdio.h>
#include <string.h>


#define maxn 105
int less(const char *s,int p,int q){
    int n = strlen(s);
    for (int i = 0; i < n;i++){
        if(s[(p+i)%n] != s[(q+i)%n])
        {
            return s[(p + i) % n] < s[(q + i) % n];
        }
    }
    return 0;
}

    int main()
{
    int T;
    scanf("%d", &T);
    while(T--){
        int ans = 0;
        char s[maxn];
        scanf("%s", s);
        int n = strlen(s);
        for (int i = 0; i < n;i++)
        {
            if(less(s,i,ans))
                ans = i;
        }
        for (int i = 0; i < n;i++)
        {
            putchar(s[(ans + i) % n]);
        }
        putchar('\n');
        }

    return 0;
}