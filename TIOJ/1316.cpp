/* TIOJ 1316.cpp segment tree */
#include <queue>
#include <random>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace  std;

#define IL(X) ((X * 2) + 1)
#define IR(X) ((X * 2) + 2)
#define MAXN 8005
// lazy_tag put in sum version
// L = R -> leaf, [L, (L+R)/2] -> right child, [(L+R)/2+1, R] -> right child
struct Node{
    long long max;
    long long lazy_tag;
    int size;
};
int N;
int dataseq[MAXN];
Node seq[MAXN * 4 + 5];
void build(int l, int r, int L, int R, int index);
void modify(int l, int r, int L, int R, int index, long long Add);
long long Query(int l, int r, int L, int R, int index);
void pull(int index);
void push(int index);

void pull(int index){
    seq[index].max = max(seq[IL(index)].max, seq[IR(index)].max);
    seq[index].size = seq[IL(index)].size + seq[IR(index)].size;
    seq[index].lazy_tag = 0;
}
void push(int index){
    seq[IL(index)].lazy_tag += seq[index].lazy_tag;
    seq[IL(index)].max += seq[index].lazy_tag;
    seq[IR(index)].lazy_tag += seq[index].lazy_tag;
    seq[IR(index)].max += seq[index].lazy_tag;
    seq[index].lazy_tag = 0;
}

void build(int l, int r, int L, int R, int index){
    if(l == r){
        seq[index].max = dataseq[l];
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
        seq[index].max += Add;
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
        return seq[index].max;
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
void printseg(){
    int li = 1;
    for (int i = 0; i < 4 * N; i++){
        if(i == li){
            printf("\n");
            li = li * 3;
        }
        printf("i=%d: d:%d m:%d t=%d | ", i, dataseq[i], seq[i].max, seq[i].lazy_tag);
    }
    printf("\n--------------------\n");
}
int chips[8005];
int Lm[4005], Rm[4005];

#define QUESTION
//#define SELFGEN
int main()
{
    scanf("%d", &N);
    memset(chips, 0, sizeof(chips)); 
#ifdef SELFGEN
    srand(time(NULL));
    N = rand() % 1000 + 3000;
    printf("gen N = %d\n", N);
    for (int i = 1; i <= N; i++){
        int hash = rand() % (2 * N);
        while(chips[hash]){
            hash = rand() % (2 * N);
        }
        chips[hash] = i;
        while(chips[hash])
            hash = rand() % (2 * N);
        chips[hash] = i;
    }
    printf("dummy fin\n");
    /*
    for (int i = 0; i < 2 * N;i++){
        printf("%d ", chips[i]);
    }
    printf("\n");
    */

#endif


#ifdef QUESTION

    std::fill(Lm, Lm + N + 1, -1);
    std::fill(Rm, Rm + N + 1, 0);
    for (int i = 0; i < 2 * N; i++){
        scanf("%d", chips+i);
        if(Lm[chips[i]] != -1)
            Rm[chips[i]] = i;
        else
            Lm[chips[i]] = i;
    }
#endif
    memset(dataseq, 0, sizeof(dataseq));
    build(0, 2 * N - 1, 0, 2 * N - 1, 0);
#ifndef QUESTION
    printf("%d\n", Query(0, 2 * N - 1, 0, 2 * N - 1, 0));
    printseg();
    modify(0, 5, 0, 2 * N - 1, 0, 10);
    printseg();
    modify(4, 10, 0, 2 * N - 1, 0, 5);
    printseg();
    printf("%d\n", Query(16, 16 , 0, 2 * N - 1, 0));
#endif
#ifdef QUESTION
    
    int ans = 0;
    for (int i = 0; i < 2*N; i++)
    {
        int chip = chips[i];
        if(i != Rm[chip])
            continue;
        int maxIn = Query(Lm[chip], Rm[chip], 0, 2 * N - 1, 0);
        if(maxIn < 2){
            ans++;
            modify(Lm[chip], Rm[chip], 0, 2 * N - 1, 0, 1);
        }
    }
    printf("%d\n", ans);
#endif
    
        return 0;
}