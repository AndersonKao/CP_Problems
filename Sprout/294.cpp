// AC 
#include <iostream>
using namespace std;
int seq[10005];
int main(){
    int N;
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> seq[i];
        if(seq[i] > 0)
            seq[i] = 0;
    }
    for(int i = N-1; i >= 0; i--){
        cout << seq[i] << endl;
    }

    return 0;
}