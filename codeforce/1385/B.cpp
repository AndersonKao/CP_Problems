#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
int seq[105];
int ansseq[55];
int main(){
    int T;
    cin >> T;
    while(T--){
        set<int> S;
        int N, index = 0;
        cin >> N;
        for(int i = 0; i < 2 * N; i++){
            cin >> seq[i];
        }
        for(int i = 0; i < 2 * N; i++){
            if(S.find(seq[i]) == S.end()){
                ansseq[index] = seq[i];
                index++;
                S.insert(seq[i]);
            }
        }
        for(int i = 0; i < N; i++)
            cout << ansseq[i] << ((i == N-1) ? '\n' : ' ');
    }
    return 0;
}