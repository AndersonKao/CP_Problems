#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct poker
{
    char s[4];
    int value;
} Poker;
int compare(const void *data1, const void *data2)
{
    Poker *ptr1 = (Poker *) data1;
    Poker *ptr2 = (Poker *) data2;
    if(ptr1->value < ptr2->value)
        return -1;
    else if(ptr1->value > ptr2->value)
        return 1;
    else
        return 0;
}
int main()
{
    int n;
    scanf("%d", &n);
    Poker array[1000];
    for(int i=0;i<n;i++)
    {
        scanf("%s", array[i].s);
        if(array[i].s[2]=='0') array[i].s[1]=':';
        if(array[i].s[0]=='J') array[i].value = 1000000;
        else if(array[i].s[1]=='A') array[i].value = 200+array[i].s[0];
        else if(array[i].s[1]=='J') array[i].value = 200*100+array[i].s[0];
        else if(array[i].s[1]=='Q') array[i].value = 200*101+array[i].s[0];
        else if(array[i].s[1]=='K') array[i].value = 200*102+array[i].s[0];
        else array[i].value = array[i].s[1]*200+array[i].s[0];
    }
    qsort(array,n,sizeof(Poker),compare);
    for(int i=0;i<n-1;i++)
    {
        if(array[i].s[1]==':') array[i].s[1]='1';
        printf("%s ", array[i].s);
        //printf("%d ", array[i].value);
    }
    if(array[n-1].s[1]==':') array[n-1].s[1]='1';
    printf("%s", array[n-1].s);
    printf("\n");
    return 0;
}