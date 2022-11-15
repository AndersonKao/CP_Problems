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
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
vec<vec<int>> bcc;
const int maxn = 10000;
int D[maxn], L[maxn];
int timestamp = 1;
vec<int> adj[maxn];
stack<int> st;
void DFS(int v, int fa) { //call DFS(v,v) at first
    D[v] = L[v] = timestamp++; //timestamp > 0
    st.emplace(v);

    for (int w:adj[v]) {
        if( w==fa ) continue;
        if ( !D[w] ) { // D[w] = 0 if not visited
            DFS(w,v);
            L[v] = min(L[v], L[w]);
            if (L[w] >= D[v]) { // 找到割點!
            	int x;
                bcc.push_back({});
                do {
                    x = st.top(); st.pop();
                    bcc.back().emplace_back(x);
                } while (x!=v);
                st.push(v); // 把割點擺回去
            }
        }
        L[v] = min(L[v], D[w]);
    }

    return ;
} // 用完我 stack 要記得清乾淨!!

int main(){
	yccc;		
	int n, m;
	cin >> n>> m;
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		adj[u].eb(v), adj[v].eb(u);
	}
	DFS(1, 1);
	for(int i = 0; i < bcc.size(); i++){
		cout << "bcc " << i << " :";
		for(int u : bcc[i]){
			cout << " " << u;
		}
		cout << endl;
	}
	return 0;
}

