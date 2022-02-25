// AC 2022-02-17 20:46:57
#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000
using LL = long long;
int K;
int N;
long long cost[20];
typedef struct 
{
    int id;
    vector<int> joblist;
    long long whenavail;
    long long lastschedule;
} person;
person personnel[5];
int cmp(person a, person b){
    if(a.lastschedule != b.lastschedule)
        return a.lastschedule < b.lastschedule;
    return a.id < b.id;
}
struct task{
    long long enterT;
    task(): enterT(-1){}
    task( long long s):  enterT(s){}
} ;
map<LL, int> idtoIndex;
queue<LL> pending[20];

void personnelinfor(int K){
    for (int i = 0; i < K; i++){
        cout << "id: " << personnel[i].id << " : ";
        for(auto e: personnel[i].joblist){
            cout << e << ", ";
        }
        cout << endl;
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int cnt = 1;
    while(cin >> N){
        if(N == 0)
            break;
        idtoIndex.clear();
        int id, TaskNum, start, period;
        for (int i = 0; i < N; i++){
            cin >> id >> TaskNum >> start >> cost[i] >> period;
            while(!pending[i].empty())
                pending[i].pop();
            while(TaskNum--){
                pending[i].emplace(start);
                start += period;
            }
            idtoIndex[id] = i;
        }
        cin >> K;
        int NofJ;
        for (int i = 0; i < K; i++){
            cin >> personnel[i].id >> NofJ;
            personnel[i].joblist.clear();
            personnel[i].joblist.resize(NofJ);
            for (int j = 0; j < NofJ; j++){
                cin >> personnel[i].joblist[j];
                personnel[i].joblist[j] = idtoIndex[personnel[i].joblist[j]];
            }
            personnel[i].whenavail = 0;
        }
        //personnelinfor(K);
        // start loop
        long long curtime = 0;
        bool end = false;
        while(!end){
            LL nextcurtime = LLONG_MAX;
            sort(personnel, personnel + K, cmp);
            for (int i = 0; i < K; i++){
                if(personnel[i].whenavail > curtime){
                    // busy working
                    nextcurtime = min(nextcurtime, personnel[i].whenavail); // 還在忙的話嘗試更新到他有空的時間
                    continue;
                }
                bool findJob = false;
                LL nextPossibleJobT = LLONG_MAX;
                for(auto &pid: personnel[i].joblist){
                    if(pending[pid].empty()) // no this type job
                        continue;
                    if(pending[pid].front() <= curtime){ // got a job
                        personnel[i].whenavail = curtime + cost[pid];
                        findJob = true;
                        pending[pid].pop();
                        break;
                    }else
                        nextPossibleJobT = min(nextPossibleJobT, pending[pid].front());
                }
                if(!findJob)
                    nextcurtime = min(nextcurtime, nextPossibleJobT); // 如果沒找到job的話，嘗試更新到他地一個可以遇到的Job時間
                else
                    nextcurtime = min(nextcurtime, personnel[i].whenavail);
            }
            curtime = nextcurtime;
            end = true;
            for (int i = 0; i < N; i++)
                if(!pending[i].empty()){
                    end = false;
                    break;
                }
        }
        for (int i = 0; i < K; i++)
            curtime = max(curtime, personnel[i].whenavail);
        cout << "Scenario " << cnt++ << ": All requests are serviced within " << curtime << " minutes.\n";
    }

    return 0;
}