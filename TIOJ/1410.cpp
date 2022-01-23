// AC 
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N;
vector<int> inseq;
vector<int> sequit;
int main(){
    std::ios_base::sync_with_stdio(false);
    cin >> N;
    inseq.resize(N);
    sequit.resize(N);
    for(int i = 0; i < N; i++){
        cin >> inseq[i] >> sequit[i];
    }
    sort(inseq.begin(), inseq.end());
    sort(sequit.begin(), sequit.end());
    int curAns, FinalAns, InIndex, OutIndex;
    curAns = FinalAns = InIndex = OutIndex = 0;
    while(InIndex < N){
        if(inseq[InIndex] <= sequit[OutIndex]){
            curAns++;
            InIndex++;
        }else{
            curAns--;
            OutIndex++;
        }
        FinalAns = max(FinalAns, curAns);
    }
    cout << FinalAns << "\n";
    return 0;
}