// AC2019-10-21 13:53:00
#include <iostream>
#include <string>
#define _for(i, a, b) for (int i=(a); i < (b); i++)
using namespace std;
int readint(void);

int main(){
    int n = readint();
    int scores[n];
    int cnt;
    string scorestr[n];
    _for(i, 0, n)
    {
        scores[i] = 0;
        cin >> scorestr[i];
        cnt = 0;
        _for(k,0,scorestr[i].size())
        {
            if(scorestr[i][k] == 'O')
            {
                cnt++;
                scores[i] += cnt;
            }else
            {
                cnt = 0;
            }
        }
    }
    _for(i,0,n)
    {
        cout << scores[i] << endl;
    }


    return 0;
}
int readint(void){
    int x;
    cin >> x;
    return x;
}