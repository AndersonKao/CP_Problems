// AC
// UTC+0 2022-05-15 16:43:34
// WA
// 如果要推，要一路找到合法的格子，推到他身上，而非身後沒格子就不推
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back
#define REP(i, n) for (int i = 0; i < (int)n; i++)

template <typename T>
using vec = vector<T>;
using piii = tuple<int, int, int>;

#define F 0
#define L 1
#define B 2
#define R 3
#define T 4
#define D 5

vec<vec<int>> di = {
    {1, 0, 0},
    {0, 0, 1},
    {-1, 0, 0},
    {0, 0, -1},
    {0, 1, 0},
    {0, -1, 0}
};

int N;

vec<vec<vec<vec<char>>>> cube;
vec<vec<vec<bool>>> inQ;
vec<vec<vec<bool>>> dis;

bool invalid(vec<char>& lattice){
    int cnt = 0;
    bool dot = false;
    vec<bool> colors(26, false);
    for (char &color : lattice)
    {
//        cout << color << ", ";
        if (color != 'e' && color != '.' && !colors[(color - 'A')])
        {
            cnt++;
            colors[(color - 'A')] = true;
        }
        dot = dot || (color == '.');
    }

    return cnt > 1 || dot;
}

void pushin(int i, int j, int k, queue<piii> &Q)
{
    vec<char> &lattice = cube[i][j][k];
    dis[i][j][k] = true;

    REP(f, 6){
        int ni = i + di[f][0], nj = j + di[f][1], nk = k + di[f][2];
        while(!(ni < 0 || ni >= N || nj < 0 || nj >= N || nk < 0 || nk >= N) && dis[ni][nj][nk])
            ni = ni + di[f][0], nj = nj + di[f][1], nk = nk + di[f][2];

        if (ni < 0 || ni >= N || nj < 0 || nj >= N || nk < 0 || nk >= N)
            continue;
        //if (lattice[f] == 'e' || dis[ni][nj][nk])
        if (lattice[f] == 'e' || dis[ni][nj][nk])
            continue;
        cube[ni][nj][nk][f] = lattice[f];
        if(!inQ[ni][nj][nk] && invalid(cube[ni][nj][nk])){
            Q.emplace(ni, nj, nk);
            inQ[ni][nj][nk] = true;
        }
    }
}

int main()
{
    int ans;
    while(cin >> N){
        if(!N)
            break;
        ans = N * N * N;
        cube.clear();
        cube.resize(N, vec<vec<vec<char>>>(N, vec<vec<char>>(N, vec<char>(6, 'e'))));
        inQ.clear();
        inQ.resize(N, vec<vec<bool>>(N, vec<bool>(N, false)));
        dis.clear();
        dis.resize(N, vec<vec<bool>>(N, vec<bool>(N, false)));
        string str;
        REP(j, N)
        {
            int idl, idr, idc;
            REP(i, 6)
            {
                cin >> str;
                REP(k, N)
                {
                    switch (i)
                    {
                    case F:
                        idl = 0;
                        idr = j;
                        idc = k;
                        break;
                    case L:
                        idl = N - 1 - k;
                        idr = j;
                        idc = 0;
                        break;
                    case B:
                        idl = N-1;
                        idr = j;
                        idc = N - 1 - k;
                        break;
                    case R:
                        idl = k;
                        idr = j;
                        idc = N-1;
                        break;
                    case T:
                        idl = N - 1 - j;
                        idr = 0;
                        idc = k;
                        break;
                    case D:
                        idl = j;
                        idr = N-1;
                        idc = k;
                        break;
                    default:
                        break;
                    }
                    cube[idl][idr][idc][i] = str[k];
                }
            }
        }
        queue<piii> invalidQ;
        /*
        REP(f, 6){
            REP(i, N){
                REP(j, N){
                    REP(k, N){
                        cout << cube[i][j][k][f] << " ";
                    }
                    cout << endl;
                }
                cout << "-----" << endl;
            }
            cout << "--------------";
            cout << endl
                 << endl;
        }
        */
        REP(i, N)
        {
            REP(j, N){
                REP(k, N){
                    if(invalid(cube[i][j][k])){
                        invalidQ.emplace(i, j, k);
                        inQ[i][j][k] = true;
                        //cout << "inv: " << i << ", " << j << ", " << k << endl;
                    }
                }
            }
        }
        
        while(!invalidQ.empty()){
            int i, j, k;
            tie(i, j, k) = invalidQ.front();
//            cout << i << ", " << j << ", " << k << endl;
            invalidQ.pop();
            inQ[i][j][k] = false;
            if(invalid(cube[i][j][k])){
                pushin(i, j, k, invalidQ);
                ans--;
            }
        }
        cout << "Maximum weight: " << ans << " gram(s)" << endl;
    }
    return 0;
}