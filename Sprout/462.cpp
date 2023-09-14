// AC 2020/08/12 10:43:29
#include <iostream>
using namespace std;
char str[1005];
char newstr[1005];
char opera[10];
int main(){
    int T, step;
    cin >> str;
    cin >> T;
    int length = 0;
    while(str[length] != '\0'){
        length++;
    }
    while(T--){
        cin >> opera;
        cin >> step;
        if(opera[0] == 'u'){
            step %= 26;
            for(int i = 0; i < length; i++){
                if(str[i] + step > 'z'){
                  str[i] += (step - (int)('z' - 'a' + 1));
                }else{
                    str[i] += step;
                }
                
            }
        }else if(opera[0] == 'd'){
            step %= 26;
            for(int i = 0; i < length; i++){
                str[i] -= step;
                if(str[i] < 'a'){
                    str[i] += ('z'-'a' + 1);
                }
            }
        }else if(opera[0] == 'l'){
            step %= length;
            for(int i = 0; i < length; i++){
                newstr[(i - step + length) % length] = str[i];
            }
            for(int i = 0; i < length; i++){
                str[i] = newstr[i];
            }
        }else if(opera[0] == 'r'){
            step %= length;
            for(int i = 0; i < length; i++){
                newstr[(i + step) % length] = str[i];
            }
            for(int i = 0; i < length; i++){
                str[i] = newstr[i];
            }
        }
        str[length] = '\0';
        cout << str << endl;
    }

    return 0;
}