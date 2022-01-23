#include <iostream>
#include <climits>
#include <cmath>
using namespace std;

long long tarseq[35];
const long long  Upperlimit = 10e16 + 5;

long long getMax(long long k){
    long long ans = k;
    if(ans == 1)
        return 1;
    while(ans<Upperlimit){
        ans *= k;
    }
    return ans / k;

}

int main(){
    int T;cin >> T;
    while(T--){
        int size;
        long long k;
        cin >> size >> k;
        for(int i=0;i<size;i++)
            cin >> tarseq[i];
        // cout << getMax(k) << endl;
        long long minor = getMax(k);
        while(minor >= 1){
            // cout << "minor: " <<  minor << endl;
            int maxindex = 0;
            for(int i=1;i<size;i++){
                maxindex = tarseq[maxindex] > tarseq[i] ? maxindex : i;
            }
            if(tarseq[maxindex] >= minor){
                tarseq[maxindex] -= minor;
            }
            // for(int i=0;i<size;i++)
            //     cout << tarseq[i] << " ";
            // cout << endl;
            
            if(minor == 1)
                break;
            minor /= k;
        }
        bool flag = true;
        for(int i = 0;i<size;i++){
            if(tarseq[i] != 0){
                flag = false;
                break;
            }
        }
        if(flag){
            cout << "YES\n";
        }else
            cout << "NO\n";
    }
    return 0;
}