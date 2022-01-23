#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    while(cin.get() != '\n')
    int n;
    cin >> n; // n >= 2 n <= 3
    int s[n];
    for(int i = 0; i < n; i ++)
    {
        cin >> s[i];
    }
    if(n == 2)
    {
        if(s[0] == s[1])
            cout << s[0] << endl;
        long long bigger,smaller;
        bigger = s[0] > s[1] ? s[0] : s[1];
        smaller = s[0] < s[1] ? s[0] : s[1];
        while(true)
        {
            bigger = bigger%smaller;
            if(bigger != 0)
                swap(bigger,smaller);
            else
                break;
        }
        cout << s[0] * s[1] / smaller;
    }else
    {

        long long ma = s[0] > s[1] ? s[0] : s[1];
        ma = ma > s[2] ? ma : s[2];
        int k = ma;
        for(int i = 1; i > 0 ; i++)
        {
                if(ma%s[0] == 0)
                {
                    if(ma%s[1] == 0)
                    {
                        if(ma%s[2] == 0)
                            break;
                    }
                }

                    ma = ma + k;




        }
        cout << ma << endl;
    }


    return 0;

}
