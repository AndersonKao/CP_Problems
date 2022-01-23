
// Sample code to perform I/O:
#include <iostream>
using namespace std;
int seq[100005];
int seats[100005];
int Find[100005];

int main(){
    int N, M, K;
    int Ans = 0;
    cin >> N >> M >> K;
    for(int i = 1; i <= N; i++)
        cin >> seq[i];
    for(int i = 1; i <= M; i++){
        seats[i] = K;
        Find[i] = i;
    }
    int i;
    for(i = 1; i <= N; i++){
        if(seats[seq[i]] > 0)
            seats[seq[i]]--;
        else{
            while(seats[Find[seq[i]]] == 0){
                Find[seq[i]]++;
                if(Find[seq[i]] > M)
                    Find[seq[i]] = 1;
                if(Find[seq[i]] == seq[i])
                    break;
            }
            if(Find[seq[i]] == seq[i])
                break;
            seats[Find[seq[i]]]--;
            Ans++;
        }
    }
    Ans += N - i + 1;
    cout << Ans << '\n';
    return 0;
}

// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail


// Write your code here
