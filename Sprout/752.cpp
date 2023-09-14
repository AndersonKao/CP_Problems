// AC 2020/05/15 22:36:26
#include <iostream>
#include <cassert>
#define MAXN 100000
#define MAXM 1000000
using namespace std;
typedef struct person{
    int count;
    int *loved_begin;
}person;
int storage[MAXM];
person all_people[MAXN];
int pairs[MAXM][2];
int now_cnt[MAXN] = {0};
void prepare(int n, int m, person *all_people, int *storage){
    // input
    for(int i=0; i<m; i++)
        cin >> pairs[i][0] >> pairs[i][1];
    
    // initialization 
    for(int i=0; i<n; i++)
        all_people[i].count = 0;
    
    // calculate_count
    for(int i=0; i<m; i++)
        all_people[pairs[i][0]].count++;\
    // calculate start
    int now_start = 0;
    for(int i=0; i<n; i++){
        all_people[i].loved_begin = storage+now_start;
        now_start += all_people[i].count;
    }
    // push element into storage
    for(int i=0; i<m; i++){
        int be_loved = pairs[i][0], to_love = pairs[i][1];
        (all_people[be_loved].loved_begin)[now_cnt[be_loved]++] = to_love;
    }
    // destroy the elements
    for(int i=0; i<m; i++)
        pairs[i][0] = pairs[i][1] = 0;
}
void print(int n, int m, person *All_People, int *store){
    for(int i = 0;i < n; i++){
        if(All_People[i].count == 0)
            continue;
        cout << i << ": ";
        for(int j = 0; j < All_People[i].count; j++){
            cout << (All_People[i].loved_begin)[j]; //  *(All_People[i].loved_begin + j)
            if(j != All_People[i].count - 1)
                cout << " ";
        }
        cout << endl;
    }
}
int main(){
    int n, m;
    cin >> n >> m;
    prepare(n, m, all_people, storage);
    print(n, m, all_people, storage);
    return 0;
}