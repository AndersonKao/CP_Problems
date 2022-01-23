#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;
struct vertex{
    pair<int, int> status;
    vertex(int a, int b){
        status = pair<int, int>(a, b);
    }
};
vector<vertex> vertices;
vector<vector<int>> G;
vector<int> Edges;
map<pair<int, int>, int> M;
int main(){
    int Ca, Cb, target;
    queue<vertex> Q;
    while(cin >> Ca >> Cb >> target){
        vertex u(Ca, Cb);
    }
    return 0;
}