#include <iostream>
using namespace std;
int N, T;
int main(){
    // int T;
    cin >> T;
    while(T--){
        cin >> N;
        for(int i = 0; i < N; i++){
            cout << "1";
            cout << (i == N-1 ? '\n' : ' ');
        }
    }

    return 0;
}