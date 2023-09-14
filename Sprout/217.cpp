// AC 
#include <iostream>
using namespace std;
char str[505];
int main(){
    cin >> str;
    int index = 0;
    while(str[index] != '\0'){
        str[index] += 3;
        if(str[index] > 'z'){
            str[index] = str[index] - 'z' + 'a' - 1;
        }
        index++;
    }
    cout << str << endl;
}