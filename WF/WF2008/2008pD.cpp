// solution: I just misunderstand and know the questions stands for the following
// **The hare always places a comfirmation marker on the route following a choice point.**
// So even the edge have two comfirmation marker is legal, we may occur that the edge is between two decision point and the two corresponding comfirmaker should belongs two decision point.
// So it's one and only one comfirmation marker on each edge copy(eid and eid^1) represents if u is a comfirmation marker and also v, then it may use the edge twice.
// failed : when clearflour on one edge, the correspond copied edge(eid^1) shouldn't clearflour if it's not at the same point
// failed : when determine the min(confdist, curdis)
// we have to make sure now we are finding flour but not found
// because if founded flour, the function is used to find the next decition point, the dis cost shouldn't be cut;
// edge case 1 may just be the start and end
// sol : check that dis at least > 0
// only when checkpoint we need to ignore the direction arrived from, not when idiot running
// 
#include <bits/stdc++.h>
using namespace std;
#define MAXN 101
#define al(x) x.begin(), x.end()
#define eb emplace_back
#define debug(x) cout << #x << ": " << x << endl;
using pii = pair<int, int>;
using ll = long long;
int ncp, nroad, ncm, startisect, endisect, startdir;
ll confdist;
vector<bool> isdeci(MAXN);
vector<int> tmproute;
struct edge{
	int u, v;
	int degu, degv;
	int len;
	int flour;
	edge(){}
	edge(int a, int b, int du, int dv, int l){
		u = a, v = b;
		degu = du, degv = dv;
		len = l;
		flour = -1;
	}
	void putflour(int dis){
		flour = (flour == -1 ? dis : min(dis, flour));
	}
	bool getflour(ll dis){
		return flour == -1 ? false : flour <= dis;
	}
	void clearflour(){
		flour = -1;
	}
	friend ostream& operator<<(ostream& os, edge& a);
};
ostream& operator<<(ostream& os, edge& a){
	return (os << a.u << " to " << a.v << " du, dv = " << a.degu << ", " << a.degv << " len = " << a.len << " flour: " << a.flour);
}
vector<vector<int>> G;
vector<edge> Es; 
void init(){
	fill(isdeci.begin(), isdeci.end(), false);
	tmproute.clear();
	G.clear();
	G.resize(MAXN);
	Es.clear();
}
inline int counterdeg(int deg){
	return deg >= 180 ? deg - 180 : deg + 180;
}
inline int absdeg(int deg, int deg2){
	int x = abs(deg - deg2);
	return min(360 - x, x);
}
inline int diffdeg(int deg, int deg2){
	if(deg == deg2)
		return 0;
	if(deg > deg2){
		int v =  deg - deg2;
		if(v > 180){
			return 360 - v;	
		}else{
			return -v; 
		}
	}
	else{
		int v =  deg2 - deg;
		if(v > 180){
			return -v;	
		}else{
			return 360-v; 
		}
	}	
}
pair<int,int> findfirst(int u, int peid, ll& curdis, bool docatch, bool& catchit){
	tmproute.eb(peid);
#ifdef Dfind
	cout << "finding " << u << endl;
	debug(peid);
	debug(curdis);	
	debug(docatch);	
	debug(catchit);
	cout << "tmproute: ";
	for(int a: tmproute)
		cout << a << " ";
	cout << endl;
#endif
	if(isdeci[u] && curdis != 0){
		if(docatch && catchit == false)
			curdis = min(confdist, curdis);
#ifdef Dfind
		cout << "isdeci" << endl;
#endif
		return make_pair(u, peid);
	} 

	if(peid != -1 && ((docatch && catchit && u == endisect) || (docatch == false && u == endisect))){
#ifdef Dfind
		cout << "end " << endl;
#endif
		return {u, peid};
	} 
	if(docatch && catchit == false && curdis >= confdist){
		curdis = min(confdist, curdis);
#ifdef Dfind
		cout << "out of confdist" << endl;
#endif
		return {-1, -1};
	}
	if(G[u].size() == 1 && peid != -1){
		if(docatch && catchit == false)
			curdis = min(confdist, curdis);
#ifdef Dfind
		cout << "dead end on " << u << endl;
#endif
		return {u, peid};
	}

	int outdeg =0;	
	int outdegv = 0;
	if(peid == -1){
		outdeg = startdir;
		outdegv = counterdeg(outdeg);
// use the worst case, diff with outdeg = 180
	}
	else{
		outdegv = Es[peid].degu;
 		outdeg = counterdeg(outdegv);
	}
	int eid = -1;
	vector<int> & V = G[u];
	for(int i = 0; i < G[u].size(); i++){
//		if(V[i] == peid) // error on description
//			continue;
#ifdef Dfind
		cout << "test " << G[u][i] << ": " << Es[G[u][i]] << endl;
#endif
		int& edegv = Es[V[i]].degu;
		int aoe = absdeg(outdeg, edegv);
		int aoo = absdeg(outdeg, outdegv);
		if(aoe < aoo){
			outdegv = edegv;
			eid = G[u][i];
#ifdef Dfind
			cout << "eid renew to "  << eid << endl;
#endif
		}	
		else if(aoe == aoo){
			if(diffdeg(outdeg, edegv) >= 0){
				outdegv = edegv;
				eid = G[u][i];
#ifdef Dfind
			cout << "eid renew to "  << eid << endl;
#endif
			}	
		}
	}	
#ifdef Dfind
	cout << "going to " << eid << ": " << Es[eid] << endl;
	cout << "conter to " << (eid^1) << ": " << Es[eid^1] << endl;
#endif
	if(docatch){
		if(Es[eid].getflour(confdist - curdis)){
			catchit = true;	
//			if(Es[eid^1].flour == (Es[eid].len - Es[eid].flour))
//				Es[eid^1].clearflour();
			Es[eid].clearflour();
		}
	}
	curdis += Es[eid].len;
	return findfirst(Es[eid].v, eid^1, curdis, docatch, catchit);
}

