#include <iostream>
using namespace std;

int G[100][100] = {0};
int main(){
	int N, M;
	cin >> N >> M;
	for(int i = 0; i < M; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		G[u][v] = G[v][u] = 1;
	}
	int ans = 0;
	for(int a = 0; a < N; a++){
		for(int b = a+1; b < N; b++){
			for(int c = b+1; c < N; c++){
				if(G[a][b] && G[b][c] && G[c][a])
					ans++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
