#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define eb emplace_back
#define REP(i, n) for(int i = 0; i < n; i++)
using ll = long long;
template<typename T> using vec = vector<T>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
struct Section{
	bool isFerry;
	ll len;	
	ll timelen;
	int freq;
	vec<int> stTime;
};
vec<Section> sections;
vec<pll> dp; // first for embarkation, second for disembarkation;
int main(){
	int n;
	string from, to, type;
	while(cin >> n){
		if (n == 0)
			break;
		sections.resize(n);	
		REP(i, n){
			cin >> from >> to >> type;
			if (type == "ferry") {
				sections[i].isFerry = true;	
				cin >> sections[i].timelen >> sections[i].freq;
				sections[i].stTime.resize(sections[i].freq);
				REP(j, sections[i].freq){
					cin >> sections[i].stTime[j];
				}
			}
			else if (type == "road") {
				sections[i].isFerry = false;	
				cin >> sections[i].len;
			}
		}
		


	}

	return 0;
}
