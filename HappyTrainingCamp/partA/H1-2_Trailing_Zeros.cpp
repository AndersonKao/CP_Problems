#include <bits/stdc++.h>
using namespace std;

unsigned N;

int main(){
    cin >> N;

    unsigned long long ans = 0;
    unsigned long long cnt = 1;
    unsigned slavecnt = 1;
    for (unsigned i = 5; i <= N; i*=5)
    {
        slavecnt = 1;
        for (unsigned mul = 1; i * mul <= N; mul++, slavecnt++){
            if(slavecnt == 5)
            {
                slavecnt = 0;
                continue;
            }
            ans += cnt;
        }
        cnt++;
    }
    cout << ans << endl;

    return 0;
}