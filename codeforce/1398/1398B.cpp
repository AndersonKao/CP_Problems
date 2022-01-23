#include <iostream>
#include <string>
#include <queue>
using namespace std;
int T;
string str;
int seq[105];
priority_queue<int> pq;
int main(){
    cin >> T;
    while (T--)
    {
        /* code */
        cin >> str;
        int counter = 0;
        int index = 0;
        for(int i = 0; i < str.length(); i++){
            if(str[i] == '1')
                counter++;
            else{
                if(counter != 0){
                    pq.push(counter);
                    counter = 0;
                }
            }
        }
        int ans = 0;
        if(counter != 0)
            pq.push(counter);
        while(!pq.empty()){
            ans += pq.top();
            pq.pop();
            if(!pq.empty())
                pq.pop();
        }
        cout << ans << endl;
    }
    
    return 0;
}