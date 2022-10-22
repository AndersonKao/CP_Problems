#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;

struct Kosaraju{
    int NodeNum;
    vector<vector<int>> G;
    vector<vector<int>> GT;
    stack<int> st;
    vector<bool> visited;
    vector<int> scc;
    int sccNum;

    void init(int N){
        NodeNum = N;
        G.clear();
        G.resize(N);
        GT.clear();
        GT.resize(N);
        while(!st.empty())
            st.pop();
        visited.clear();
        visited.resize(N, false);
        scc.clear();
        scc.resize(N);
        sccNum = 0;
    }
    void addEdge(int u, int v){
        G[u].emplace_back(v);
        GT[v].emplace_back(u);
    }
    void DFS(bool isG, int u, int sccID = -1){
        visited[u] = true;
        vector<vector<int>> &dG = (isG ? G : GT);
        for(int v: dG[u])
        {
            if(!visited[v]){
                DFS(isG, v, sccID);
            }
        }
        if(isG){
            st.push(u);
        }
        else{
            scc[u] = sccID;
        }
    }
    void run(){
        fill(al(visited), false);
        for (int i = 0; i < NodeNum; i++){
            if(!visited[i])
                DFS(true, i);
        }
        fill(al(visited), false);
        while(!st.empty()){
            if(!visited[st.top()])
                DFS(false, st.top(), sccNum++);
            st.pop();
        }
    }

    vector<vector<int>> reduceG(){ //call after run
        vector<vector<int>> reG;
        reG.resize(sccNum);
        for (int i = 0; i < NodeNum; i++){
            for(int w: G[i]){
               if(scc[i] == scc[w])
                   continue;
               reG[scc[i]].emplace_back(scc[w]);
            }
        }
        return reG;
    }
};


// 2-SAT (A or B) and (C or ^B) and (E) = true : O(n) = O(v+e)
/* common terms edge building
A : ^A -> A, which means A must be true 
not A : A -> ^A , which means A must be false
A or B : ^A -> B, ^B -> A 
not A or B : A -> B, ^B -> ^A
not A or not B : A -> ^B, B -> ^A
A xor B : A -> ^B, ^A -> B, B -> ^A, ^B -> A.
*/
struct twoSAT{
    Kosaraju mK;
    int n;
    vector<bool> value;
    void init(int nterm){
        this->n= nterm;
        mK.init(nterm * 2);
    }
    void addEdge(int u, int v){
        mK.addEdge(u, v);
    }
    void run(){
        mK.run();
    }
    bool satisfy(){ // assume A = i, then ^A = i+nterm
        value.clear();
        value.resize(n);
        for (int i = 0; i < n; i++){
            if(mK.scc[i] == mK.scc[i+n]){
                return false;
            }
            value[i] = mK.scc[i] > mK.scc[i + n];
        }
        return true;
    } 
};

int main(){
	int n, m;
	cin >> n >> m;
	twoSAT mT;
	mT.init(m);
	for(int i = 0; i < n; i++){
		char op1, op2;
		int top1, top2;	
		cin >> op1 >> top1 >> op2 >> top2;
		top1--, top2--;
		if(op1 == '+'){
			if(op2 == '+'){
				mT.addEdge(top1 + m, top2);	
				mT.addEdge(top2 + m, top1);	
			}
			else{
				mT.addEdge(top1 + m, top2 + m);	
				mT.addEdge(top2, top1);	
			}
		}
		else{
			if(op2 == '+'){
				mT.addEdge(top1, top2);	
				mT.addEdge(top2 + m, top1 + m);	
			}
			else{
				mT.addEdge(top1, top2 + m);	
				mT.addEdge(top2, top1 + m);	
			}
		}
	}		
	mT.run();
	/*
	for(int u = 0; u < 2*m; u++){
		cout << u << ": ";
		for(int v: mT.mK.G[u]){
			cout << v << " ";
		}
		cout << endl;
	}
	for(int u = 0; u < 2*m; u++){
		cout << "scc of " << u << " = ";
		cout << mT.mK.scc[u] + 1 << "\n";
	}
	*/
	if(mT.satisfy()){
		for(int u = 0; u < m; u++){
			cout << (mT.value[u] ? "+" : "-") << " ";
		}
	}
	else{
		cout << "IMPOSSIBLE\n";
	}
	
	return 0;
}

