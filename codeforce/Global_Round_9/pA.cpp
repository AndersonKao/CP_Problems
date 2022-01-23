#include <iostream>
using namespace std;
long long  seq[500];
int N;
int nneg, npos, tobe;

void dp(int index){
    if(index >= N)
        return;
    if(nneg >= tobe && npos >= tobe)
        return;
    // bool lpos, rpos, nextlpos, nextrpos;
    int newnpos = npos, newnneg = nneg;
    int origin = seq[index];
    seq[index] = -seq[index];
    if(origin - seq[index-1] >= 0)
        newnneg--;
    if(origin - seq[index-1] <= 0)
        newnpos--;
    if(seq[index] - seq[index-1] >= 0)
        newnneg++;
    if(seq[index] - seq[index-1] <= 0)
        newnpos++;
    if(index + 1 < N){
        if(seq[index+1] - origin >= 0)
            newnneg--;
        if(seq[index+1] - origin <= 0)
            newnpos--;
        if(seq[index+1] - seq[index] >= 0)
            newnneg++;
        if(seq[index+1] - seq[index] <= 0)
            newnpos++;
    }
    if(npos > nneg){
        if(newnpos < npos || newnneg > nneg){
           npos = newnpos;
           nneg = newnneg; 
        }else
        {
            seq[index] = -seq[index];
        }
    }else{
        if(newnpos > npos || newnneg < nneg){
           npos = newnpos;
           nneg = newnneg; 
        }else
        {
            seq[index] = -seq[index];
        }
    }
    dp(index + 1);
    
}

int main(){
    int Q;
    cin >> Q;
    while(Q--){
        nneg = npos = 0;
        cin >> N;
        for(int i = 0; i < N; i++){
            cin >> seq[i];
            if(i >= 1){
                if(seq[i] - seq[i-1] >= 0)
                    nneg++;
                if(seq[i] - seq[i-1] <= 0)
                    npos++;
            }
        }
        tobe = (N-1) / 2;
        dp(1);
        for(int i = 0; i < N; i++)
            cout << seq[i] << (i == N-1 ? '\n' : ' ');

    }

    return 0;
}