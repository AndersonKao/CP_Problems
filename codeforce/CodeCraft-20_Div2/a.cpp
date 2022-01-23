#include <iostream>
using namespace std;
int scores[1005];
int main(){
    int T;
    cin >> T;
    while(T--){
        int N,M;
        float total = 0;
        float ave;
        cin >> N >> M;
        for(int i =0;i<N;i++){
            cin >> scores[i];
            total += scores[i];
        }
        ave = total / N;
        // cout << ave << endl;
        if(total >= M)
            cout << M << endl;
        else{
            cout << total << endl;
        }
    }
    return 0;
}