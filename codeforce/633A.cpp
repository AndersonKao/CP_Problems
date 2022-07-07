#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll gcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0){
        x = 1, y = 0;
        return a;
    }
    ll x1, y1;
    ll g = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}
bool find_any_solution(ll a, ll b, ll c, ll&x0, ll&y0, ll&g){
    g = gcd(abs(a), abs(b), x0, y0);
    if(c % g != 0)
        return false;

    x0 *= (c / g);
    y0 *= (c / g);
    if(a < 0)
        x0 = -x0;
    if(b < 0)
        y0 = -y0;
    return true;
}
void shift_solution(ll& x, ll& y, ll a, ll b, ll cnt) {
    x += cnt * b;
    y -= cnt * a;
}

int main(){
    ll a, b, c;
    cin >> a >> b >> c;
    ll x, y;
    ll g;
   
    if(!find_any_solution(a, b, c, x, y, g)){
        cout << "No\n";
        return 0;
    }
    if (c % g == 0)
    {
        //        cout << x << ", " << y << endl;
        //       cout << x*a + y * b << endl;
        if(x >= 0 && y >= 0){
            cout << "Yes\n";
        }else{
            a /= g;
            b /= g;
            if (x < 0)
            {
                while(y >= 0 && x < 0){
                    shift_solution(x, y, a, b, 1);
                }
            }else{
                while(x >= 0 && y < 0){
                    shift_solution(x, y, a, b, -1);
                }

            }
            if(x >= 0 && y >= 0)
                cout << "Yes\n";
            else
                cout << "No\n";
        }
    }
    else{
        cout << "No\n";
    }
}