// AC 2019-10-20 23:32:24

#include <iostream>
#include <stdio.h>
#include <set>
#include <queue>
using namespace std;
const int arr[3] = {2, 3, 5};

int main(){
    set<long long> had;
    priority_queue<long long, vector<long long>, greater<long long> > pq;
    pq.push(1);
    had.insert(1);
    for (int i = 1;;i++){
        long long x = pq.top();
        pq.pop();
        //printf("The #%d ugly number is %lld\n", i, x);
        if(i == 1500){
            printf("The 1500'th ugly number is %lld.\n", x);
            break;
        }
        for (int j = 0; j < 3;j++){
            long long tmp = x * arr[j];
            if(!had.count(tmp)){
                had.insert(tmp);
                pq.push(tmp);
            }
            
        }
    }
}