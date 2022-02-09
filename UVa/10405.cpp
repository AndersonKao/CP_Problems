#include <bits/stdc++.h>
using namespace std;
    int ans[1001][1001];

int main(){
    string str1, str2;
    while(getline(cin, str1)){
        getline(cin, str2);
        for (int i = 0; i <= str1.length(); i++){
            for (int j = 0; j <= str2.length(); j++){
                ans[i][j] = 0;
            }
        }
        for (int i = 1; i <= str1.length(); i++)
        {
            for (int j = 1; j <= str2.length(); j++)
            {
                if(str1[i-1] == str2[j-1])
                    ans[i][j] = ans[i - 1][j - 1] + 1;
                else
                    ans[i][j] = max(ans[i - 1][j], ans[i][j - 1]);
            }
        }
        cout << ans[str1.length()][str2.length()] << endl;
    }
    return 0;
}

// abcdgh
// aghbce
// 