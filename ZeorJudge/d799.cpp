// AC 2020-07-06 15:56
#include <iostream>
#include <algorithm>
using namespace std;
#define IL(X) ((X) * 2 + 1)
#define IR(X) ((X) * 2 + 2)

// #define IL(X) (X<<1)
// #define IR(X) (X<<1 | 1)
struct Node{
    int size;
    long long sum;
    long long lazy_add;
    long long real_sum(){
        return sum + lazy_add * size; 
    }
    bool islazy(){
        return lazy_add != 0;
    }

};
int maxI = 0;
long long dataseq[500005];
Node seq[20000005];
void build(int L, int R, int index);
long long Query(int l, int r, int L, int R, int index);
void pull(int index);
void push(int index);
void addition(int l, int r, int L, int R, int index, long long toAdd);
int main(){
    std::ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> dataseq[i];
    }
    build(0, N - 1, 0);
    int Q, Op, x ,y;
    long long k;
    cin >> Q;
    while(Q--){
        cin >> Op;
        if(Op == 1){
            cin >> x >> y >> k;
            x--;
            y--;
            addition(x, y, 0, N-1, 0, k);
        }else if(Op == 2){
            cin >> x >> y;
            x--;
            y--;

            cout << Query(x, y, 0, N-1, 0) << "\n";
        }
        // for(int i = 0; i <= maxI; i++){
        //     cout << "i: " << i << " Sum: " << seq[i].sum
        //     << " Lazy: " << seq[i].lazy_add << "\n";
        // }
    }
    return 0;
}
void build(int L, int R, int index){
    if(L == R){
        seq[index].sum = dataseq[L];
        seq[index].lazy_add = 0;
        seq[index].size = 1;
        maxI = max(maxI, index);
        return;
    }
    int M = (L + R) / 2;
    build(L, M, IL(index));
    build(M + 1, R, IR(index));
    pull(index);
}

long long Query(int l, int r, int L, int R, int index){
    if(l == L && r == R){
        return seq[index].real_sum();
    }

    int M = (L + R) /2;
    push(index);
    pull(index);
    if(r <= M){
        return Query(l, r, L, M, IL(index));
    } 
    else if(l > M){
        return Query(l, r, M + 1, R, IR(index));
    } 

    return Query(l, M, L, M, IL(index)) + Query(M + 1, r, M + 1, R, IR(index));

}

void addition(int l, int r, int L, int R, int index, long long toAdd){
    if(l == L && r == R){
        seq[index].lazy_add += toAdd;
        return ;
    }
    int M = (L + R) / 2;
    push(index);
    if(r <= M)
        addition(l, r, L, M, IL(index), toAdd);
    else if(l > M) 
        addition(l, r, M + 1, R, IR(index), toAdd);
    else{
        addition(l, M, L, M, IL(index), toAdd);
        addition(M + 1, r, M + 1, R, IR(index), toAdd);
    }
    pull(index);
}
void pull(int index){
    seq[index].size = seq[IL(index)].size + seq[IR(index)].size;
    seq[index].sum = seq[IL(index)].real_sum() + seq[IR(index)].real_sum();
    seq[index].lazy_add = 0;
}
void push(int index){
    seq[IL(index)].lazy_add += seq[index].lazy_add;
    seq[IR(index)].lazy_add += seq[index].lazy_add;
    seq[index].lazy_add = 0; // Done

}
/*
8
11 14 6 2 3 19 36 8
99

*/