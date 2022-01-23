// AC 2020-07-13 13:51:52
#include <iostream>
#include <utility>
#include <stack>
using namespace std;
#define animal pair<long long, int> 
#define INT32_MAX 2147483647
int N;

animal ele[80005];
stack<pair<long long, int>> ST;
int main(){
    int data, index;
    long long ans = 0;
    cin >> N;
    index = N - 1;
    ST.push(pair<long long ,int>(INT32_MAX, N+1));
    for(int i = 0; i < N; i++){
        cin >> data;
        ele[i] = animal(data, i + 1);
    }
    while(!ST.empty() && index >= 0){
        // cout << "Hei: " << ST.top().first << "Index: " << ST.top().second << '\n';
        while(ST.top().first < ele[index].first){
            ST.pop();
        }
        ans += (abs(ele[index].second - ST.top().second) - 1);
        ST.push(ele[index]);
        index--;
        // cout << "Ans: " << ans << '\n';
    }
    // while(ST.size() > 1){
    //     cout << "Hei: " << ST.top().first << "Index: " << ST.top().second << '\n';
        
    //     ans += (N - ST.top().second);
    //     ST.pop();
    //     cout << "Ans: " << ans << '\n';
    // }
    cout << ans << '\n';
    // cout << ans << '\n';

    return 0;
}