#include <bits/stdc++.h>
using namespace std;

#define INF 105
int dis[100][100];

bool appear[100];

void printG(){

    for (int i = 0; i < 10; i++){
            cout << "i = " << i << ": ";
        for (int j = 0; j < 10; j++){
                cout << dis[i][j] << " ";
        }
        cout << endl;
    }
}
void solve(){
    fill(appear, appear+ 100, false);
    for (int i = 0; i < 100; i++)
        fill(dis[i], dis[i] + 100, INF);
    int a, b;
    int num = 0;
    while(cin >> a >> b){
        if(a == 0 && b == 0)
            break;
    //    cout << "get a, b = " << a << " " << b << endl;
        a--;
        b--;
        dis[a][b] = 1;
        if(!appear[a])
        {
            dis[a][a] = 0;
            appear[a] = true;
            num++;
        }
        if(!appear[b]){
            dis[b][b] = 0;
            appear[b] = true;
            num++;
        }
    }
    for (int m = 0; m < 100; m++){
        for (int i = 0; i < 100; i++){
            for (int j = 0; j < 100; j++){
                if(dis[i][m] + dis[m][j] < dis[i][j] )
                    dis[i][j] = dis[i][m] + dis[m][j];
            }
        }
    }
    long long sum = 0;
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++){
            if(dis[i][j] != INF)
                sum += dis[i][j];
        }
    }
    cout << sum /(double)(num * (num-1));
}

int main(){

    int a, b;
    int cnt = 1;
    cout << fixed << setprecision(3);
    while(true){
        if(cin.peek() == '0'){
            cin >> a >> b;
            if(a == 0 && b == 0)
                break;
        }
        cout << "Case " << cnt++ << ": average length between pages = ";
        solve();
        cout << " clicks\n";
        cin.get();
    }
    return 0;
}