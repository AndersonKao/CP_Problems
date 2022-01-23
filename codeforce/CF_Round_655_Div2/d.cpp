#include <queue>
#include <iostream>
#include <vector>
#define LL long long
using namespace std;
struct Node{
    Node * lc, *rc;
    LL value;
    Node():lc(0),rc(0), value(0){}
    bool operator<(Node &rhs){
        return (this->lc->value + this->rc->value)
         < (rhs.lc->value + rhs.rc->value);
    }
};

int N;
int seq[200005];
Node Nseq[200005];
int main(){
    cin >> N;
    
    for(int i = 0; i < N; i++){
        cin >> Nseq[i].value;
    }
    Nseq[0].lc = &Nseq[N-1];
    Nseq[0].rc = &Nseq[1];
    Nseq[N-1].lc = &Nseq[N-2];
    Nseq[N-1].rc = &Nseq[0];
    for(int i = 1; i < N - 1; i++){
        Nseq[i].lc = &Nseq[i-1];
        Nseq[i].rc = &Nseq[i+1];
    }

    return 0;
}
