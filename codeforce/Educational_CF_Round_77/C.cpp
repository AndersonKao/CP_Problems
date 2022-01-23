#include <iostream>
using namespace std;

void makes(int *a, int *b)
{
    if (*b > *a)
    {
        int c = *a;
        *a = *b;
        *b = c;
    }
}

int bigcom(int a, int b)
{
    if (a == 1 || b == 1)
    {
        return 1;
    }
    makes(&a,&b);
    if (a % b == 0)
        return b;
    return bigcom(b, a % b);
}

unsigned long long maxit(int a,int b){
    return a / bigcom(a,b) * b;
}

int main(){
    int T,r,b,k;
    cin >> T;
    while(T--){
        cin >> r >> b >> k;
        unsigned long long limit = r /bigcom(r,b) * b;
        int tmpr = 0,tmpb = 0;
        int flagr ,flagb;
        tmpr = limit / r;
        tmpb = limit / b;
        makes(&tmpr,&tmpb);
        if(tmpr / tmpb >= k)
            cout << "REBEL\n";
        else
            cout << "OBEY\n";
    }

    return 0;
}