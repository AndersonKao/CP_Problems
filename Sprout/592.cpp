// AC
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
int main(){
    int T;
    char str[205];
    char ansStr[205];
    int AnsStrong = -1;
    cin >> T;
    while(T--){
        cin >> str;
        int strong = 0;
        int Len = strlen(str);
        for (int i = 1; i < Len; i++){
            if(str[i] == str[i-1])
                continue;
            if(isupper(str[i]) && isupper(str[i-1])){
                strong++;
            }else if(islower(str[i]) && islower(str[i-1])){
                strong++;
            }else if(isdigit(str[i]) && isdigit(str[i-1])){
                strong++;
            }else if(str[i] != str[i-1]){
                strong += 2;
            }
        }
        if(strong > AnsStrong){
            strcpy(ansStr, str);
            AnsStrong = strong;
        }
    }
    cout << ansStr << endl;
    return 0;
}