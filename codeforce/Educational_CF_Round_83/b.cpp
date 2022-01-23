#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int N;

int seq[105];
int main(){
    int T; cin >> T;
    while(T--){
        cin >> N;
        memset(seq,0,sizeof(seq));
        // appear.clear();

        for(int i=0;i<N;i++){
            cin >> seq[i];
        }
        sort(seq,seq+N);
        for(int i=N-1;i>=0;i--){
            cout << seq[i];
            if(i != 0)
                cout << " ";
        }
        cout << endl;
    }
    return 0;
}