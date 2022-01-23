// AC 2020-07-06 17:09
#include <iostream>
using namespace std;
#define IL(X) ((X * 2) + 1)
#define IR(X) ((X * 2) + 2)
#define MAXN 500005
struct Node{
    long long sum;
    long long lazy_tag;
    int size;
};
short dataseq[MAXN];
Node seq[MAXN * 4 + 5];
void build(int l, int r, int L, int R, int index);
void modify(int l, int r, int L, int R, int index, long long Add);
long long Query(int l, int r, int L, int R, int index);
void pull(int index){
    seq[index].sum = seq[IL(index)].sum + seq[IR(index)].sum;
    seq[index].size = seq[IL(index)].size + seq[IR(index)].size;
    seq[index].lazy_tag = 0;
}
void push(int index){
    seq[IL(index)].lazy_tag += seq[index].lazy_tag;
    seq[IL(index)].sum += seq[index].lazy_tag * seq[IL(index)].size;
    seq[IR(index)].lazy_tag += seq[index].lazy_tag;
    seq[IR(index)].sum += seq[index].lazy_tag * seq[IR(index)].size;
    seq[index].lazy_tag = 0;
}
void push(int index);

int main(){
    int N, Q;
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> dataseq[i];
    }
    build(0, N-1, 0, N - 1, 0);
    int qL, qR, Op, Add;
    cin >> Q;
    while(Q--){
        cin >> Op >> qL >> qR;
        qL--;
        qR--;
        if(Op == 1){
            cin >> Add;
            modify(qL, qR, 0, N - 1, 0, Add);
        }else if(Op == 2){
            cout << Query(qL, qR, 0, N - 1, 0) << '\n';
        }
    }
    return 0;
}

void build(int l, int r, int L, int R, int index){
    if(l == r){
        seq[index].sum = dataseq[l];
        seq[index].size = 1;
        seq[index].lazy_tag = 0;
        return; 
    }
    int M = (L + R) / 2;
    build(l, M, L, M, IL(index));
    build(M + 1, r, M + 1, R, IR(index));
    pull(index);
}

void modify(int l, int r, int L, int R, int index, long long Add){
    if(l == L && r == R){
        seq[index].lazy_tag += Add;
        seq[index].sum += Add * seq[index].size;
        return;
    }
    push(index);
    int M = (L + R) / 2;

    if(r <= M){
        modify(l, r, L, M, IL(index), Add);
    }else if(l > M){
        modify(l, r, M + 1, R, IR(index), Add);
    }else{
        modify(l, M, L, M, IL(index), Add);
        modify(M + 1, r, M + 1, R, IR(index), Add);
    }
    pull(index);
}

long long Query(int l, int r, int L, int R, int index){
    if(l == L && r == R){
        return seq[index].sum;
    }
    int M = (L + R) / 2;
    push(index);

    pull(index);
    if(r <= M){
        return Query(l, r, L, M, IL(index));
    }else if(l > M){
        return Query(l, r, M + 1, R, IR(index));
    }else{
        return Query(l, M, L, M, IL(index)) + 
        Query(M + 1, r, M + 1, R, IR(index));
    }

}