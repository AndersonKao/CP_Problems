#include <iostream>
using namespace std;
struct minpowertex
{
    int power;
    int tex;
};
int main() {
    int budgetnum;
    cin >> budgetnum;
    int bweight[budgetnum];
    int bttimes[budgetnum];
    int allweight = 0;

    for(int i = 0; i < budgetnum; i++)
    {
        cin >> bweight[i];
        allweight+=bweight[i];
    }
    cout << allweight << endl;

    for(int i = 0; i < budgetnum; i++)
    {
        cin >> bttimes[i];
    }
   /* for(int i = 0;i < budgetnum; i++)
    {
        cout << bweight[i] << " " << bttimes[i] << endl;
    }*/
    bool testtex[budgetnum];
    for(int k = 0; k < budgetnum ;k++)
            testtex[k] = true;
    int placetex[budgetnum];
    int exweight;
    int changebnum = budgetnum;
    minpowertex minb;
    int totalpower = 0;
    bool tt; // whether minb has the initial value
    for(int i = 0; i < budgetnum; i++)
    {
        tt = false;
        for(int t = 0; t < budgetnum; t++) // smallest
        {
            if(testtex[t] == true)
            {
                if(tt == false)
                {
                    minb.power = (allweight-bweight[t]) * bttimes[t];
                    minb.tex = t;
                    tt = true;
                 //   cout << "tt" <<endl;
                }

                exweight = (allweight-bweight[t]) * bttimes[t];
                if(exweight < minb.power)
                {
                minb.power = exweight;
                minb.tex = t;
               // cout << "minb" << endl;
                }
              //  cout << "oohohoh" << endl;
            }
           // cout << "power = " << minb.power << endl;
        }
        totalpower+=minb.power;
        allweight-=bweight[minb.tex];
        placetex[budgetnum-i-1] = minb.tex;
        testtex[minb.tex] = false;
        //for(int k = 0; k < budgetnum ;k++)
          //  cout << testtex[k] << " ";
        //cout << endl;
        changebnum--;
       // cout << "swtich!" << endl;
    }
    /*for(int i = 0; i < budgetnum; i++)
        cout << placetex[i] << endl;*/

        cout << totalpower << endl;


    return 0;
}
