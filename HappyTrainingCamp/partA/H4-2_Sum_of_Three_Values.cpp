#include <bits/stdc++.h>
using namespace std;

using Iter = vector<pair<int, int>>::iterator;
int T;

bool found =false;
bool cmp(const pair<int, int>&lhs, const pair<int, int>& rhs){
    if((lhs).first > (rhs).first)
        return true;
    else if((lhs).first < rhs.first)
        return false;
    return lhs.second < (rhs.second);
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    vector<pair<int, int>> V;
    int N, x;
    cin >> N >> x;
    int data;
    for (int i = 0; i < N; i++){
        cin >> data;
        V.emplace_back(data, i + 1);
    }
    sort(V.begin(), V.end(), cmp);

    // debug
    if(V.size() >= 3)
    for (Iter it1 = V.begin(); it1 != V.end() - 2; it1++){
        if(found)
            break;
        for (Iter it2 = it1 + 1; it2 != V.end() - 1; it2++){
            if(found)
                break;
            Iter it3 = it2 + 1;
            if(it3 == V.end())
                break;
            pair<int, int> tofind(x - it1->first - it2->first, -1);
            Iter last = lower_bound(it3, V.end(), tofind, cmp);
            if(last != V.end() && it1->first + it2->first + last->first == x){
                found = true;
                vector<int> ANS;
                ANS.emplace_back(it1->second);
                ANS.emplace_back(it2->second);
                ANS.emplace_back(last->second);
                sort(ANS.begin(), ANS.end());

                for (int i = 0; i < 3; i++)
                    cout << ANS[i] << (i == 2 ? "\n" : " ");
            }
        }
    }

    if (!found)
        cout << "IMPOSSIBLE\n";

    return 0;
}