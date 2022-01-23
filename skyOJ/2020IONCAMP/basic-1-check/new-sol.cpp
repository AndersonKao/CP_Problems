#include<iostream>
#include<algorithm>
#include <vector>
#include<string>
#include<iomanip>
#define item_limit 6
using namespace std;

struct item {
	double ad, ap, p;
	item(double ad, double ap, double p) :ad(ad), ap(ap), p(p) {}
	item() :ad(0.0), ap(0.0), p(0.0) {}
};

struct state {
	int choosen[15];	//第i th要幾件
	double dmg;
};

int status[20];		//0-based
int item_num;
int num = 0;
vector<item>  v;	//裝備資訊
vector<state> combination;

bool cmp(state a, state b) {
	return a.dmg > b.dmg;
}

void print_status() {
	state s;
	double dmg = 0.0, p = 0.0;
	for (int i = 0; i < item_num; ++i) {
		s.choosen[i + 1] = status[i];
		dmg += (0.75 * v[i].ad + 0.2 * v[i].ap) * status[i];
		p += v[i].p * status[i];
	}
	s.dmg = dmg * (1.0 + min(p, 1.0));

	combination.push_back(s);
}

void k(int remain, int idx) {		//把remain個東西, 分給0到idx的人
	if (remain == 0) {
		print_status();
		return;
	}

	if (idx == -1 && remain != 0)
		return;

	for (int i = remain; i >= 0; --i) {			//自己拿走 i 個, 剩下的分給 0 到 idx - 1的人
		status[idx] = i;
		k(remain - i, idx - 1);
		status[idx] = 0;
	}
}

int main() {
	int m, n;
	double ap, ad, p;

	cin >> m >> item_num;
	v.resize(item_num);
	for (int i = 0; i < item_num; ++i) {
		cin >> v[i].ap >> v[i].ad >> v[i].p;
	}

	k(item_limit, item_num - 1);

	sort(combination.begin(), combination.end(), cmp);

	cout << fixed << setprecision(2) << combination[m - 1].dmg;

	return 0;
}