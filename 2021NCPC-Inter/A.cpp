#include <bits/stdc++.h>
using namespace std;

#define IL(X) ((X * 2) + 1)
#define IR(X) ((X * 2) + 2)
#define MAXN 100005
// lazy_tag put in sum version
// L = R -> leaf, [L, (L+R)/2] -> right child, [(L+R)/2+1, R] -> right child
// L, M is the range represented by current accessing node 

struct Node{
    long long sum;
    long long max;
    long long lazy_tag;
    int size;
};
int dataseq[MAXN];
Node seq[MAXN * 4 + 5];
void build(int l, int r, int L, int R, int index);
void modify(int l, int r, int L, int R, int index, long long Add);
long long QuerySum(int l, int r, int L, int R, int index);
long long QueryMax(int l, int r, int L, int R, int index);
void pull(int index);
void push(int index);

void pull(int index){
    seq[index].sum = seq[IL(index)].sum + seq[IR(index)].sum
    +seq[IL(index)].lazy_tag * seq[IL(index)].size + seq[IR(index)].lazy_tag * seq[IR(index)].size;
    seq[index].size = seq[IL(index)].size + seq[IR(index)].size;
    seq[index].max = max(seq[IL(index)].max, seq[IR(index)].max);
    seq[index].lazy_tag = 0;
}
void push(int index){
    seq[IL(index)].sum += seq[index].lazy_tag * seq[index].size;
    seq[IL(index)].lazy_tag += seq[index].lazy_tag;
    //seq[IL(index)].sum += seq[index].lazy_tag * seq[IL(index)].size;
    seq[IR(index)].lazy_tag += seq[index].lazy_tag;
    //seq[IR(index)].sum += seq[index].lazy_tag * seq[IR(index)].size;
    seq[index].lazy_tag = 0;
}

void build(int l, int r, int L, int R, int index){
    if(l == r){
        seq[index].sum = dataseq[l];
        seq[index].size = 1;
        seq[index].lazy_tag = 0;
        seq[index].max = dataseq[l];
        return; 
    }
    int M = (L + R) / 2;
    build(l, M, L, M, IL(index));
    build(M + 1, r, M + 1, R, IR(index));
    pull(index);
}

void modify(int l, int r, int L, int R, int index, long long Add){
    if(r < L || l > R)
        return;
    if(l == L && r == R){
        seq[index].lazy_tag += Add;
//        seq[index].sum += Add * seq[index].size;
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

long long QuerySum(int l, int r, int L, int R, int index){
    if(l > R || r < L)
        return 0;
    if(l == L && r == R){
        return seq[index].sum + seq[index].size * seq[index].lazy_tag;
    }
    int M = (L + R) / 2;
    push(index);
    pull(index);
    if(r <= M){
        return QuerySum(l, r, L, M, IL(index));
    }else if(l > M){
        return QuerySum(l, r, M + 1, R, IR(index));
    }else{
        return QuerySum(l, M, L, M, IL(index)) + 
        QuerySum(M + 1, r, M + 1, R, IR(index));
    }
}

int main(){
    int N, Q;
    int l, r;
    cin >> N;

    memset(dataseq, 0, sizeof(dataseq));
    memset(seq, 0, sizeof(seq));
    build(0, N - 1, 0, N - 1, 0);
    for (int i = 0; i < Q; i++)
    {
        cin >> l >> r;
        modify(l, r, 0, N - 1, 0, 1);
        cout << QuerySum(0, N - 1, 0, N - 1, 0) << endl;
    }

    return 0;
}