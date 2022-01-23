#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
int N, M, b1, b2;
vector<int> ANS;
int ANSdis = 0;
bool visited[2000005] = {false};
vector<int> neigh[200005];
bool restaurant[200005] = {0};
vector<int> Disseq;

queue<int> Visiting;
int main(){
    cin >> N >> M;
    // neigh.resize(N + 5);
    // res.resize(N + 5, false);
    Disseq.resize(N + 5, 0);
    for(int i = 0; i < M; i++){
        cin >> b1 >> b2;
        neigh[b2].push_back(b1);
    }
    cin >> M;
    for(int i = 0; i < M; i++){
        cin >> b1;
        restaurant[b1] = true;
    }
    Visiting.push(1);
    Disseq[1] = 0;
    visited[1] = true;
    // cout << "going to while";
    while(!Visiting.empty()){
        int curNode = Visiting.front();
        Visiting.pop();
        // cout << "Visiting " << curNode << "\n";
        if(restaurant[curNode]){
            // // cout << "Encounter " << curNode << "\n";
            // cout.flush();
            if(!ANSdis){
                ANSdis = Disseq[curNode];
                ANS.push_back(curNode);
            }else if (Disseq[curNode] == ANSdis){
                ANS.push_back(curNode);
            }
        }
        // cout << "adding neight\n";
        if(!neigh[curNode].empty())
            for(int it = 0; it < neigh[curNode].size(); it++){
                if(visited[neigh[curNode][it]]) continue;
                visited[neigh[curNode][it]] = true;
                Visiting.push(neigh[curNode][it]);
                Disseq[neigh[curNode][it]] = Disseq[curNode] + 1;
            }
    }
    // cout << "going to sort\n";
    sort(ANS.begin(), ANS.end());
    // cout << "sorted\n";
    if(ANS.size())
    for(int i = 0; i < ANS.size(); i++){
        cout << ANS[i] << (i == ANS.size()-1 ? '\n' : ' ');
    }
    else
        cout << "-1\n";

    return 0;
}