// AC 	2020-08-10 15:14:59
#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>
#include <queue>
#include <cstring>
#include <cmath>

using namespace std;

#define INF 20000.0
#define point pair<double, double>
#define con pair<double, int> // first for distance, second for index

vector<point> Node;
vector<con> neigh[205];
vector<double> pathsmall;
int N;

double dis(point a, point b){
    double r1 = a.first - b.first , r2 = a.second - b.second; 
    return sqrt(r1 * r1 + r2 * r2);
}

int main(){
    int counter = 1;
    while(cin >> N){
        if(!N)
            return 0;
        // init
        queue<int> indexQ;
        pathsmall.clear();
        pathsmall.resize(N, INF);
        Node.clear();
        double x, y;
        for (int i = 0; i < 205; i++)
            neigh[i].clear();

        for (int i = 0; i < N; i++)
        {
            cin >> x >> y;
            Node.push_back(point(x, y));
        }
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(i != j){
                    neigh[i].push_back(con(dis(Node[i], Node[j]), j));
                }
            }
        }
        // setup finished

        priority_queue<con, vector<con>, less<con>> pq;
        pq.push(con(pathsmall[0] = 0, 0));
        while(pq.size()){
            con curIt = pq.top();
            pq.pop();
            for(auto it: neigh[curIt.second]){ // use curIt to relax
                double curdata = max(pathsmall[curIt.second], it.first);
                if(pathsmall[it.second] > curdata){
                    pathsmall[it.second] = curdata;
                    pq.push(con(pathsmall[it.second], it.second));
                }
            }
        }
        cout << "Scenario #" << counter++ << "\nFrog Distance = ";
        
        cout << fixed << setprecision(3) << pathsmall[1] << "\n\n";
        
    }
        return 0;
}