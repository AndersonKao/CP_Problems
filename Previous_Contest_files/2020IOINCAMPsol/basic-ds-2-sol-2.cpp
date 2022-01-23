#include <iostream>
#include <priority_queue>
#include <algorithm>
using namespace std;
int N;
int seq[300005];
int dataseq[3];
set<int> S;
set<int> Spre;
set<int> Ssub;
int main(){
    cin >> N;
    
    for(int j = 0; j < 3; j++){
        cin >> dataseq[j];
    }
    sort(dataseq, dataseq + 3);
    Spre.insert(dataseq[0]);
    S.insert(dataseq[1]);
    Ssub.insert(dataseq[2]);
    
    cout << *(--Spre.end()) << " " << *(--Ssub.end()) << endl;
    for(int i = 1; i < N; i++){
        for(int j = 0; j < 3; j++){
            cin >> dataseq[i];
        }
        sort(dataseq, dataseq+3);
        set<int>::iterator itpre = --Ssub.end();
        set<int>::iterator itsub = --Ssub.end();
        int preCount = 0;
        int midCount = 0;
        int subCount = 0;
        for(int j = 0; j < 3; j++){
            if(dataseq[i] < *itpre){
                pre--;
            }else if(dataseq[i] > pre && dataseq[i] < *sub){
                
            }
        }
    }
    return 0;
}