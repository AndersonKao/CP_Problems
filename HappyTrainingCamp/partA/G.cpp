#include <bits/stdc++.h>
using namespace std;

int T;

char str[1000001];
char tmpstr[1000001];

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    while(cin >> str){
        
        if(strcmp(str, "END") == 0)
            break;
        else if (strcmp(str, "1") == 0)
        {
            cout << "1\n";
            continue;
        }
        unsigned digit = strlen(str);
        unsigned ans = 2;
        sprintf(tmpstr, "%d", digit);
        unsigned newdigit = strlen(tmpstr);

        while(newdigit != digit)
        {
            digit = newdigit;
            sprintf(tmpstr, "%d", digit);
            newdigit = strlen(tmpstr);
            ans++;
        }
        cout << ans << endl;
    }

    return 0;
}