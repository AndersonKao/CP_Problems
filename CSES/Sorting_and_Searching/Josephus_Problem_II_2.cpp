#include <bits/stdc++.h>
using namespace std;

template <typename T>
using vec = vector<T>;
struct Fenwick
{

    int n;
    vec<int> arr;
    Fenwick(int n)
    {
        this->n = n;
        arr.resize(n + 1, 0);
    }
    void add(int idx, int val){
        int tmp = idx;
        while(tmp <= n){
            arr[tmp] += val;
            tmp += (tmp & (-tmp));
        }
    }
    int psum(int idx){
        int tmp = idx;
        int ans = 0;
        while(tmp >= 1){
            ans += arr[tmp];
            tmp -= (tmp & (-tmp));
        }
        return ans;
    }
    int val(int idx){
        return psum(idx) - psum(idx - 1);
    }
};

int N;

int main(){

    int k;
    cin >> N >> k;
    Fenwick F(N);
    for (int i = 1; i <= N; i++)
    {
        F.add(i, 1);
    }
    int cur = 1;
    for (int size = N; size > 0; size--)
    {
        int finding = cur + k;
            if(finding > size)finding  = (finding - 1)% size + 1;
        int l = 1, r = N;
        while (l < r)
        {
            int m = (l + r) >> 1;
            int val = F.psum(m);
            if (val < finding)
            {
                l = m + 1;
            }
            else
                r = m;
        }
        cout << l << " ";
        F.add(l, -1);
        cur = finding;
    }
    cout << endl;
}