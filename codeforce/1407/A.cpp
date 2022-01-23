#include <cstring>
#include <iostream>
// #define LOCAL
using namespace std;
int seq[10005];
bool output[10005];
int main(){
    int T;
    cin >> T;
    while(T--){
        memset(seq, 0, sizeof(seq));
        memset(output, 0, sizeof(output));
       
        int N;
        cin >> N;

        int oddnum, zeronum;
        oddnum = zeronum = 0;
        for (int i = 1; i <= N; i++){
            cin >> seq[i];
            if(seq[i] & 1){
                oddnum += 1;
            }else{
                zeronum += 1;
            }
        }
        if(oddnum > zeronum){
            #ifdef LOCAL
            cout << "odd bigger!\n";
            #endif
            int cnt = 0;
            for (int i = 1; i <= N; i++){
                if(seq[i]){
                    output[i] = true;
                    cnt++;
                }
            }
            if(cnt & 1){
                for (int i = 1; i <= N; i++){
                    if(output[i]){
                        output[i] = false;
                        break;
                    }
                }
                cnt--;
            }

            cout << cnt << endl;
            for (int i = 1; i <= cnt; i++){
                cout << 1 << (i == cnt ? '\n' : ' ');
            }
        }else{
            int cnt = 0;
            for (int i = 1; i <= N; i++){
                if(!seq[i]){
                    output[i] = true;
                    cnt++;
                }
            }
            cout << cnt << endl;
            for (int i = 1; i <= cnt; i++){
                cout << 0 << (i == cnt ? '\n' : ' ');
            }
        }
        
    }
    return 0;
}