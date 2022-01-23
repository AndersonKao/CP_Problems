#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;
struct  Guest
{
    int arrival, leave;
} g[10];
bool cmp(int i, int j)
{
    return abs(i) < abs(j);
}
int main(void){
    srand(time(NULL));
    int max= 5;
    int min= 1;
    int people = 5;
     for(int i = 0; i<people; i++)
     {
         
         g[i].arrival = rand() % (max - min + 1) + min;
         g[i].leave = rand() % (max - min + 1) + min;
         if(g[i].arrival > g[i].leave)
            swap(g[i].arrival,g[i].leave);
        if (g[i].arrival == g[i].leave)
        {
            /* code */
            g[i].leave++;
        }
        cout << g[i].arrival << " " << g[i].leave << endl;
     }
    vector<int> time;
    for (int i=0; i<people; i++)
    {
        time.push_back(+g[i].arrival);
        time.push_back(-g[i].leave);
    }
    sort(time.begin(),time.end(),cmp);
    int n = 0, maximum = 0;
    for (int i=0; i<time.size();i++){
        if(time[i] >=0)
            n++;
        else
            n--;
        if(maximum < n)
            maximum = n;
        
    }
    cout << endl <<"人數最多" << maximum << endl;
    return 0;
}