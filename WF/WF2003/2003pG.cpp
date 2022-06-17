// AC 2022-06-17 07:19:50
// this is not compactable with c++20
#include <bits/stdc++.h>
using namespace std;
#define yccc cin.tie(0), ios_base::sync_with_stdio(false);
/*
#define DEFINITION
#define DATAIN
#define CHECKPLACE
*/
#define eb emplace_back
#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define debug(x) cout << #x << " >: " << x << endl;

template <typename T>
using vec = vector<T>;
using pib = pair<int, bool>;

const int byte = 8;
const int lomask = ((1 << 8) - 1);
const int himask = ((1 << 8) - 1) << 8;

struct module
{
    vec<int> code;
    vec<string> symref;
    friend ostream &operator<<(ostream &os, const module &mod);
};
ostream &operator<<(ostream &os, const module &mod){
    cout << "symref size dec: " << mod.symref.size() << ", hex: " << hex << mod.symref.size() << endl;
    REP(i, mod.symref.size()){
        cout << i << ": " << mod.symref[i] << endl;
    }
    cout << "codesize dec: " << mod.code.size() << ", hex: " << hex << mod.code.size() << endl;
    REP(i, mod.code.size()){
        cout << mod.code[i] << " ";
        if((i + 1) % 10 == 0)
            cout << endl;
    }
    return os;
}
vec<module> mods;
map<string, pair<int, bool>> sym2addr;
set<string> symset;

uint16_t rotl16a(uint16_t x, uint16_t n){
    return (x << n) | (x >> (16 - n));
}
uint16_t checksum(){
    uint16_t ans = 0;
    REP(i, mods.size()){
        vec<int> &codeV  = mods[i].code;
        REP(j, codeV.size()){
            ans = rotl16a(ans, 1);
            uint16_t x = codeV[j];
            ans += x;
        }
    }
    return ans;
}

int main()
{
    yccc;
    int CaseN = 1;
    char op;
    while (cin >> op){
        if(op == '$')
            break;

        mods.clear();
        sym2addr.clear();
        symset.clear();

        int curaddr = 0x100;
        module *curmod = new module;
        do
        {
            if (op == '$')
                break;
            if (op == 'D') {
                string symname;
                int offset;
                cin >> symname >> hex >> offset;
                map<string, pib>::iterator iter;
                if ((iter = sym2addr.find(symname)) == sym2addr.end()) {
                    sym2addr.emplace(symname, pib(curaddr + offset, false));
                    symset.emplace(symname);
                    #ifdef DEFINITION
                    cout << "define symebol " << symname << " at " << hex << curaddr + offset << endl;
                    #endif
                }
                else {
                    iter->second.second = true;
                }
            }
            else if (op == 'E') {
                string symname;
                cin >> symname;
                curmod->symref.eb(symname);
                symset.emplace(symname);
            }
            else if (op == 'C') {
                int len;
                cin >> hex >> len;
                REP(i, len){
                    string codedata;
                    cin >> codedata;
                    if (codedata == "$") {
                        curmod->code.eb(-1);
                    }
                    else
                    {
                        stringstream ss;
                        ss << codedata;
                        int val;
                        ss >> hex >> val;
                        curmod->code.eb(val);
                    }
                    curaddr += 1;
                }
            }
            else if (op == 'Z') {
                mods.eb(*curmod);
                delete curmod;
                curmod = new module;
            }
        } while (cin >> op);
        delete curmod;
        #ifdef DATAIN
        REP(i, mods.size()){
            cout << mods[i] << endl;
        }
        for(auto&e: sym2addr){
            cout << "symbol: " << e.first << " at " << e.second.first << endl;
        }
        #endif
        REP(i, mods.size()){
            vec<int> &codeV = mods[i].code;
            vec<string> &symrefV = mods[i].symref;
            REP(j, mods[i].code.size())
            {
                if(codeV[j] == -1){
                    int symid = codeV[j + 1];
                    map<string, pib>::iterator it;
                    int symval;
                    if ((it = sym2addr.find(symrefV[symid])) == sym2addr.end()){
                        symval = 0;
                    }
                    else {
                        symval = sym2addr[symrefV[symid]].first;
                    }
                    codeV[j] = (symval & himask) >> byte;
                    codeV[j + 1] = symval & lomask;
                    #ifdef MASKING
                    cout << "found " << symrefV[symid] << " is at " << symval << endl;
                    debug(codeV[j]);
                    debug(codeV[j+1]);
                    #endif
                }
            }
        }
        #ifdef CHECKPLACE
        cout << "\n after replacement ------------------\n";
        REP(i, mods.size())
        {
            cout << mods[i] << endl;
        }
        #endif
        if(CaseN != 1)
            cout << endl;
        uint16_t checkans = checksum();
        cout << "Case " << dec << CaseN++ << ": checksum = ";
        cout << uppercase << hex << setfill('0') << setw(4) << checkans<< endl;
        cout << " SYMBOL   ADDR\n--------  ----\n";
        for (const string &e : symset)
        {
            cout << e;
            REP(i, 10 - e.length()){
                cout << " ";
            }
            map<string, pib>::iterator it;
            if ((it = sym2addr.find(e)) == sym2addr.end()) {
                cout << "????";
            }
            else {
                cout << uppercase << setfill('0') << setw(4) << std::hex << it->second.first;
                cout.width(0);
                cout.fill(' ');
                if (it->second.second)
                    cout << " M";
            }
            cout << endl;
        }
    }
        return 0;
}