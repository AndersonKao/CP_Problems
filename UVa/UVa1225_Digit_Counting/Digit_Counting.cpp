// AC 2019-10-21 13:49:29
#include <iostream>
#include <cctype>
#include <string>
#include <cstring>
#include <stdio.h>
using namespace std;
#define _for(i, a, b) for(int i=(a);i<b;i++)
int main(){
    int T;
    cin >> T;
    int ar[T];
    _for(i,0,T)
        cin >> ar[i];
    int table[10001][10];
    char str[6];
    _for(i,1,10001){
        sprintf(str, "%d", i);
        if(i>1){
            _for(k,0,10){
            table[i][k] = table[i - 1][k];
            }
        }
        _for(k,0,6){
            if(str[k] == '\n'){
                break;
            }
            if(str[k]=='0'){
                table[i][0]++;
            }else if(str[k]=='1'){
                table[i][1]++;
            }else if(str[k]=='2'){
                table[i][2]++;
            }else if(str[k]=='3'){
                table[i][3]++;
            }else if(str[k]=='4'){
                table[i][4]++;
            }else if(str[k]=='5'){
                table[i][5]++;
            }else if(str[k]=='6'){
                table[i][6]++;
            }else if(str[k]=='7'){
                table[i][7]++;
            }else if(str[k]=='8'){
                table[i][8]++;
            }else if(str[k]=='9'){
                table[i][9]++;
            }
        }
        /*for(int k=0;k<10;k++){
            cout << table[i][k] << " ";
            }
            cout << endl;*/
    }
   // cout << "tohere" << endl;
    _for(i,0,T){
        int j = ar[i];
        //cout << "running" << i << endl;
        for(int k=0;k<10;k++){
            cout << table[j][k];
            if(k!=9)
                cout << " ";
        }
            cout << endl;
    }
    
    

    return 0;
}