// AC 2022-06-07 08:53:56
#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define F first 
#define S second

#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define al(x) x.begin(), x.end()
#define REP1(i, n) for (int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << #x << ": " << "(" << x.first << ", " << x.second << ")" << endl;
/*
#define DPROC
#define PALL
#define DMERGE
#define DSCORE
*/

template <typename T>
using vec = vector<T>;
using pii = pair<int, int>;
using area = vec<vec<char>>;
using row = vec<char>;
void printMap(const area& MAP){
    cout << "+";
            for (int c = 0; c < MAP[0].size(); c++){
                cout << "-";
            }
            cout << "+\n";

            for (int r = 0; r < MAP.size(); r++)
            {
                cout << "|";
                for (int c = 0; c < MAP[r].size(); c++)
                {
                    cout << MAP[r][c];
                }
                cout << "|\n";
            }
            cout << "+";
            for (int c = 0; c < MAP[0].size(); c++){
                cout << "-";
            }
            cout << "+\n";
}
int matching(const area& other, const area& anoth, pii& offset, bool& reverted){
#ifdef DEBUG
    cout << "matching \n";
    printMap(other);
    printMap(anoth);
#endif

    int maxscore = 0;
    offset = pii(100, 100);
    reverted = false;
    int oh = other.size(), ow = other[0].size(), ah = anoth.size(), aw = anoth[0].size();
    for (int roff = (-ah); roff < oh; roff++)
    {
        for (int coff = (-aw ); coff < ow; coff++){
            int mnum = 0;
            bool valid = true;
            for (int i = 0; i < ah; i++)
            {
                int oi = i + roff;
                if(oi >= oh || oi < 0)
                    continue;
                for (int j = 0; j < aw; j++){
                    int oj = j + coff;
                    if (oj >= ow || oj < 0)
                        continue;
                    if(other[oi][oj] != '-'){

                        if( anoth[i][j] == other[oi][oj] ){
                            mnum++;
                        }
                        else if(anoth[i][j] != '-'){
                            valid = false;
                            break;
                        }
                    }
                }
                if(!valid)
                    break;
            }
            if (valid && mnum > 0)
            {
                if(mnum> maxscore){
                    maxscore = mnum;
                    offset = pii(roff, coff);
                    reverted = false;
                }
                else if(mnum == maxscore){
                    //cout << "same score\n";
                    offset = min(offset, pii(roff, coff));
                    // depii(offset);
                    reverted = false;
                }
            }
        }
    }
    return maxscore;
}
using pmap = tuple<int, int, int, pii, bool>; // i, j, score, pair
auto pqcmp = [](const pmap &a, const pmap &b)
{
    if(get<2>(a) == get<2>(b))
    {
        if(min(get<0>(a), get<1>(a)) == min(get<0>(b), get<1>(b)))
            return max(get<0>(a), get<1>(a)) > max(get<0>(b), get<1>(b));
        return min(get<0>(a), get<1>(a)) > min(get<0>(b), get<1>(b));
    }
    return get<2>(a) < get<2>(b);
};
area merge(const area& other, const area& anoth, pii offset, const bool rev){
    if(rev)
        offset = pii(-offset.first, -offset.second);
    int roff= offset.first, coff= offset.second;
    int oh = other.size(), ow = other[0].size(), ah = anoth.size(), aw = anoth[0].size();
    int nw = coff > 0 ? (max(ow, aw + coff)) : (max(aw, ow - coff));
    int nh = roff > 0 ? (max(oh, ah + roff)) : (max(ah, oh - roff));
    #ifdef DMERGE
    cout << "merging : ";
    depii(offset);
    #endif
    int ostr, ostc, astr, astc;
    ostr = ostc = astr = astc = 0;
    if (roff > 0)
    {
        astr = roff;
    }
    else if (roff < 0)
    {
        ostr = (-roff);
    }
    if(coff > 0){
        astc = coff;
    }else if(coff < 0)
        ostc = (-coff);

    area newmap(nh, row(nw, '-'));
    for (int i = 0; i < nh; i++)
    {
        for (int j = 0; j<nw ; j++){
            int oi = i - ostr, oj = j - ostc, ai = i - astr, aj = j - astc;
            if(oi >= 0 && oi < oh && oj >= 0 && oj < ow){
                if(other[oi][oj] != '-')
                newmap[i][j] = other[oi][oj];
            }
            if(ai >= 0 && ai < ah && aj >= 0 && aj < aw){
                if(anoth[ai][aj] != '-')
                newmap[i][j] = anoth[ai][aj];
            }
        }
    }
    return newmap;
}

