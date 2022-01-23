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
bool bigcom(int a, int b)
{
    makes(&a,&b);
    if(a > 2*b)
        return false;
    if((a+b) % 3 == 0)
        return true;
    else
        return false;
}

int main()
{
    int T;
    cin >> T;
    int a, b;
    while (T--)
    {
        cin >> a >> b;
        if(bigcom(a,b))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}