#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;


int matrix[105][105];
bool exists[105];
int main(){
    int T;
    cin >> T;
    int N,cases = 1;
    int trace, rerow,recol;
    bool flag;
    while(T--){
        cin >> N;
        for(int i =0;i< N;i++){
            for(int j = 0; j < N; j++){
                cin >> matrix[i][j];
            }
        }
        trace = rerow = recol = 0;
        for(int i = 0; i < N; i++){
            trace += matrix[i][i];
        }
        flag = false;
        for(int i =0;i< N;i++){
            memset(exists,0,sizeof(exists));
            
            for(int j = 0; j < N; j++){
                if(exists[matrix[i][j]]){
                    rerow++;
                    break;
                }else{
                    exists[matrix[i][j]] = true;
                }
            }
        }
        for(int i =0;i< N;i++){
            memset(exists,0,sizeof(exists));
            for(int j = 0; j < N; j++){
                if(exists[matrix[j][i]]){
                    recol++;
                    break;
                }else{
                    exists[matrix[j][i]] = true;
                }
            }
        }
        printf("Case #%d: %d %d %d\n", cases++, trace, rerow,recol);
    }

    return 0;
}