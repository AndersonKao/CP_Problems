// AC 2022-05-21 06:44:48
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for (int i = 0; i < (int)n;i++)
template <typename T>
using vec = vector<T>;
vec<vec<vec<bool>>> hasTrain;
vec<vec<int>> f;
const int MAXT = 250;
int main()
{
    int N;
    int T;
    int cnt = 1;
    while (cin >> N)
    {
        if(!N)
            break;
        cin >> T;
        hasTrain.clear();
        hasTrain.resize(N, vec<vec<bool>>(T + 1, vec<bool>(2)));
        f.clear();
        f.resize(N, vec<int>(T + 1, MAXT));
        f[0][0] = 0;
        vec<int> dis(N - 1);
        REP(i, N -1)
            cin >> dis[i];
        int M1, M2;
        cin >> M1;
        REP(i, M1){
            int st;
            cin >> st;
            if(st <= T)
                hasTrain[0][st][0] = true;
        }
        cin >> M2;
        REP(i, M2)
        {
            int st;
            cin >> st;
            if(st <= T)
                hasTrain[N-1][st][1] = true;
        }
        for (int i = 1; i < N; i++){
            for (int t = 0; t <= T; t++)
            {
                if(t - dis[i-1] >= 0)
                    hasTrain[i][t][0] = hasTrain[i - 1][t - dis[i - 1]][0];
            }
        }
        for (int i = N-2; i >= 0; i--){
            for (int t = 0; t <= T; t++)
            {
                if(t - dis[i] >= 0)
                    hasTrain[i][t][1] = hasTrain[i + 1][t - dis[i]][1];
            }
        }
        for (int t = 1; t <= T; t++){
            for (int i = 0; i < N; i++){
                f[i][t] = min(f[i][t], f[i][t - 1] + 1);
                if(i - 1 >= 0 && t - dis[i-1] >= 0 && hasTrain[i-1][t - dis[i-1]][0])
                    f[i][t] = min(f[i][t], f[i - 1][t - dis[i - 1]]);
                if(i + 1 < N && t - dis[i] >= 0 && hasTrain[i+1][t - dis[i]][1])
                    f[i][t] = min(f[i][t], f[i + 1][t - dis[i]]);
            }
        }
        cout << "Case Number " << cnt++ << ": ";
        if (f[N - 1][T] == 250)
            cout << "impossible";
        else
            cout << f[N - 1][T];
        cout << endl;
    }

    return 0;
}