pair<ll, ll> solve(vector<int>& route){	
	ll hounddis = 0, haredis = 0;
	bool catchit = false;
	tmproute.clear();
	int cur, eid_in; 
	ll dis = 0;
	tie(cur, eid_in) = findfirst(startisect, -1, dis, false, catchit);
	hounddis += dis;
	haredis += dis;
#ifdef Dsolve
	printf("findfirst: cur= %d, eid_in=%d\n", cur, eid_in);
	debug(hounddis);
	debug(haredis);
#endif
	route.insert(route.end(), al(tmproute));	
	if(cur == endisect)
		return {hounddis, haredis};
	while(cur != endisect){
#ifdef Dsolve
		cout << "now at check point " << cur << " eid-in: " << eid_in << endl;
#endif
		vector<bool> outried(G[cur].size(), false);	
		int foundu = -1, found_eid_in = -1;
		catchit = false;
		int outdegv = Es[eid_in].degu; 
		int outdeg = counterdeg(Es[eid_in].degu);	
		while(catchit == false){
#ifdef Dsolve	
			cout << "haven't catchit\n";
#endif
			int usei = -1;
			outdeg = counterdeg(outdegv);
			for(int i = 0; i < G[cur].size(); i++){
				if(outried[i] || G[cur][i] == eid_in)
					continue;
#ifdef Dsolve
		cout << "otest " << G[cur][i] << ": " << Es[G[cur][i]] << endl;
#endif
				int edegv = Es[G[cur][i]].degu;
				int aoe = absdeg(outdeg, edegv);
				int aoo = absdeg(outdeg, outdegv);
				if(aoe < aoo){
					outdegv = edegv;
					usei = i;
#ifdef Dfind
			cout << "eid renew to "  << G[cur][usei]<< endl;
#endif
				}	
				else if(aoe == aoo){
					if(diffdeg(outdeg, edegv) >= 0){
						outdegv = edegv;
						usei = i;
#ifdef Dsolve
			cout << "eid renew to "  << G[cur][usei]<< endl;
#endif
					}	
				}
			}	
			if(usei == -1)
				cout << "errororrr" << endl;
			int eid = G[cur][usei];
			dis = Es[eid].len;
			outried[usei] = true;
			tmproute.clear();
			if(Es[eid].getflour(min(confdist, dis))){
				catchit = true;	
//				if(Es[eid^1].flour == (Es[eid].len - Es[eid].flour))
//					Es[eid^1].clearflour();
				Es[eid].clearflour();
#ifdef Dsolve
				cout << "preget flour " <<endl;
#endif
			}
#ifdef Dsolve
			cout << "go for " << Es[eid] << endl;
#endif
			tie(foundu, found_eid_in) = findfirst(Es[G[cur][usei]].v, G[cur][usei]^1, dis, true, catchit);
			if(foundu == -1 || catchit == false){
				outdegv = Es[eid].degu;			
				hounddis += dis*2;	
			}
			
#ifdef Dsolve
			debug(hounddis);
			debug(haredis);
#endif
		}
		haredis += dis;		
		hounddis += dis;	
#ifdef Dsolve
		debug(hounddis);
		debug(haredis);
#endif
		route.insert(route.end(), al(tmproute));	
		cur = foundu, eid_in = found_eid_in;
	}
	return {hounddis, haredis};
}

int main(){
	int caseN = 1;
	while(cin >> ncp >> nroad >> ncm >> confdist >> startisect >> endisect >> startdir){
		if(ncp == 0 && nroad == 0 && ncm == 0 && confdist == 0 && startisect == 0 && endisect == 0 && startdir == 0)
			break;
		init();
		for(int i = 0; i < ncp; i++){
			int u;	
			cin >> u;
			isdeci[u] = true;
		}
		for(int i = 0 ;i < nroad ; i++){
			int u , v;			
			int du, dv, l;
			cin >> u >> v >> du >> dv >> l;
			G[u].eb(Es.size());
			Es.emplace_back(u, v, du, dv, l);
			G[v].eb(Es.size());
			Es.emplace_back(v, u, dv, du, l);
		}
		for(int i = 0; i < ncm; i++){
			int u, eid, dis;
			cin >> u >> eid >> dis;
			eid = (eid-1) * 2;
			if(u != Es[eid].u)
				eid ^= 1;
			Es[eid].putflour(dis);
			Es[eid^1].putflour(Es[eid^1].len - dis);
		}
#ifdef Dedges
		for(auto k : Es){
			cout << k << endl;
		}
#endif
		vector<int> ansarr;
		int hounddis, haredis;
		tie(hounddis, haredis) = solve(ansarr);	
		cout << "Case " << caseN++ << ":\n";	
		cout << "   Length of hare's route is " << haredis << endl;
		cout << "   Length of hound's search is " << hounddis<< endl;
		cout << "   Route:";
		for(int i = 1; i < ansarr.size(); i++)
			cout << " " << (ansarr[i] >> 1) + 1;
		cout << endl << endl;
	}
	return 0;
}
