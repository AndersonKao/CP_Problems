// AC 2022-05-21 18:51:27
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace __gnu_pbds;

using orderset = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;
using ordermap= tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update>;


int N;

int main(){

    int k;
    cin >> N >> k;
    orderset S;
    for (int i = 1; i <= N; i++)
    {
        S.insert(i);
    }
    int cur = 0;
    for (int size = N; size > 0; size--)
    {
        int finding = cur + k;
        if(finding >= size)
            finding %= size;
        auto it = S.find_by_order(finding);
        cout << *it << " ";
        S.erase(it);
        cur = finding;
    }
    cout << endl;
}