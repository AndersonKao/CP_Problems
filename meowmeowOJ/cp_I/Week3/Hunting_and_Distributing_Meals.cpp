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
#define endl '\n'
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
int N, M;
vec<int> age;
vec<string> name;
vec<int> pos;
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	while(cin >> N >> M){
		name.resize(N);
		age.resize(N);
		pos.resize(N);
		REP(i, N){
			string carrier;
			cin >> name[i] >> carrier >> age[i];
			if(carrier[0] == 'e'){
					pos[i] = 0;
			}
			else if(carrier[0] == 'n'){
					pos[i] = 1;
			}
			else if(carrier[0] == 'k'){
					pos[i] = 2;
			}
			else if(carrier[0] == 'w'){
					pos[i] = 3;
			}
			else if(carrier[0] == 'a'){
					pos[i] = 4;
			}
			else if(carrier[0] == 'm'){
					pos[i] = 5;
			}
			else if(carrier[0] == 'd'){
					pos[i] = 6;
			}
			else if(carrier[0] == 'l'){
					pos[i] = 7;
			}
		}
		auto cmp = [&](int a, int b){
			if(pos[a] != pos[b]){
				return pos[a] < pos[b];
			}
			else if(age[a] != age[b]){
				if(pos[a] == 4){
					return age[a] < age[b];
				}
				return age[a] > age[b];
			}
			return name[a] < name[b];
		};
		vec<int> V(N);
		iota(al(V), 0);
		sort(al(V), cmp);
		for(int i = 0; i < min(N, M); i++){
			cout << name[V[i]] << '\n';
		}
	}
	return 0;
}

