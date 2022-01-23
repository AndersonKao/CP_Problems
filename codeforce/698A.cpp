// AC Sep/03/2020 15:24UTC+8
#include <iostream>
#include <cstring>
using namespace std;
int daycase[105];
int ans[105][4]; // each day min rest
#define INT_MAX 10000
void dp()
{
}
int main()
{
    int N;
    cin >> N;
    memset(ans, INT_MAX, sizeof(ans));
    for (int i = 0; i < 3; i++)
        ans[0][i] = 0;
    for (int i = 1; i <= N; i++)
    {
        cin >> daycase[i];
    }
    
    for (int i = 1; i <= N; i++)
    {
        ans[i][0] = INT_MAX;
        for (int j = 0; j < 3; j++){
            ans[i][0] = min(ans[i][0], ans[i - 1][j] + 1);
        }
        switch(daycase[i]){
            case 0:
                ans[i][1] = ans[i][2] = INT_MAX;
                break;
            case 1:
                ans[i][1] = min(ans[i-1][0], ans[i-1][2]);
                ans[i][2] = INT_MAX;
                break;
            case 2:
                ans[i][2] = min(ans[i-1][0], ans[i-1][1]);
                ans[i][1] = INT_MAX;
                break;
            case 3:
                ans[i][1] = min(ans[i-1][0], ans[i-1][2]);
                ans[i][2] = min(ans[i-1][0], ans[i-1][1]);
                break;
        }
    }
    int tureans = INT_MAX;
    for (int i = 0; i < 3; i++){
        tureans = min(tureans, ans[N][i]);
    }
    // for (int i = 0; i <= 2; i++){
    //     for (int j = 0; j <= N; j++){
    //         cout << ans[j][i] << " ";
    //     }
    //     cout << endl;
    // }
        cout << tureans << endl;
    return 0;
}