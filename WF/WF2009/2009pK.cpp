#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define eb emplace_back
#define debug(x) cout << #x << ": " << x << endl;
using ll = long long;
const ll INF = numeric_limits<ll>::max() / 3;
struct node{
	string str;
	int rlen;
	int rid;
	int rnd; // from or to
	int sid;
	node(){}
	node(string str, int rlen, int i, int a, int b){
		this->str = str;
		this->rlen = rlen;
		rid = i, rnd = a, sid = b;
	}
};

vector<vector<pair<string, string>>> rules;
vector<vector<pair<vector<int>, vector<int>> >> rulesubid;
// [Len][rid].F[subj];
// 0 len reserve for start, end
int main(){
	int caseN = 1;
	string start, end;
	while(cin >> start){
		if(start == ".")
			break;
		cin >> end;
		int N;		
		cin >> N;
		rules.clear();
		rules.resize(21);
		rulesubid.clear();
		rulesubid.resize(21);
		for(int i = 0; i < N; i++){
			string st, to;
			cin >> st >> to;
			rules[st.length()].eb(st, to);
		}
		vector<node> allstr;
		rulesubid[0].resize(1);
		rulesubid[0][0].F.resize(start.length());
		rulesubid[0][0].S.resize(end.length());
		for(int i = 0; i < start.length(); i++){
			allstr.eb(start.substr(i), 0, 0, 0, i);
		}	
		for(int i = 0; i < end.length(); i++){
			allstr.eb(end.substr(i), 0, 0, 1, i);
		}	
		for(int i = 1; i < rules.size(); i++){
			rulesubid[i].resize(rules[i].size());
			for(int k = 0; k < rules[i].size(); k++){
				string & from = rules[i][k].F, &to = rules[i][k].S;
				rulesubid[i][k].F.resize(from.length());
				rulesubid[i][k].S.resize(to.length());
				for(int j = 0; j < from.length(); j++){
					allstr.eb(from.substr(j), i, k, 0, j);
				}
				for(int j = 0; j < to.length(); j++){
					allstr.eb(to.substr(j), i, k, 1, j);
				}
			}
		}
		sort(allstr.begin(), allstr.end(), [](node&a, node& b){
			if(a.str.length() != b.str.length())
				return a.str.length() < b.str.length();
			return a.str < b.str;
		});
		int idcnt = 0;
		vector<int> ids(allstr.size());
		for(int i = 0; i < allstr.size(); i++){
			string& str = allstr[i].str;
			if(i > 0 && str != allstr[i-1].str)
				idcnt++;
			int rlen = allstr[i].rlen;
			int rid = allstr[i].rid, rnd = allstr[i].rnd, sid = allstr[i].sid;
			if(rnd == 0){
				rulesubid[rlen][rid].F[sid] = idcnt;
			}
			else{
				rulesubid[rlen][rid].S[sid] = idcnt;
			}
			ids[i] = idcnt;
#ifdef Dallstr
			printf("%s id: %d, rlen: %d, rid: %d, rnd %d, sid %d\n",  str.c_str(),idcnt, rlen, rid, rnd, sid);
#endif
		}
		int curL = 0, curR;	
		int Gbase, Gsize, pGbase, pGsize;
		vector<vector<ll>> G[2];
		int Gid = 0;
		int ansBase;
		while(curL < allstr.size() && allstr[curL].str.length() <= start.length()){
			curR = curL;
			int curLen = allstr[curL].str.length();
			while(curR + 1 < allstr.size() && allstr[curR+1].str.length() == allstr[curL].str.length()){
				curR++;
			}
			Gbase = ids[curL];
			Gsize = ids[curR] - ids[curL] + 1;
			if(curLen == start.length())
				ansBase = Gbase;
#ifdef DcurLR
			debug(curLen);
			debug(curL);
			debug(curR);
			for(int i = curL; i <= curR; i++){
				cout << allstr[i].str << " u: " << ids[i] - Gbase << endl;
			}
#endif
			vector<vector<ll>> &curG = G[Gid];
			vector<vector<ll>> &preG = G[Gid ^ 1];
			curG.clear();
			curG.resize(Gsize, vector<ll>(Gsize, INF));
			for(int i = 0; i < Gsize; i++)
				curG[i][i] = 0;
			for(int i =0; i < rulesubid[curLen].size(); i++){
				int u = rulesubid[curLen][i].F[0] - Gbase;
				int v = rulesubid[curLen][i].S[0] - Gbase;
#ifdef Drule
				cout << "add rule from " << u << " to " << v << endl;
#endif
				curG[u][v] = 1;
			}
	#ifdef DcurG
			for(int i = 0; i < Gsize; i++){
				for(int j = 0; j < Gsize; j++){
					cout << curG[i][j] << " ";
				}
				cout << endl;
			}
	#endif
			if(curLen > 1){
				for(int i = curL; i <= curR; i++){
						int irlen = allstr[i].rlen, irid = allstr[i].rid, isid = allstr[i].sid + 1;
						int u = (allstr[i].rnd == 0 ? rulesubid[irlen][irid].F[isid] : rulesubid[irlen][irid].S[isid]) - pGbase;
					for(int j = curL; j <= curR; j++){
						if(ids[i] == ids[j])
							continue;
						if(allstr[i].str[0] == allstr[j].str[0]){
							int jrlen = allstr[j].rlen, jrid = allstr[j].rid, jsid = allstr[j].sid + 1;
							int v = (allstr[j].rnd == 0 ? rulesubid[jrlen][jrid].F[jsid] : rulesubid[jrlen][jrid].S[jsid]) - pGbase;
							int cu = ids[i] - Gbase, cv = ids[j] - Gbase;
#ifdef DcurG
							debug(cu);
							debug(cv);
							debug(curG.size());
							debug(u);
							debug(v);
							debug(preG.size());
							printf("new %d to %d with old %d to %d, cost = %lld\n", cu, cv, u, v, preG[u][v]);
#endif
							curG[cu][cv] = min(curG[cu][cv], preG[u][v]);
						}
					}
				}	
			}
			for(int k = 0; k < Gsize; k++){
				for(int i = 0; i < Gsize; i++){
					if(curG[i][k] == INF)
						continue;
					for(int j = 0; j < Gsize; j++){
						if(curG[k][j] == INF)
							continue;
						curG[i][j] = min(curG[i][j], curG[i][k] + curG[k][j]);
					}
				}
			}
	#ifdef DcurG
			for(int i = 0; i < Gsize; i++){
				for(int j = 0; j < Gsize; j++){
					cout << curG[i][j] << " ";
				}
				cout << endl;
			}
	#endif
			Gid^=1;
			pGsize = Gsize, pGbase = Gbase;
			curL = curR+1;
		}
		vector<vector<ll>>& ansG = G[Gid^1];
		cout << "Case " << caseN++ << ": ";
		int u = rulesubid[0][0].F[0] - ansBase;
		int v = rulesubid[0][0].S[0] - ansBase;
#ifdef Dans
		debug(u);
		debug(v);
		debug(ansG.size());
		debug(ansG[u].size());
#endif
		if(ansG[u][v] == INF)
			cout << "No solution\n";
		else
			cout << ansG[u][v] << endl;
	}

}
