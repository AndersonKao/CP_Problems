// AC 2020-07-04 16:20
#include <algorithm>
#include <cstdio>
using namespace std;
#define IL(X) ((X) * 2 + 1)
#define IR(X) ((X) * 2 + 2)

int seq[2000006] = {0};
int dataseq[500005] = {0};

void build(int L, int R, int index){
    if(L == R){
        seq[index] = dataseq[L];
        return ;
    }
    int M = (L + R) / 2;
    build(L, M, IL(index));
    build(M + 1, R, IR(index));
    seq[index] = max(seq[IL(index)], seq[IR(index)]);
}

int Query(int l, int r, int L, int R, int index){
    if(l == L && r == R)
        return seq[index];
    int M = (L + R) / 2;
    if(r <= M){
        return Query(l,r,L,M,IL(index));
    }else if( M < l){
        return Query(l,r,M+1, R, IR(index));
    }else{
        return max(Query(l,M, L, M, IL(index)), Query(M+1, r, M + 1, R, IR(index)));
    }
}


int main(){
    int N;
    int Q, qL, qR;
    scanf("%d", &N);
    // cin >> N;

    for(int i = 0; i < N; i++){
        scanf("%d", &dataseq[i]);
        // cin >> dataseq[i];
    }
    build(0, N - 1, 0);
    scanf("%d", &Q);
    // cin >> Q;
    while(Q--){
        scanf("%d %d", &qL, &qR);
        // cin >> qL >> qR;
        if(qL > qR){
            int c = qL;
            qL = qR;
            qR = c;
        }
        qL--;
        qR--;
        printf("%d\n", Query(qL, qR, 0, N - 1, 0));
        // cout << Query(qL, qR, 0, N - 1, 0) << "\n";
    }
    return 0;
}