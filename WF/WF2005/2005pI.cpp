#include <bits/stdc++.h>
using namespace std;
bool cmp(pair<int, int>&a, pair<int, int>&b){
    if(a.second == b.second){
        return a.first < b.first;
    }
    return a.second < b.second;
}
int main()
{
    int w, r;
    int caseN = 1;
    while (cin >> w)
    {
        if(w == 0)
            break;
        vector<pair<int, int>> event(w);
        for (int i = 0; i < w; i++){
            cin >> event[i].first >> event[i].second;
        }
        cin >> r;
        vector<pair<int, int>> room(r);
        for (int i = 0; i < r;i++){
            int p, h, m;
            cin >> p;
            scanf("%d:%d", &h, &m);
            room[i].first = p, room[i].second = (h - 14) * 60 + m;
        }

        sort(event.begin(), event.end(), cmp);
        sort(room.begin(), room.end(), cmp);
        #ifdef DEBUG
        for (int i = 0; i < w; i++){
            cout << "event " << i << ": with p = " << event[i].first << " t = " << event[i].second << endl;
        }
        for (int i = 0; i < r; i++){
            cout << "room " << i << ": with p = " << room[i].first << " t = " << room[i].second << endl;
        }
        #endif
        multiset<int> S;
        int ei = 0;
        int ans = w;
        for (int i = 0; i < r; i++)
        {
            while(ei < event.size()&& event[ei].second <= room[i].second){
                S.insert(event[ei].first);
                ei++;
            }
            multiset<int>::iterator it = S.upper_bound(room[i].first);
            if ((it == S.end() && !S.empty()) || (it != S.begin()))
            {
                it--;
                ans--;
                S.erase(it);
            }
            #ifdef DEBUG
            cout << "In set: ";
            for (multiset<int>::iterator it = S.begin(); it != S.end(); it++)
            {
                cout << *it << " ";
            }
            cout << endl;
            #endif
        }
        int remain = 0;
        for (multiset<int>::iterator it = S.begin(); it != S.end(); it++){
            remain += (*it);
        }
        for (int i = ei; i < w; i++)
            remain += event[i].first;
        cout << "Trial " << caseN++ << ": " << ans << " " << remain << endl << endl;
    }

    return 0;
}