#include <tuple>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define IL(X) ((X * 2) + 1)
#define IR(X) ((X * 2) + 2)
#define MAXN 500005
// lazy_tag put in val version
// add tag
// tag += tag
// val += tag

    struct Node{
        int val;
        int lazy_tag;
    };
    int dataseq[MAXN];
    Node seq[MAXN * 4 + 5];
    void pull(int index){
        seq[index].val = max(seq[IL(index)].val, seq[IR(index)].val);
    }
    void push(int index){
        seq[IL(index)].lazy_tag += seq[index].lazy_tag;
        seq[IL(index)].val += seq[index].lazy_tag;
        seq[IR(index)].lazy_tag += seq[index].lazy_tag;
        seq[IR(index)].val += seq[index].lazy_tag;
        seq[index].lazy_tag = 0;
    }

    void build(int L, int R, int index){
        if(L == R){
            seq[index].val = dataseq[L];
            seq[index].lazy_tag = 0;
            return; 
        }
        int M = (L + R) / 2;
        build(L, M, IL(index));
        build(M + 1, R, IR(index));
        pull(index);
    }

    void modify(int l, int r, int L, int R, int index, long long Add){
        if(l == L && r == R){
            seq[index].lazy_tag += Add;
            seq[index].val += Add;
            return;
        }
        printf("%d %d\n", l, r);
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
            return seq[index].val;
        }
        int M = (L + R) / 2;
        push(index);
        if(r <= M){
            return Query(l, r, L, M, IL(index));
        }else if(l > M){
            return Query(l, r, M + 1, R, IR(index));
        }else{
            return max(Query(l, M, L, M, IL(index)), 
            Query(M + 1, r, M + 1, R, IR(index)));
        }

    }

int N, K;
int main(){
    scanf("%d %d", &N, &K);
    std::fill(dataseq, dataseq + N + 1, 0);
    build(1, N, 0);
    int l, r;
    vector<tuple<int, int, int>> V;
    for (int i = 0; i < N; i++){
        scanf("%d %d", &l, &r);
        V.emplace_back(r - l + 1, l, r);
        modify(l, r, 1, N, 0, 1);
    }
    sort(V.begin(), V.end());
    for(auto u: V){
        printf("%d %d %d\n", get<0>(u), get<1>(u), get<2>(u));
    } 

    return 0;
}
