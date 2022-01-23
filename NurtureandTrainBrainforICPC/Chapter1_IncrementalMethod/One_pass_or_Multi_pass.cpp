#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
#define REP(i, n) for (int i = 0; i < n; i++)

int main()
{
    //one-pass
    
    int people1;
    cin >> people1;
    int scores1[people1];
    int safty1 = 0, sum1 =0;
    REP(i,people1)
    {
        cin >> scores1[i];
        sum1+= scores1[i];
        if(scores1[i]>=60)
            safty1++;
    }
    cout << "Safty:" << safty1 << " ave:" << sum1/people1 << endl;
    safty1 = 0;
    sum1 = 0;
    REP(i, people1)
    {
        if(scores1 [i] > 100)
            scores1[i] = 100;
        scores1[i] = sqrt(scores1[i]) * 10 +10;
        if (scores1[i] >= 95)
            scores1[i] = 95;
        if(scores1[i]<50)
            scores1[i] = 50;
        sum1 += scores1[i];
         if (scores1[i] >= 60)
            safty1++;
    }
    cout << "Safty:" << safty1 << " ave:" << sum1/people1 << endl;
    //multi-pass
    int people;
    cin >> people;
    int scores[people];
    int safty = 0, sum = 0;
    REP(i, people)
    {
        cin >> scores[i];
    }
    REP(i, people)
    {
        sum += scores[i];
    }
    REP(i, people)
    {
        if (scores[i] >= 60)
            safty++;
    }
    cout << "Safty:" << safty << " ave:" << sum / people << endl;
    safty = 0;
    sum = 0;
    REP(i,people)
    {
        if(scores[i] > 100)
            scores[i] = 100;
    }
    REP(i,people)
    {
        scores[i] = sqrt(scores[i]) * 10 +10;
    }
    REP(i, people)
    {
        if (scores[i] >= 95)
            scores[i] = 95;
        if(scores[i]<50)
            scores[i] = 50;
    }
    REP(i, people)
    {
        sum += scores[i];
    }
    REP(i, people)
    {
        if (scores[i] >= 60)
            safty++;
    }
    
    cout << "Safty:" << safty << " ave:" << sum / people << endl;

    return 0;
}