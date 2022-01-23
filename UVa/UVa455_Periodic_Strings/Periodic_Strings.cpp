// WA 2019-10-21 13:47:52
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <string.h>
#define _for(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;

int main()
{

    char str[86];
    int T;
    cin >> T;
    cin.get();
    cin.get();
    int counters[T];
    int lens[T];
    _for(i, 0, T)
    {
        scanf("%s", str);
        if(i != T-1){
            cin.get();
            cin.get();
        }
        
        int counter = 1;
        int n = strlen(str);
        lens[i] = strlen(str);
        bool flag = true;

        while(flag){
            char base[counter];
            strncpy(base, str, counter);
            _for(k,0,n)
            {
                if(str[k]!=base[k%counter]){
                    counter++;
                    flag = true;
                    break;
                }else{
                    flag = false;
                }
            }
        }

        counters[i] = counter;

          
    }
    for (int i = 0; i < T;i++)
    {
        if (counters[i] != lens[i])
        {
            cout << counters[i] << endl;
            
        }
        else
            cout << 1 << endl;
        if(i != T-1) cout << endl;  
    }
        
    return 0;
}