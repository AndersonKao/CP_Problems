// Collecting coins
// AC 00:17:09

#include <iostream>
using namespace std;
int main(){
    int T;
    cin >> T;
     long long n;
     long long seq[3];
    while(T--){
         long long max;
        max = 0;
        for(int i=0;i<3;i++)
            cin >> seq[i];
        cin >> n;
        for(int i=0;i<3;i++){
            max = max > seq[i] ? max : seq[i];
        }
        // cout << max << "\n";
        for(int i=0;i<3;i++){
            n -= (max - seq[i]);
            // cout << "n remaining" << n << "\n";
            
        }
        // cout << max;
        if(n < 0){
                cout << "NO\n";
                continue;
        }
        if(n % 3 == 0)
            cout << "YES\n";
        else
        {
            cout << "NO\n";
        }
        

    }
    return 0;
}