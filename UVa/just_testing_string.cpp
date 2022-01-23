#include <cstring>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <algorithm>
#define _for(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
void mergesort(int *arr, int len);
struct Point{int x, y;};
void test(Point x);
int main()
{
    Point
    return 0;
}
void mergesort(int *arr, int len)
{
    if (len <= 1)
        return;

    int leftlen = len / 2, rightlen = len - leftlen;
    int *leftarr = arr, *rightarr = arr + leftlen;
    mergesort(leftarr, leftlen);
    mergesort(rightarr, rightlen);

    static int temp[10];
    int tmplen = 0, l = 0, r = 0;
    while (l < leftlen && r < rightlen)
        if (leftarr[l] < rightarr[r])
            temp[tmplen++] = leftarr[l++];
        else
            temp[tmplen++] = rightarr[r++];
    while (l < leftlen)
        temp[tmplen++] = leftarr[l++];
    while (r < rightlen)
        temp[tmplen++] = rightarr[r++];
    for (int i = 0; i < tmplen; i++)
        arr[i] = temp[i];
}

/*
  *
 *** 
*****
  *
  *  
*/
