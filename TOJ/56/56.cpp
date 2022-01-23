#include <iostream>
using namespace std;

int main(void)
{
    long long n,m;
    long long sheep,peter;
    int times = 0;
    bool flag = true;
    int k;
    long jh , hu;
    while(cin >> n >> m)
    {
        sheep = max(n,m);
        peter = min(n,m);
//        cout << sheep << " " << peter << endl;
        while( (sheep > 0) && (peter > 0) )
        {
            if(flag)
            {
                sheep %= peter;
            }else
            {
                peter %= sheep;
            }
            if(sheep >= peter)
                flag = true;
            else
                flag = false;
//            cout << sheep << " " << peter << endl;
        }
        k = max(sheep,peter);
        cout << k << endl;

    }

    return 0;
}
