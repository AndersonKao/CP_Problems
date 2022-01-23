#include <iostream>
#include <string>
#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 105;
string filenames[maxn];
int main(){
    
    int N;
    while(scanf("%d",&N)){
        int M = 0;
        for(int i=0;i<N;i++){
            cin >> filenames[i];
            M = M > filenames[i].length() ? M : filenames[i].length();
        }
        sort(filenames,filenames+N);
        for(int i=0;i<60;i++)
            printf("-");
        printf("\n");
        
    }


    return 0;
}