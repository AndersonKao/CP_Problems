#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define al(a) a.begin(), a.end()
#define F frist
#define S second
#define eb emplace_back
#define REP(i,n) for(int i = 0; i < (int)n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define debug(x) cout << " > " << #x << ": " << x << endl;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <typename T>
using vec = vector<T>;
bool first;

void solve(int bitn){
//	cout << "ouo: " << data << endl;
        if (bitn == 8){
            cout << "11111111" << endl << flush;
            return;
        }else if (bitn == 4 and first) {
            cout << "10101010" << endl << flush;
            
            first = false;
            return;
        }
    string str = "00000000";
	while(bitn){
	    int i = rand() % 8;
	    if(str[i] == '0')
	        str[i] = '1', bitn--;
	}
	cout << str << endl;
	cout.flush();
}


int main(){
	int T;
	cin >> T;	
	while(T--){
		int bitn;
		first = true;
		while(cin >> bitn){
			if(bitn == 0)
				break;
			if(bitn == -1){
				cout << "WA\n";
				return 0;
			}
			solve(bitn);
		}
	}
}

