// AC 2019-10-21 13:54:31
#include <algorithm>
#include <cstdio>
using namespace std;
int main()
{
    const int maxn = 10000;
    int len, t, a[maxn], ans,want,counter =0;
    while(scanf("%d %d",&len,&t) == 2 && len !=0){
        for (int i = 0; i < len;i++)
            scanf("%d", &a[i]);
        sort(a, a + len);
         printf("CASE# %d:\n", ++counter);
        while(t--)
        {
            scanf("%d", &want);
           
            ans = lower_bound(a, a + len, want) - a ;
            if(a[ans] == want) printf("%d found at %d\n",want, ans+1);
            else
                printf("%d not found\n",want);
        }
        
    }

}