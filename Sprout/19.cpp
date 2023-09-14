#include <iostream>
#include <stack>
using namespace std;
int seq[100006];
int main(){
    int T;
    cin >> T;
    stack<int> TrainStack;
    while(T--){
        while(!TrainStack.empty())
            TrainStack.pop();
        int N, counter = 1, Index = 0;

        cin >> N;
        for(int i = 0; i < N; i++){
            cin >> seq[i];
        }

        while(Index != N){
            if(!TrainStack.empty() && TrainStack.top() == seq[Index]){
                TrainStack.pop();
                Index++;
            }else{
                if(counter > N)
                    break;
                TrainStack.push(counter++);
            }
        }
        
        if(Index == N)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
    return 0;
}