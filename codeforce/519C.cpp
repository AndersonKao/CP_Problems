#include <iostream>
using namespace std;
int n, m;
int main(){
    cin >> n >> m;

    if(n >= 2 * m){
        cout << m << '\n';
    }else if(m >= 2*n){
        cout << n << '\n';
    }else{
        int ans = 0;
        while(n && m){
            if(n == 1 && m == 1)
                break;
            if(n > m && n >= 2){
                n -= 2;
                m -= 1;
                ans++;
            }else if(m >= 2){
                m -= 2;
                n -= 1;
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}