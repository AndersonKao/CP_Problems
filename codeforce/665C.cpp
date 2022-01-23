// AC Feb/05/2020 17:39UTC+8
#include <iostream>
#include <string>
using namespace std;
 void change(char l,char r,char & tc){
    while((l!= '\0' && tc == l) || (tc != '\0' && tc == r)){
        tc++;
        if(tc > 'z')
            tc = 'a';
    }
}
int main(){
 
    string str;
    cin >> str;
    int limit = str.length();
    if(str[0] == str[1]){
        change('\0',str[2],str[1]);
    }
 
    for(int i=1;i<limit-1;i++){
        if(str[i] == str[i-1]){
            change(str[i-1],str[i+1],str[i]);
        }
    }
    if(str[limit-1] == str[limit-2]){
        change(str[limit-2],'\0',str[limit-1]);
    }
    cout << str << "\n";
    return 0;
}