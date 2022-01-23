#include <iostream>
using namespace std;
long horses[105][2];
long enemy[105];
void my_horse_sort(int N);
void enemy_sort(int N);
bool compare(int N, int K);
void duplicate(int N);
void printmyhorse(int N){
    cout << "print horses now\n";
    for(int i=0;i<N;i++)
    {
         cout << horses[i][0] << endl;
    }   
}
void Swap(long *a,long *b){
    int c = *a;
    *a = *b;
    *b = c;
}
int main()
{
    int T, N, K, win;
    bool flag;
    cin >> T;
    while (T--)
    {
        cin >> N >> K;
        bool win = 0, flag = false;
        long long hortotal = 0, enehortotal = 0;
        bool allzero = true;
        for (int i = 0; i < N; i++)
        {
            cin >> horses[i][0] >> horses[i][1];
            hortotal += horses[i][0];
        }
        for (int i = 0; i < N; i++)
        {
            cin >> enemy[i];
            enehortotal += enemy[i];
        }
        my_horse_sort(N);
        enemy_sort(N);
        for(int i = 0; i< N;i++)
            cout << enemy[i] << endl;
        for (int i = 0; i < N; i++)
            if (horses[i][1] != 0)
            {
                allzero = false;
                break;
            }
        if (allzero)
        {
            if (compare(N, K))
            {
                cout << "1\n";
                return 0;
            }
            else
            {
                cout << "-1\n";
                return 0;
            }
        }
        int counters = 0;
        while (!flag)
        {
            if (compare(N, K))
            {
                flag = true;
                cout << counters << endl;
                break;
            }
            duplicate(N);
            my_horse_sort(N);
            //printmyhorse(N);
            counters++;
        }
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
void my_horse_sort(int N)
{
    for (int i = 1; i < N; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (horses[j - 1][0] > horses[j][0] )
            {
                Swap(&horses[j-1][0], &horses[j][0]);
                Swap(&horses[j-1][1], &horses[j][1]);
            }
            else
            {
                break;
            }
        }
    }
}
bool compare(int N, int K)
{
    int index = 0, index2 = 0;
    int counts = 0;
    while (index < N)
    {
        if (horses[index][0] > enemy[index2])
        {
            counts++;
            index2++;
        }
        index++;
        if (counts >= K)
        {
            return true;
        }
    }
    return false;
}
void duplicate(int N)
{
    for (int i = 0; i < N; i++)
        horses[i][0] = horses[i][0] + horses[i][1];
}