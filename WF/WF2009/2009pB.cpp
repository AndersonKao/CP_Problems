#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define eb emplace_back
#define debug(x) cout << #x << ": " << x << endl;
using pvv = pair<vector<int>, vector<int>>;
int N, G, U, B;
int toid(string str){
	int id = 0;
	if(str[0] == 'g'){
		id += N;
	}
	int off = 0;
	for(int i = 1; i < str.length(); i++){
		off*=10;
		off += (str[i] - '0');	
	}
	return id + off - 1;
}
vector<vector<int>> myG;
vector<int> curval;
vector<char> gatetype;
int errgate, errtype;
vector<pair<vector<int>, vector<int>>> unittest;
vector<int> simuOrder;
vector<bool> f;
int fcnt;
void DFS(int u){
	f[u] = true;
	for(int&v: myG[u]){
		if(f[v])
			continue;
		DFS(v);
	}
	simuOrder.eb(u);
}
void topo(){
	simuOrder.clear();
	f.resize(myG.size());
	fill(f.begin(), f.end(), false);
	for(int i = 0; i < myG.size(); i++){
		if(f[i])
			continue;	
		DFS(i);
	}		
//	reverse(simuOrder.begin(), simuOrder.end());
#ifdef Dtopo
	cout << "simuOrder: ";
	for(int u: simuOrder){
		cout << u << " ";
	}
	cout << endl;
#endif
}
bool simulate(int b){
	const vector<int>& in = unittest[b].F;
	const vector<int>& desire = unittest[b].S;
	fill(curval.begin(), curval.end(), -1);
	for(int i = 0; i < N; i++){
		curval[i] = in[i];
	}
	for(int i = 0; i < simuOrder.size(); i++){
		int u = simuOrder[i];
		if(u < N)
			continue;
#ifdef Dsimu
		debug(u);
#endif
		if(N <= u && u < N+G){
#ifdef Dsimu
			debug(gatetype[u-N]);
#endif
			if(gatetype[u - N] == 'a'){
				curval[u] = 1;
				for(int&v : myG[u]){
					curval[u] &= curval[v];
				}
			}
			else if(gatetype[u - N] == 'o'){
				curval[u] = 0;
				for(int&v : myG[u]){
					curval[u] |= curval[v];
				}
			}
			else if(gatetype[u - N] == 'x'){
				curval[u] = curval[myG[u][0]] ^ curval[myG[u][1]];
			}
			else if(gatetype[u - N] == 'n'){
				curval[u] = curval[myG[u][0]] ^1;
			}
			if(u - N == errgate){
				if(errtype == 0){
					curval[u] = curval[u] ^ 1;
				}
				else if(errtype == 1){
					curval[u] = 0;
				}
				else if(errtype == 2){
					curval[u] = 1;
				}
			}
		}
		else{
			curval[u] = curval[myG[u][0]];
		}
	}	
	bool ans = true;
	for(int i = 0; i < U; i++){
		if(curval[N + G + i] != desire[i])
			ans = false;
	}
#ifdef Dsimu
	for(int i = 0; i < N+G; i++)
		cout << curval[i] << " ";
	cout << endl;
	for(int i = 0; i < U; i++)
		cout << curval[N+G+i] << " ";
	cout << endl;
	for(int i = 0; i < U; i++)
		cout << desire[i] << " ";
	cout << endl;
	cout << (ans ? "good" : "fail") << endl;	
#endif
	return ans;
}
int main(){
	int caseN = 1;
	while(cin >> N >> G >> U){
		if(N == 0 && G == 0 && U == 0)
			break;
		myG.clear();
		myG.resize(N+G+U);	
		curval.resize(N+G+U);
		gatetype.resize(G);
		for(int i = 0; i < G; i++){
			cin >> gatetype[i];		
			string str;
			getline(cin, str);
			stringstream ss(str);
			while(ss >> str){
				int id = toid(str);
				myG[N+i].eb(id);	
			}
		}
		for(int i = 0; i < U; i++){
			int gid;
			cin >> gid;	
			myG[N+G+i].eb(N+gid-1);	
		}
		cin >> B;
		unittest.clear();
		unittest.resize(B);
		for(int i = 0; i < B; i++){
			pvv& Pv = unittest[i];
			Pv.F.resize(N), Pv.S.resize(U);
			for(int j = 0;j < N; j++){
				cin >> Pv.F[j];
			}
			for(int j = 0;j < U; j++){
				cin >> Pv.S[j];
			}
		}
		topo();
		errgate = errtype = -1;
		bool haveErr = false;
#ifdef Dsimu
		cout << "first simu: \n";
#endif
		for(int i = 0; i < B; i++){
			if(simulate(i) == false){
				haveErr = true;
			}
		}
		if(haveErr){
			int errnum = 0;
			int ansgate, anserr;
			for(int i = 0; i < G; i++){
				errgate = i;
				for(int errt = 0; errt < 3; errt++){
					errtype = errt;
#ifdef Derr
					debug(errgate);
					debug(errtype);
#endif
					/* 0-> invert output, 1-> always 0, 2->always 1*/
					int hErr = false;
					for(int i = 0; i < B; i++){
						if(simulate(i) == false){
							hErr = true;
						}
					}	
					if(hErr == false){
						ansgate = errgate;
						anserr = errtype;
						errnum++;
					}
				}
			}
			cout << "Case " << caseN++ << ": ";
			if(errnum != 1){
				cout << "Unable to totally classify the failure\n";
			}else{
				cout << "Gate " << ansgate+1 << " is failing; output ";			
				if(anserr == 0){
					cout << "inverted\n";	
				}
				else if(anserr == 1){
					cout << "stuck at 0\n";	
				}
				else if(anserr == 2){
					cout << "stuck at 1\n";	
				}
			}
		}	
		else{
			cout << "Case " << caseN++ << ": ";
			cout << "No faults detected\n";
		}	
	}
	return 0;
}
