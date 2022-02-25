#include <bits/stdc++.h>
//#define debug
using namespace std;
using PII = pair<int, int>;
int T;
int grid[1001][1001];
int back[1001][1001];
PII vec[1000001];
bool possi(int test, int n, int m, int h, int w){

#ifdef debug
    cout << "testing: " << test << endl;
#endif

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            
            back[i][j] = back[i - 1][j] + back[i][j - 1] - back[i-1][j-1];
            if(grid[i][j] > test)
                back[i][j]++;
#ifdef debug
            cout << back[i][j] << (j == m ? "\n" : " ");
#endif
        }
    }

    for (int i = 0; i + h <= n ; i++){
        for (int j = 0; j + w <= m ; j++){
            int sum = back[i + h][j + w]  - back[i][j+w] - back[i + h][j]+ back[i][j];
#ifdef debug
            cout << i + 1 << ", " << j + 1 << " are good\n";
            cout << "sum: " << sum << endl;
#endif
            if(sum <= (h * w) / 2 ){
                return true;
            }
        }
    }
    return false;
}
void solve(){
    int n, m, h, w;
    cin >> n >> m >> h >> w;
    memset(back, 0, sizeof(back));
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            cin >> grid[i][j];
        }
    }
    int l = 1;
    int r = n * m;
    while(l < r){
#ifdef debug
        cout << l << ", " << r << endl;
#endif
        int mid = (l + r) / 2;
        if(possi( mid, n, m, h, w)){
            r = mid;
        }else{
            l = mid + 1;
        }
    }
#ifdef debug
    cout << l << endl;
#endif
    cout << r << endl;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    solve();

    return 0;
}