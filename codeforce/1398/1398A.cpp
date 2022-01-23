#include <iostream>
using namespace std;
int N;
int T;
int seq[100005];
int main(){
    cin >> T;
    while(T--){
        cin >> N;
        for(int i = 0; i < N; i++){
            cin >> seq[i];
        }
        if(seq[0] + seq[1] > seq[N-1])
            cout << "-1\n";
        else
            cout << "1 2 " << N << endl;
    }
    return 0;
}