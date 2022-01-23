#include <iostream>
#include <cstring>
#include <string>
using namespace std;
bool put[100005];
int main(){
    int T;
    cin >> T;
    string str;
    char ans[100005];
    int x;
    while(T--){
        bool flag = true;
        memset(put, 0, sizeof(put));
        memset(ans, 0, sizeof(ans));
        int len;
        cin >> str;
        cin >> x;
        len = str.length();
        for (int i = 0; i < len; i++)
        {
            if (str[i] == '0'){
                if(i - x >= 0){
                    if(!put[i-x]){
                        put[i - x] = true;
                        ans[i - x] = '0';
                    }else if(ans[i-x] != '0'){
                        flag = false;
                        break;
                    }
                }
                if(i + x < len){
                    if(!put[i+x]){
                        put[i + x] = true;
                        ans[i + x] = '0';
                    }else if(ans[i-x] != '0'){
                        flag = false;
                        break;
                    }
                }
            }
        }   
        
        for (int i = 0; i < len; i++){
            if(str[i] == '1'){
                if(i + x < len && !put[i+x]){
                    continue;
                }else if(i - x >= 0 && !put[i-x]){
                    continue;
                }
                flag = false;
                break;
            }
        }   
        if (!flag)
        {
            // cout << "break2\n";
            cout << "-1\n";
            continue;
        }
        for (int i = 0; i < len; i++){
            
            if(!put[i]){
                ans[i] = '1';
            }
        }
        ans[len] = '\0';
        cout << ans << '\n';
    }
    return 0;
}