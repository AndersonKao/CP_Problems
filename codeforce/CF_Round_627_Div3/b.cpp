#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int seq[5005];
int subseq[5005];
int numused[5005];
int main(){
    int T;
    cin >> T;
    while(T--){
        int N;
        cin >> N;
        memset(numused,0,sizeof(numused));
        for(int i = 0;i<N;i++){
            cin >> seq[i];
            subseq[i] = seq[i];
            numused[seq[i]]++;
        }
        bool must = false;
        for(int i = 1;i<N;i++)
            if(numused[i]>=3){
                cout << "YES\n";
                must = true;
                break;
            }
        if(must)
            continue;
        sort(subseq,subseq+N);
        bool sorted = true;
        for(int i = 0;i<N;i++){
            if(subseq[i] != seq[i]){
                sorted = false;
                break;
            }
        }
        if(sorted)
            cout << "NO\n";
        else
            cout << "YES\n";
    }
    return 0;
}