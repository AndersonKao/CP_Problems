#include <iostream>
using namespace std;
int main(){
    int seq[105];
    int N; cin >> N;
    float total = 0;
    float ave;
    for(int i=1;i<=N;i++){
        cin >> seq[i];
        total += seq[i];
    }
    ave = total / N * 2;
    cout << "total: " << total << " N:" << N << endl;
    cout << ave << endl;
    
        for(int i=1;i<=N;i++){
            if(seq[i] != 0){
                for(int j = 1;j<=N;j++){
                    if(j != i && ((seq[i] + seq[j]) == ave)){
                        cout << i << " " << j << "\n";
                        seq[i]  = 0;
                        seq[j] = 0;
                    }
                }
            }
        }

    return 0;
}
