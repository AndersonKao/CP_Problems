#include <stdio.h>
int confort[1000001], height[10000001];
int main()
{
    int N, X;
    scanf("%d, %d", &N, &X);
    scanf("%d", height[0]);
    for(int i=1; i<N; i++)
    {
        scanf("%d", height[i]);
        if(height[i]>height[i-1])
        {
            confort[i] = confort[i-1] + 1;
            if(confort[i] == X)printf("%d", i+1);
        }
        else if(height[i]<=height[i-1]){
            confort[i] = 0;
        }
    }
    return 0;
}