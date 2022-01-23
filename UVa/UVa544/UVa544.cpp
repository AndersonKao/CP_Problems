// AC 2020-08-11 14:51:41
#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>
#include <queue>
#include <cstring>
#include <cmath>
#include <map>

using namespace std;

#define INF 20000
#define con pair<int, int> // first for distance, second for index
map<string, int> nametoIndex;
vector<con> neigh[205];
vector<int> pathsmall;
int N, Q;


int main(){
    int counter = 1;

    while(cin >> N >> Q){
        if(!N && !Q)
            return 0;
        // init
        queue<int> indexQ;
        pathsmall.clear();
        pathsmall.resize(N, 0);
        nametoIndex.clear();
        for (int i = 0; i < 205; i++)
            neigh[i].clear();
        int curIndexCounter = 0;
        for (int i = 0; i < Q; i++)
        {
            string a, b;
            int weight;
            cin >> a >> b;
            if(!nametoIndex.count(a)){
                nametoIndex[a] = curIndexCounter++;
            }
            if(!nametoIndex.count(b))
                nametoIndex[b] = curIndexCounter++;
            cin >> weight;
            neigh[nametoIndex[a]].push_back(con(weight, nametoIndex[b]));
            neigh[nametoIndex[b]].push_back(con(weight, nametoIndex[a]));
        }
        string stName, endName;
        cin >> stName >> endName;
        // setup finished

        priority_queue<con, vector<con>, less<con>> pq;
        pq.push(con(pathsmall[nametoIndex[stName]] = INF, nametoIndex[stName]));
        while(pq.size()){
            con curIt = pq.top();
            pq.pop();
            for(auto it: neigh[curIt.second]){ // use curIt to relax
                int curdata = min(pathsmall[curIt.second], it.first);
                if(pathsmall[it.second] < curdata){
                    pathsmall[it.second] = curdata;
                    pq.push(con(pathsmall[it.second], it.second));
                }
            }
        }
        // for (int i = 0; i < N; i++){
        //     cout << "Index " << i << ": " << pathsmall[i];
        //     if(i == nametoIndex[stName])
        //         cout << " This is starter";
        //     else if(i == nametoIndex[endName])
        //         cout << " This is ender";
        //     cout << endl;
        // }
            cout << "Scenario #" << counter++ << "\n";

        cout << fixed << setprecision(3) << pathsmall[nametoIndex[endName]];
        cout << " tons\n\n";
    }
        return 0;
}