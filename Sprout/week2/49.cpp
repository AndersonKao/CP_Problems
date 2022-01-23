// AC 2019/11/28 08:27:54
#include <iostream>
using namespace std;
int arr[100005][2];
int main(){
    int T,totar,toin,N,m,q,toask;
    cin >> T;
    while(T--){
        cin >> N >> m;
        for(int i=0;i<=N;i++){
            arr[i][0] = i;
            arr[i][1] = 1;
        }
        while(m--){
            cin >> totar >> toin;
            arr[toin][0] = totar;
            arr[totar][1] += arr[toin][1];
            int tmp = totar;
            while(arr[tmp][0] != tmp){
                arr[arr[tmp][0]][1] += arr[toin][1];
                tmp = arr[tmp][0];
            }
        }
        cin >> q;
        while(q--){
            cin >> toask;
            cout << arr[toask][1] << "\n";
        }

    }
    return 0;
}