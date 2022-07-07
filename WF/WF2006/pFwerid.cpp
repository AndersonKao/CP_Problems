#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#ifdef dbg
#define endl '\n'
#endif

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 1e9;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

int init, n;
vec<pair<char, int>> _list;
vec<vec<int>> hour, minute;
deq<bool> vis;

vec<vec<vec<int>>> ans;

struct Src {
    double speed;
    int idx, num;
    
    Src() {
        idx = -1;
        speed = num = 0;
    }
    Src(double speed, int idx, int num) : speed(speed), idx(idx), num(num) {}
    
};

vec<Src> status(10);

void go(int now, int goal) {
    if (!fcmp(status[now].speed, 1. * goal)) {
        if (goal == 2) { // hour
            vec<int> tmp;
            
            for (int i = 1; i <= now; i++)
                tmp.eb((status[i].num == 1 ? -1 : 1) * (1 + status[i].idx));
            
            hour.eb(tmp);
        }
        
        if (goal == 24) {
            vec<int> tmp;
            
            for (int i = 1; i <= now; i++)
                tmp.eb((status[i].num == 1 ? -1 : 1) * (1 + status[i].idx));
            
            minute.eb(tmp);
        }
        
        return;
    }
    
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        
        vis[i] = true;
        
        if (status[now].num < 2) {  // same
           status[now+1].idx = i;
           status[now+1].num = status[now].num + 1;
           status[now+1].speed = status[now].speed;
           
           go(now+1, goal); 
        }
        
        if (status[now].num > 0) {  // right
            status[now+1].idx = i;
            status[now+1].num = 1;
            status[now+1].speed = -status[now].speed*(1. * _list[status[now].idx].S/_list[i].S);
            
            go(now+1, goal);
        }
        
        vis[i] = false;
    }
}

bool check(vec<int>& h, vec<int>& m) {
    
    int i;
    for (i = 0; i < h.size() and i < m.size(); i++) {
        
        if (h[i] != m[i]) break;
    }
    
    for (int k = i; k < h.size(); k++)
        for (int j = i; j < m.size(); j++)
            if (abs(h[k]) == abs(m[j])) return false;
    
    return true;
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> n) {
        if (!n) break;
        
        if (c != 1) cout << endl;
        
        cin >> init;
        
        _list.resize(n);
        for (auto &i : _list)
            cin >> i.F >> i.S;
            
        hour.clear();
        minute.clear();
        vis.resize(n);
        fill(al(vis), false);
        
        status[0].speed = init;
        status[0].idx = -1;
        status[0].num = 0;
        go(0, 2);
        // devec2(hour);
        
        go(0, 24);
        // devec2(minute);
        
        ans.clear();
        for (auto i : hour) {
            for (auto k : minute) {
                if (check(i, k)) {
                    vec<vec<int>> tmp;
                    tmp.eb(i);
                    tmp.eb(k);
                    
                    ans.eb(tmp);
                    // devec2(tmp);
                }
            }
        }
        
        if (ans.size() == 0) {
            cout << "Trial " << c++ << " IS IMPOSSIBLE\n";
            continue;
        }
        
        auto cmp = [](vec<vec<int>>& a, vec<vec<int>>& b) {
            int na = 0, nb = 0;
            set<int> sa, sb;
            for (auto i : a)
                for (auto k : i) {
                    if (sa.find(k) == sa.end())
                        na += (k < 0);
                    
                    sa.emplace(k);
                }
            
            if (a[0].size() and a[1].size() and a[0][0] != a[1][0]) na--;
                
            for (auto i : b)
                for (auto k : i) {
                    if (sb.find(k) == sb.end())
                        nb += (k < 0);
                    
                    sb.emplace(k);
                }
                
            if (b[0].size() and b[1].size() and b[0][0] != b[1][0]) nb--;
            
            if (na != nb)
                return na < nb;
            
            if (a[0].size() + a[1].size() != b[0].size() + b[1].size())
                return a[0].size() + a[1].size() < b[0].size() + b[1].size();
            
            string strA, strB;
            for (int i = 1; i >= 0; i--) {
                for (auto k : a[i])
                    strA += _list[(abs(k) - 1)].F;
            }
            
            for (int i = 1; i >= 0; i--) {
                for (auto k : b[i])
                    strB += _list[(abs(k) - 1)].F;
            }
            
            
            return strA < strB;
        };
        
        // for (int i = 0; i < ans.size(); i++) {
        //     auto t = ans[i];
        //     devec2(t);
        // }
           
        // cout << endl;
        sort(al(ans), cmp);
        
        // for (int i = 0; i < ans.size(); i++) {
        //     auto t = ans[i];
        //     devec2(t);
        // }
        
        cout << "Trial " << c++ << endl;
        cout << "Minutes: *";
        for (int i = 0; i < ans[0][1].size(); i++) {
            if (i == 0)
                cout << _list[abs(ans[0][1][i])-1].F;
            else {
                if (ans[0][1][i] < 0)
                    cout << '-';
                cout << _list[abs(ans[0][1][i])-1].F;
            }
        }
        cout << endl;
        cout << "Hours:   *";
        for (int i = 0; i < ans[0][0].size(); i++) {
            if (i == 0)
                cout << _list[abs(ans[0][0][i])-1].F;
            else {
                if (ans[0][0][i] < 0)
                    cout << '-';
                cout << _list[abs(ans[0][0][i])-1].F;
            }
        }
        cout << endl;
    }
}