#include<bits/stdc++.h>
#define LL long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
const int N (105);
int a[N];
char s[10005];
int main() {
	int cse = 0;
	while (cin >> (s + 1)) {
		if (s[1] == '.') break;
		LL c = 0; cse++;
		printf ("Case %d: ", cse);
		int m = strlen (s + 1), n = -1, mid = m + 1;
		rep (i, 1, m) if (s[i] == '/') mid = i;
		int flg = 1, xa = -1, xb = -1, now = 0, ok = 0;
		rep (i, 2, mid - 1) {
			if (s[i] == '-' || s[i] == '+' || s[i] == ')') {
				if (i != 2) {
					if (xa < 0) xa = 1;
					if (xb < 0) xb = 1;
					if (!ok) xb = 0;
					if (n == -1) n = xb;
					a[xb] = xa * flg, xb = -1, xa = -1;
				}
				ok = 0;
				if (s[i] == ')') continue;
				flg = (s[i] == '-' ? -1 : 1);
				now = 0; continue;
			}
			if (s[i] == '^') {
				now = 1; continue;
			}
			if (s[i] == 'n') {
				ok = 1; continue;
			}
			int &xx = (now ? xb : xa);
			if (xx < 0) xx = 0;
			xx = xx * 10 + s[i] - '0';
		}
		rep (i, mid + 1, m) c = c * 10 + s[i] - '0';
		if (c == 0) c = 1;
        int pl = 0;
		rep (x, 0, 100) {
			LL sum = 0, t = 1;
			per (i, 100, 0) sum = (sum * x + a[i]) % c;
			if (sum != 0) {
				puts ("Not always an integer");
				pl = 1; break;
			}
		}
		if (!pl) puts ("Always an integer");
		memset (a, 0, sizeof(a));
	}
	return 0;
}
