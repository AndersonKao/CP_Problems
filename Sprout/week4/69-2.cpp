#include <iostream>
#include <algorithm>

using namespace std;

long long horses[10005][2];
long long enemy[10005];
long long horsefortest[10005];
void my_horse_sort(long long *,int N);
void enemy_sort(int N);
int compare(int N);
void finddata(int N,long long M){
    for(int i=0;i<N;i++)
        horsefortest[i] = horses[i][0] + M * horses[i][1];
}
void Swap(long long *a,long long *b){
    long long c = *a;
    *a = *b;
    *b = c;
}
int main()
{
    
    int T, N, K;
    cin >> T;
    while (T--)
    {
        cin >> N >> K;
        bool allzero = true;
        for (int i = 0; i < N; i++)
            cin >> horses[i][0] >> horses[i][1];
        for (int i = 0; i < N; i++)
            cin >> enemy[i];
        qsort(enemy,N,sizeof(long long));
        stable_sort(enemy, enemy+N);
        long long L = 0, R = 100000000;
        do{
            finddata(N,(L+R)/2);
            stable_sort(horsefortest,horsefortest+N);
            // cout << "Printing data\n";
            // for(int i=0;i<N;i++)
            //     cout << horsefortest[i] << endl;
            int ans = compare(N);
            if(ans>=K)
                R = (L+R)/2;
            else if(ans < K)
                L = (L+R)/2;
        }while(L<R);
        if(R != 100000000)
        cout << R << endl;
        else 
        cout << "-1\n";
    }
    return 0;
}
void enemy_sort(int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (enemy[j - 1] > enemy[j])
            {
                Swap(&enemy[j-1],&enemy[j]);
            }
            else
            {
                break;
            }
        }
    }
}
void my_horse_sort(long long *horses,int N)
{
    for (int i = 1; i < N; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (horses[j - 1] > horses[j] )
            {
                Swap(&horses[j-1],&horses[j]);
                Swap(&horses[j-1], &horses[j]);
            }
            else
            {
                break;
            }
        }
    }
}
int compare(int N){
    int index = 0, index2 = 0;
    int counts = 0;
    while (index < N)
    {
        if (horsefortest[index] > enemy[index2])
        {
            counts++;
            index2++;
        }
        index++;
    }
    return counts;
}