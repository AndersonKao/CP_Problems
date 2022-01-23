#include <iostream>
using namespace std;

struct yah
{
    int dex;
    int num;
    yah * previous;
    yah * next;
};

int main(void)
{
    int n;
    cin >> n;
    yah object[n];
    int middex = 0;
    for(int i = 0; i < n; i++)
    {
        cin >> object[i].num;
        for(int k = 0; k <=i; k++)
        {
            if(object[i].num >= object[k].num)
            {
                object[i].
            }
        }
    }
    return 0;
}
