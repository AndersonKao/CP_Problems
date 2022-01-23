#include <bits/stdc++.h>
using namespace std;

#define IL(X) ((X * 2) + 1)
#define IR(X) ((X * 2) + 2)
#define MAXN 500005
// lazy_tag put in sum version
// L = R -> leaf, [L, (L+R)/2] -> right child, [(L+R)/2+1, R] -> right child
// L, M is the range represented by current accessing node

int N;
struct Node{
    long long sum;
    long long max;
    int size;
};
short dataseq[MAXN];
Node seq[MAXN * 4 + 5];
void build(int l, int r, int L, int R, int index);
void modify(int l, int r, int L, int R, int index, long long Add);
long long Query(int l, int r, int L, int R, int index);


void pull(int index){
    seq[index].size = seq[IL(index)].size + seq[IR(index)].size;
    seq[index].max = max(seq[IL(index)].max, seq[IR(index)].max);
    seq[index].sum = seq[IL(index)].sum + seq[IR(index)].sum;
}

void build(int l, int r, int L, int R, int index){
    if(r < L || l > R)
        return;
    if(l == r){
        seq[index].sum = dataseq[l];
        seq[index].size = 1;
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
    if(l == r){
        seq[index].sum += Add;
        if(seq[index].sum >= N)
        {
            printf("mod %d = %d ", l,  seq[index].sum);
            seq[index].sum %= N;
            printf("to %d\n", seq[index].sum);
        }
        seq[index].max = seq[index].sum;
        return;
    }
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
    if(r < L || l > R)
        return 0;
    if(l == L && r == R){
        return seq[index].sum;
    }
    int M = (L + R) / 2;
        return Query(l, M, L, M, IL(index)) + 
        Query(M+1, r, M + 1, R, IR(index));
    pull(index);
}
long long QueryMax(int l, int r, int L, int R, int index){
    if(r < L || l > R)
        return 0;
    if(l <= L && r >= R){
        return seq[index].max;
    }
    int M = (L + R) / 2;
        return max(QueryMax(l, r, L, M, IL(index)) , 
        Query(l, r, M + 1, R, IR(index)));
}
int main(){

    int  Q;
    int l, r;
    cin >> N;
    cin >> Q;

    memset(dataseq, 0, sizeof(dataseq));
    memset(seq, 0, sizeof(seq));
    build(0, N - 1, 0, N - 1, 0);
    for (int i = 0; i < Q; i++)
    {
        cin >> l >> r;
        l--;
        r--;
        modify(l, r, 0, N - 1, 0, 1);
        cout << Query(0, N - 1, 0, N - 1, 0) << endl;
        cout << "Max be " << 0 << " to " << N-1 << endl;
        cout << QueryMax(0, N - 1, 0, N - 1, 0) << endl;
        cout << "Max be " << 0 << " to " << N/2 << endl;
        cout << QueryMax(0, N/2, 0, N - 1, 0) << endl;
        cout << "Max be " << N/2 + 1 << " to " << N-1 << endl;
        cout << QueryMax(N/2 + 1, N - 1, 0, N - 1, 0) << endl;
    }

    return 0;
}