#include <iostream>
#include <vector>

using namespace std;

int super[150005];

int find(int a){
    if(super[a] == a)
        return a;
    return super[a] = find(super[a]);
}
void Union(int a, int b){
    super[find(a)] = find(b);
}

bool sameSet(int a, int b){
    return find(a) == find(b);
}

int T;
int N;
int main(){
    scanf("%d", &N);
    scanf("%d", &T);
    for (int i = 1; i <= 3*N; i++)
    {
        super[i] = i;
    }
    int ANS = 0;
    while (T--)
    {
        int op;
        int X, Y;
        scanf("%d %d %d", &op, &X, &Y);
        if (X < 1 || X > N || Y < 1 || Y > N){
            ANS++;
            continue;
        }
        if (op == 1)
        {
            if (sameSet(X, Y + N) || sameSet(Y, X + N))
            {
                ANS++;
            }
            else
            {
                Union(X, Y);
                Union(X + N, Y + N);
                Union(X + 2 * N, Y + 2 * N);
            }
        }else{
            if(sameSet(X,Y) || sameSet(Y, X + N))
            {
                ANS++;
            }
            else{
                Union(X, Y + N);
                Union(X + N, Y + 2*N);
                Union(X + 2*N, Y);
            }
        }
    }
    cout << ANS << endl;
    return 0;
}