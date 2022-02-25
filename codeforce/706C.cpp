// AC Sep/03/2020 16:51UTC+8
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
#define LL long long
#define MAX INT64_MAX - 100
LL cost[100005];
string str[2][2];
LL ans[2][2];
string reverse_String(string &str){
    string tore = "";
    int len = str.length();
    // tore.resize(len);
    for (int i = 0; i < len; i++){
        tore += str[len-i-1];
    }
    return tore;
}
int main(){
    int N;
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> cost[i];
    }
    memset(ans, 0, sizeof(ans));
    ans[0][0] = 0;
    ans[0][1] = cost[0];

    for (int i = 0; i < N; i++){
        int cur = i & 1;
        cin >> str[cur][0];
        str[cur][1] = reverse_String(str[cur][0]);
        // cout << "reserve: " << str[cur][1] << endl;
        if(i == 0){
            // cout << ans[0][0] << " " << ans[0][1] << endl;
            continue;
        }
        ans[cur][0] = ans[cur][1] = MAX;
        
        for (int k = 0; k < 2; k++)
        {
            if(ans[cur^1][k] == MAX)
                continue;
            if (str[cur][0].compare(str[cur ^ 1][k]) >= 0)
            {
                // cout << "str: " << str[cur][0] << " do >= " << str[cur ^ 1][k] << endl;
                ans[cur][0] = min(ans[cur][0], ans[cur ^ 1][k]);
            }else
            {
                // cout << "str: " << str[cur][0] << " don't >= " << str[cur ^ 1][k] << endl;
            }
            
        }
        for (int k = 0; k < 2; k++){
            
            if(ans[cur^1][k] == MAX)
                continue;
            if (str[cur][1].compare(str[cur ^ 1][k]) >= 0) {
                
                // cout << "str: " << str[cur][1] << " do >= " << str[cur ^ 1][k] << endl;
                ans[cur][1] = min(ans[cur][1], ans[cur ^ 1][k] + cost[i]);
            }else
            {
                // cout << "str: " << str[cur][1] << " don't >= " << str[cur ^ 1][k] << endl;
            }
            
        }
        // cout << "ex:  ";
        // cout << ans[cur^1][0] << " " << ans[cur^1][1] << endl;

        // cout << "now: ";
        // cout << ans[cur][0] << " " << ans[cur][1] << endl;

    }
    LL ANS = min(ans[(N - 1) & 1][0], ans[(N - 1) & 1][1]);
    if(ANS == MAX){
        cout << "-1\n";
        return 0;
    }
    cout << ANS << endl;
    return 0;
}