int main()
{

    int cases = 1;
    stringstream ss;
    while (true)
    {
        int N;
        string str;
        cin >> str;
        while (!all_of(al(str), [](char ch)
                    { return (ch) >= '0' && ch <= '9'; })){
            cin >> str;
        }
        ss = stringstream(str);
        ss >> N;
        if (!N)
            break;
        if (cases != 1)
            cout << endl;
        cout << "Case " << cases++ << endl;
        int w, h;
        vec<area> Areas;
        vec<bool> used(200, false);
        REP(k, N)
        {
            string str;
            cin >> str;
            while (!all_of(al(str), [](char ch)
                       { return (ch) >= '0' && ch <= '9'; })){
                cin >> str;
            }
            ss = stringstream(str);
            ss >> h;
            cin >> str;
            while (!all_of(al(str), [](char ch)
                       { return (ch) >= '0' && ch <= '9'; })){
                cin >> str;
            }
            ss = stringstream(str);
            ss >> w;
            area Map(h, row(w));
            REP(i, h)
            {
                string str;
                cin >> str;
                if(str.length() < w){
                    i--;
                    continue;
                }
                str = string(str.begin(), str.begin() + w);
                if (!all_of(al(str), [](char ch)
                            { return  isupper(ch) or ch == '-'; }))
                {
                    i--;
                    continue;
                }
                REP(j, w)
                {
                    Map[i][j] = str[j];
                }
            }
            
                Areas.eb(Map);
        }
        priority_queue<pmap, vec<pmap>,decltype(pqcmp)> pq(pqcmp);
        for (int i = 0; i < Areas.size(); i++)
        {
            #ifdef PALL
            cout << "Map of " << i << endl;
            printMap(Areas[i]);
            cout << "\n---------------\n";
            #endif
               /*
               bool nothing = all_of(al(Areas[i]), [](row &R)
                             { return all_of(al(R), [](char ch)
                                             { return ch == '-'; }); });
            if(nothing){
                continue;
            }
            */


            for (int j = i + 1; j < Areas.size(); j++)
            {
                pii offset(0, 0);
                bool rev;
                int score = matching(Areas[i], Areas[j], offset, rev);
                #ifdef DSCORE
                cout << i << ", " << j << " with score " << score << endl;
                depii(offset);
                #endif
                if(score > 0){
                    pq.emplace(i, j, score, offset, rev);
                }
            }
        }
        while(!pq.empty()){
            int a, b, score;
            pii offset;
            bool rev;
            tie(a, b, score, offset, rev) = pq.top();
            pq.pop();
            if(used[a] || used[b])
                continue;
            #ifdef DPROC
            cout << "\n----------\nmerging " << a << " with " << b << " s: " << score << endl;
            printMap(Areas[a]);
            printMap(Areas[b]);
            #endif
            area newmap = merge(Areas[a], Areas[b], offset, rev);
            #ifdef DPROC
            cout << "result:\n";
            printMap(newmap);
            cout << "\n";
            #endif
            used[a] = used[b] = true;
            for(int i = 0; i < Areas.size(); i++){
                if(used[i])
                    continue;
                pii offset(0, 0);
                bool rev;
                int score = matching(Areas[i], newmap, offset, rev);
                #ifdef DSCORE
                cout << i << ", " << Areas.size() << " with score " << score << endl;
                depii(offset);
                #endif
                if(score > 0){
                    pq.emplace(i, Areas.size(), score, offset, rev);
                }
            }
            Areas.eb(newmap);
        }
        int pcnt = 0;
        for (int i = 0; i < Areas.size(); i++)
        {
            if(used[i])
                continue;
            if(pcnt != 0)
                cout << endl;
            pcnt++;
            cout << "    MAP " << i + 1 << ":\n";
            cout << "    +";
            for (int c = 0; c < Areas[i][0].size(); c++){
                cout << "-";
            }
            cout << "+\n";

            for (int r = 0; r < Areas[i].size(); r++)
            {
                cout << "    |";
                for (int c = 0; c < Areas[i][r].size(); c++)
                {
                    cout << Areas[i][r][c];
                }
                cout << "|\n";
            }
            cout << "    +";
            for (int c = 0; c < Areas[i][0].size(); c++){
                cout << "-";
            }
            cout << "+\n";
        }
    }

    return 0;
}