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
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;

using cd = complex<double>;
const double PI = acos(-1);

int reverse(int num, int lg_n) {
    int res = 0;
    for (int i = 0; i < lg_n; i++) {
        if (num & (1 << i))
            res |= 1 << (lg_n - 1 - i);
    }
    return res;
}

void fft(vector<cd> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}
// if doing on real number polynomial, just change int to double. And check real() >= eps ? real() : 0 at line 62 (generating result)
vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
// add this for multiplying two long numbers
    int carry = 0;
    for (int i = 0; i < n; i++){
        result[i] += carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }
    return result;
}
char sa[20000], sb[20000];

int main(){
    scanf("%s%s", sa, sb); // multiply two bin integers
    printf("%s\n%s\n", sa, sb); // multiply two bin integers
    int lena = strlen(sa), lenb = strlen(sb);
	int n = 1;
    while(n < lena + lenb) n *= 2; // reserving space for multiplication 
    vec<int> a(n, 0), b(n, 0);
    for(int i = 0; i < lena; i++)
	    a[i] = sa[lena - 1 - i] - '0';
    for(int i = 0; i < lenb; i++)
	    b[i] = sb[lenb - 1 - i] - '0';

    vec<int> res = multiply(a, b);
    for(int i = res[lena + lenb - 1] ? lena + lenb - 1: lena + lenb - 2; i >= 0; i--)
	    putchar('0' + res[i]);
    putchar('\n'); return 0;
}
