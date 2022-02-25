#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000
using LL = long long;
struct {
    int id;
    int quantum;
    long long period;
    long long cost;
    long long nextenter;
    int jobdput;
} taskdata[20];
struct 
{
    int id;
    vector<int> joblist;
    bool avail;
    long long whenavail;
    long long lastschedule;
} personnel[5];
struct task{
    long long enterT;
    task(): enterT(-1){}
    task( long long s):  enterT(s){}
} ;
queue<task> pending[20];

int findsb(int taskid, int K){
    long long lastschedule = LONG_LONG_MAX;
    int ansp = K;
    for (int i = 0; i < K; i++){
        if(personnel[i].avail == false)
            continue;
        for(auto &u: personnel[i].joblist){
            if(u == taskdata[taskid].id){
                if(personnel[i].lastschedule < lastschedule || (personnel[i].lastschedule == lastschedule && personnel[i].id < ansp)){
                    ansp = i;
                    lastschedule = personnel[i].lastschedule;
                }
            }
        }
    }
    return (ansp == K ? -1 : ansp);
}
int findnext(int N, int K){
    // 找時間最近且有人做
    int todoid = MAXN;
    LL todostart = LLONG_MAX;
    int assign = -1;
    for (int i = 0; i < N; i++){
        if(pending[i].empty()) continue;
        if(pending[i].front().enterT < todostart){
            if(findsb(i, K)!= -1){
                todoid = i;
                todostart = pending[i].front().enterT;
            }
        }
    }
    return (todoid == MAXN ? -1 : todoid);
}

int nextavail(int K){
    int nextavailp = K;
    LL mintime = LLONG_MAX;
    for (int i = 0; i < K; i++){
        if(!personnel[i].avail && personnel[i].whenavail < mintime){
            mintime = personnel[i].whenavail;
            nextavailp = i;
        }
    }
    return (nextavailp == K ? -1 : nextavailp);
}
int nextcoming(int N){
    LL mintime = LLONG_MAX;
    for(int i = 0; i < N; i++){
        if(taskdata[i].jobdput == taskdata[i].quantum)
            continue;
        mintime = min(mintime, taskdata[i].nextenter);
    }
    return (mintime == LLONG_MAX ? -1 : mintime);
}
void jobinfor(int N){
    for (int i = 0; i < N; i++){
#ifdef debug
        cout << "id: " << taskdata[i].id << " quantum: " << taskdata[i].quantum << " jobdput: " << taskdata[i].jobdput << endl;
        cout << "nextenter T: " << taskdata[i].nextenter << " cost: " << taskdata[i].cost << " period: " << taskdata[i].period;
        cout << " Nums in queue: " << pending[i].size() << endl;
#endif
    }
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int K;
    int N;
    int cnt = 1;
    while(cin >> N){
        if(N == 0)
            break;
        for (int i = 0; i < N; i++){
            cin >> taskdata[i].id >> taskdata[i].quantum >> taskdata[i].nextenter >> taskdata[i].cost >> taskdata[i].period;
            taskdata[i].jobdput = 0;
        }
        cin >> K;
        for (int i = 0; i < K; i++){
            cin >> personnel[i].id;
            personnel[i].joblist.clear();
            int NofJ;
            cin >> NofJ;
            personnel[i].joblist.resize(NofJ);
            for (int j = 0; j < NofJ; j++){
                cin >> personnel[i].joblist[j];
            }
            personnel[i].avail = true;
            personnel[i].whenavail = 0;
        }
        // init
        for (int i = 0; i < N; i++){
            while(!pending[i].empty())
                pending[i].pop();
        }
        for (int i = 0; i < N; i++){
            if(taskdata[i].nextenter == 0){
                pending[i].emplace(0);
                taskdata[i].nextenter += taskdata[i].period;
                taskdata[i].jobdput++;
            }
        }
        // start loop
        long long curtime = 0;
        while(true){
            int taskid ;
            while((taskid = findnext(N, K))!= -1){
                // get task id and sb. can do this
                int p = findsb(taskid, K);
#ifdef debug
                cout << "find task " << taskid << " assigned to person " << p << endl;
#endif
                personnel[p].avail = false;
                personnel[p].lastschedule = max(personnel[p].whenavail, pending[taskid].front().enterT);
                personnel[p].whenavail = personnel[p].lastschedule + taskdata[taskid].cost;
                pending[taskid].pop();
            }
            int nextavailp = nextavail(K);
            LL nextjobT= nextcoming(N);
#ifdef debug
            cout << "next avail person " << nextavailp << endl;
#endif
            if(nextavailp == -1 && nextjobT == -1)
                break;
            if(nextavailp == -1 || nextjobT < personnel[nextavailp].whenavail){
                curtime = nextjobT;
            }else if(nextjobT == -1 || nextjobT >= personnel[nextavailp].whenavail){
                personnel[nextavailp].avail = true;
                curtime = personnel[nextavailp].whenavail;
            }
#ifdef debug
            cout << " current time to " << curtime << endl;
#endif
            for(int i = 0; i < K; i++){
                if(personnel[i].whenavail <= curtime){
                    personnel[i].avail = true;
                }
            }
            for (int i = 0; i < N; i++){
                while(taskdata[i].nextenter <= curtime && taskdata[i].jobdput < taskdata[i].quantum){
                    pending[i].emplace(taskdata[i].nextenter);
                    taskdata[i].nextenter += taskdata[i].period;
                    taskdata[i].jobdput++;
                }
            }
#ifdef debug
            jobinfor(N);
#endif
        }
        cout << "Scenario " << cnt++ << ": All requests are serviced within " << curtime << " minutes.\n";
    }

    return 0;
}