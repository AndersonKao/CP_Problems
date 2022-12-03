// AC 2020-02-04 15:56
#include <iostream>
#include <vector>
using namespace std;
vector<int> seq[10005];
bool pro[10005] = {true};

void dothis(int index){
    if(!pro[index])
        return ;
    pro[index] = false;
    int limit = seq[index].size();
    for(int i=0;i<limit;i++){
        dothis(seq[index][i]);
    }
}

int main(){

    int N,M,L,Q;
    cin >> N >> M >> L >> Q;
    for(int i=0;i<=N;i++)
        pro[i] = true;
    for(int i=0;i<M;i++){
        int a ,b;
        cin >> a >> b;
        seq[a].push_back(b);
    }
    for(int i=0;i<L;i++){
        int x;
        cin >> x;
        dothis(x);
    }
    
    for(int i=0;i<Q;i++){
        int y;
        cin >> y;
        if(pro[y])
            cout << "YA~~\n";
        else
            cout << "TUIHUOOOOOO\n";
    }
    return 0;
}