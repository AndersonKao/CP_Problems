#include <bits/stdc++.h>
using namespace std;

string gph[110];
bool isv[110][110];
int n, m, x, y;
int way[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main() {
    cin >> n >> m;
    for (int i=0; i<n; i++) cin >> gph[i];
    cin >> x >> y;
    int dd = -1;
    for (int j=0; j<2; j++) {
        for (int i=0; i<4; i++) {
            if (gph[x+way[i][0]][y+way[i][1]] == '.' && (i+2)%4 != dd) {
                dd = i;
                break;
            }
        }
        while (gph[x+way[dd][0]][y+way[dd][1]] == '.') {
            x += way[dd][0];
            y += way[dd][1];
        }
    }
    cout << x << " " << y << endl;
}