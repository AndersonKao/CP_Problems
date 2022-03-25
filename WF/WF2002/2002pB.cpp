// AC 
// even without map we can get correct output
#include <bits/stdc++.h>
using namespace std;

#define debug(x) cout << " > " << #x << " " << x << endl;
#define F first
#define endl '\n'
#define S second
#define B begin
#define E end
#define al(a) a.begin(), a.end()
#define REP(i, n) for(int i = 0; i < n; i++)
template<typename T> using vec = vector<T>;
template<typename T> using Prior = priority_queue<T>;
template<typename T> using prior = priority_queue<T, vector<T>, greater<T>>;
using ll = long long;
using pii = pair<int, int>;
using strIter = std::string::iterator;
using pss = pair<strIter, strIter>;

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) {cout << a.F << ' ' << a.S; return out;}
vec<string> strs;

class ele{
public:
	string str, str2;
	ele(){
		str.clear(), str2.clear();
	}
	ele(const ele& b){
		str = b.str, str2= b.str2;
	}
	ele(string &stra, string& strb){
		str = stra;
		str2 = strb;
	}
};

auto cmp = [](const ele& a, const ele& b){
	if(a.str2.length() <b.str2.length())
		return false;
	else if(a.str2.length() == b.str2.length()){
		return a.str2 >= b.str2;	
	}
	return true;
};

//map<ele, bool, decltype(cmp)> vis(cmp);

int main(){

	int m;
	int Case = 1;
	while(cin >> m){
		if(!m)
			break;
		strs.clear();
		strs.resize(m);
		REP(i, m)
			cin >> strs[i];
		priority_queue<ele, vector<ele>, decltype(cmp)> pq(cmp);
		//priority_queue<ele> pq;
		REP(i, m){
			REP(j, m){
				if(i == j)
					continue;
				pss it = std::mismatch(al(strs[i]), strs[j].begin());
				if(it.F == strs[i].end()){
		//			cout << "prefix find:\n";
		//			debug(strs[i]);
		//			debug(strs[j]);
					ele newS(strs[i], strs[j]);
//					vis[newS] = true;	
					pq.emplace(newS);
				}
			}
		}

		//cout << "pqing\n";
		while(!pq.empty()){
			//cout << "top!!: " <<  pq.top().str  << ", " << pq.top().str2 << endl;
			if(pq.top().str.length() == pq.top().str2.length())
				break;
			ele topS = pq.top();
			pq.pop();
			pss topIt = std::mismatch(al(topS.str), topS.str2.begin());
			REP(i, m){
				//cout << "using " << topS.str << " , " << topS.str2 << " for " << i << endl;
				pair<strIter, strIter> it = std::mismatch(al(strs[i]), topIt.S);
				if(it.F == strs[i].end() && it.S == topS.str2.end()){
					//cout << " case 1 \n";
					ele newS = topS;
					newS.str = newS.str2;
/*
					if(vis.find(newS) != vis.end())
						continue;
					vis[newS] = true;
*/
					pq.emplace(newS);
				}
				else if (it.F == strs[i].end()) {
					//cout << " case 2 \n";
					ele newS = topS;
					newS.str += strs[i];
					//cout << "placing: " << newS.str << ", " << newS.str2 << endl;
/*
					if(vis.find(newS) != vis.end())
						continue;
					vis[newS] = true;
*/
					pq.emplace(newS);
				}
				else if (it.S == topS.str2.end()) {
					//cout << " case 3 \n";
					ele newS = topS;
					newS.str += strs[i];
					swap(newS.str, newS.str2);
					//cout << "placing: " << newS.str << ", " << newS.str2 << endl;
/*
					if(vis.find(newS) != vis.end())
						continue;
					vis[newS] = true;
*/
					pq.emplace(newS);

				}
			}
		}
		cout << "Code " << Case++ << ": " << pq.top().str2.length() << " bits\n";
		int cnt = 0;
		int limit = pq.top().str.length();
		REP(i, limit){
			cout << pq.top().str[i];
			cnt++;
			if(cnt == 20){
				cnt = 0;
				cout << endl;	
			}
		}
		if(cnt != 0)
			cout << endl;
		cout << endl;
		
	}
	
	
	return 0;
}
