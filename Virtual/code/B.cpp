#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> using vec = vector<T>;
template <typename T> using deq = deque<T>;
template <typename T> using p = pair<T, T>;

#define endl '\n'
#define F first
#define S second
#define eb emplace_back
#define al(a) a.begin(),a.end()
#define yccc ios_base::sync_with_stdio(false),cin.tie(0)

double fcmp(double a, double b = 0, double eps = 1e-9) {
    if (abs(a-b) < eps) return 0;
    return a-b;
}

const double PI = acos(-1);

int main() {
    yccc;
    
    int n, k;
    cin >> n >> k;
    
    vec<int> _list(n), last(n), count(n+1, 0);
    for (auto &i : _list) {
        cin >> i;
    }
    
    for (int i = n-1; i >= 0; i--) {
        last[i] = ++count[_list[i]];
    }
    
    deq<int> d;
    deque<int> ans;
    deq<bool> isv(n+1);
	deq<bool> inq(n+1);
    fill(isv.begin(), isv.end(), false);
    fill(inq.begin(), inq.end(), false);
    
    for (int i = 0; i < n; i++) {
        //printf("visit %d\n",i);
        if(isv[_list[i]]) continue;

		if(inq[_list[i]] == false){
			while (d.size() && d.back() >= _list[i]) {
					inq[d.back()] = false;
					d.pop_back();
			}
			inq[_list[i]] = true;
			d.eb(_list[i]);
		}
		/*
		cout << i << ": " << _list[i] << " \n";
		for(int v : d){
			cout << v << " ";
		}
		cout << endl;
		*/

        if (last[i] == 1){
            while(!d.empty() && d.front() != _list[i]) {
                ans.eb(d.front());
                isv[d.front()] = true;
				inq[d.front()] = false;
                d.pop_front();
            }
			ans.eb(d.front());
			d.pop_front();
        } 
    }

//    for(int i=0;i<k;i++) cout<<ans[i] << " \n"[i==k-1];
/*
	fill(al(count), 0);
	for(int i = 0; i <= n-1; i++){
		last[i] = ++count[_list[i]];
	}

	deque<int> ans2;
	fill(al(isv), false);
	d.clear();
	for(int i = n-1; i >= 0; i--){
		if(isv[_list[i]]) continue;
		while(d.size() && d.back() <= _list[i]){
			d.pop_back();
		}
		d.eb(_list[i]);
		if (last[i] == 1) {
			while(d.size()){
				ans2.emplace_front(d.front());
				isv[d.front()] = true;
				d.pop_front();
			}
		}
	}

	for(int i = 0; i < n; i++){
		if(ans[i] == ans2[i]) continue;
		if(ans[i] > ans2[i]){
			swap(ans, ans2);
			break;
		}
		if(ans[i] < ans2[i])
			break;
	}
*/
    for(int i=0;i<k;i++) cout<<ans[i] << " \n"[i==k-1];
}

