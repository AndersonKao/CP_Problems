// Finished but has not been Judged yet
// WA 2019-10-21 13:40:59
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int maxn = 30;
int n;
vector<int> pile[maxn];
void findit(int target, int &p,int &h ){
    //cout << "callfindit\n";
    for (p = 0; p < n;p++){
        int size = pile[p].size();
        for ( h = 0; h < size;h++)
            if(pile[p][h] == target)
                return;
    }
        
}
void clear_above(int p,int h){
   // cout << "callclear p=" << p << " h=" << h << "\n";
    int size = pile[p].size();
    for (int i = h + 1; i < size;i++){
        //cout << "idomove\n";
        int k = pile[p][i];
        pile[k].push_back(k);
        pile[p].pop_back(); // or pile[p].resize(h+1);
    }
    
}
void pile_over(int pa,int ha,int pb)
{
   // cout << "callpileover\n";
    int size = pile[pa].size();
    for (int i = ha; i < size;i++){
        int k = pile[pa][i];
        pile[pb].push_back(k);
        pile[pa].pop_back();
    }
}
void printit(){
    for (int i = 0; i < n;i++){
        int size = pile[i].size();
        printf("%d: ", i);
        for (int j = 0; j < size;j++){
            printf("%d", pile[i][j]);
            if(j!=size-1)
                printf(" ");
        }
        printf("\n");
    }
}
int main()
{
    cin >> n;
    string s1, s2;
    for (int i = 0; i < n; i++)
        pile[i].push_back(i);
        //printit();
    int a, b, pa, pb,ha, hb;
    while (cin >> s1)
    {
        if(s1 == "quit")
            break;
        cin >> a >> s2 >> b;
        findit(a, pa, ha);
        findit(b, pb, hb);
        if(s1 == "move")
            clear_above(pa, ha);
        if(s2 == "onto")
            clear_above(pb, hb);
        pile_over(pa, ha, pb);
         //printit();

    }
    printit();
    return 0;
/* 10
move 9 onto 1
move 8 over 1
move 7 over 1
move 6 over 1
pile 8 over 6
pile 8 over 5
move 2 over 1
move 4 over 9
quit */
}