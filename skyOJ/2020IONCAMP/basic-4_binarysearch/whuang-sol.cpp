#include<iostream>
#include<algorithm>
#include <vector>
#include<string>
#include<iomanip>
#include<sstream>

using namespace std;

string s = "s", tmp;
vector<int> v;

bool jump(int step, int limit){

	int now_idx = 0, cnt = 0;
	while (now_idx < s.length() - 1) {
		int x = now_idx + step;
		if (x < s.length()) {
			if (v[x] == now_idx)		//離x左邊最近的r是自己->不可能成功
				return false;
			else
				now_idx = v[x];
		}
		else {
			now_idx = x;
		}
		cnt++;

		if (cnt > limit) {
			return false;
		}
	}
	return true;
}

int main(){
    // std::ios_base::sync_with_stdio(false);
    // cin.tie(0);
	int T, limit;

	cin >> T;
	while (T--) {
		cin >> limit >> tmp;

		s = s + tmp + "f";
		v.resize(s.length());
		for (int i = 1; i < s.length(); ++i) {		//記錄自己左邊最近可以走的點
			if (s[i] == 'R' || s[i] == 'f')
				v[i] = i;
			else if (s[i - 1] == 'R')
				v[i] = i - 1;
			else
				v[i] = v[i - 1];
		}

		int L = 1, R = s.length() - 1;		//最小&&最大步數
		while (L < R) {

			bool flag = jump((L + R) / 2, limit);
			if (flag) {							//找更小解
				R = (L + R) / 2;
			}
			else {
				L = (L + R) / 2 + 1;
			}
		}

		s = "s";
		cout << L << '\n';
	}

	return 0;
}