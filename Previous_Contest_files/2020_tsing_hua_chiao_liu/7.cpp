#include <iostream>
#include <algorithm>
using namespace std;
double seq[20000][2];
int main(){
    int N, a, b;
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> seq[i][0] >> seq[i][1];
    }
    int sad = 0;
    double sum = 0;
    sum += min(seq[0][1], seq[0][0]);
    for(int i = 1; i < N; i++){
        int minone = min(seq[i][0], seq[i][1]);
        int maxone = max(seq[i][0], seq[i][1]);
        if(minone >= sum / i){
            sum += minone;
        }else if(maxone >= sum / i){
            sum += maxone;
        }else{
            sad++;
            sum += minone;
        }
    }
    cout << sad << endl;
    return 0;
}