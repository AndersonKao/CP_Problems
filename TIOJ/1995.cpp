// AC 	2020-09-16 14:42:11
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define lo(x, y) 31 - __builtin_clz(y - x + 1)

#define MAXN 2500000
#define MAXQ 1000006
// #define TEST
struct Query{
    int l, r;
};
// int seq[MAXN];
int maxseq[MAXN];
Query Qseq[MAXQ];
bool done[MAXQ] = {false};
// bitset<MAXQ> done;
int cmp(Query &a, Query &b)
{
    return (a.r - a.l + 1) < (b.r - b.l + 1);
}
int Qlen(Query & a){
    return a.r - a.l + 1;
}
int main(){
    #ifdef TEST
        freopen("in.txt", "r", stdin);
    #endif
    int N, Q, l, r;
    scanf("%d %d", &N, &Q);
    for (int i = 0; i < Q; i++){
        scanf("%d %d", &(Qseq[i].l), &(Qseq[i].r));
        Qseq[i].l--;
        Qseq[i].r--;
    }
    #ifdef TEST
        for (int i = 0; i < Q; i++){
            printf("%d %d\n", Qseq[i].l, Qseq[i].r);
        }
    #endif
    // sort(Qseq, Qseq + Q, cmp);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &maxseq[i]);
    }
    for(int i = 0; (1 << i) <= N; i++){
        if(i > 0){
            for (int j = 0; j + (1 << i) <= N; j++){
                maxseq[j] = max(maxseq[j], maxseq[j + (1 << (i - 1))]);
            }
        }
        // printf("curLg: %d, i = %d\n ", (int)(log(Qlen(Qseq[index])) / log(2)), i);
        // log(Qseq[index].r - Qseq[index].l + 1) / log(2)
        for (int index = 0; index < Q; index++){
            if (!done[index] && (int)lo(Qseq[index].l, Qseq[index].r) == i)
            {
                Qseq[index].l = max(maxseq[Qseq[index].l], maxseq[Qseq[index].r - (1 << i) + 1]);
                done[index] = 1;
                #ifdef TEST
                    printf("i now = %d\n", i);
                    printf("ansof: %d is %d\n", index, Qseq[index].l);
                #endif
            }
        }
        // printf("end of i: %d\n", i);
    }
    for (int i = 0; i < Q; i++){
        printf("%d\n", Qseq[i].l);
    }
    // printf("here\n");
    return 0;
}