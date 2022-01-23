#include <iostream>
using namespace std;
int T, N, segment;
int seq[200005];
int main(){
    cin >> T;
    bool flag; // true for 上一個不是相同
    while(T--){
        segment = 0;
        flag = true;
        cin >> N;
        for(int i = 1; i <= N; i++){
            cin >> seq[i];
            if(seq[i] == i && flag && i != 1){
                flag = false;
                segment++;
            }else if(seq[i] == i){
                flag = false;
            }else{
                flag = true;
            }
        }
        if(seq[N] != N)
            segment++;
        if(segment > 1)
            cout << "2\n";
        else if(segment == 1)
            cout << "1\n";
        else
            cout << "0\n";
    }
    return 0;
}