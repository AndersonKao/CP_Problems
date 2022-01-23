#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

string ans;
vector <string> anslist;
int counter, box_Num, max_x , max_y ;
bool flag ;
bool table[1005][1005];
void DFS(int x,int y) {
    // cout << ans;
    if(x>max_x || y > max_y) 
        return ;
    if(table[y][x])
        counter++;
    if(counter == box_Num){
        flag = true;
        // cout << ans << endl;
        anslist.push_back(ans);
        counter--;
        return ;
    }
    ans+="R";
    DFS(x+1,y);
    ans.pop_back();
    ans+="U";
    DFS(x,y+1);
    ans.pop_back();
    if(table[y][x])
        counter--;
}
int main(){
    int T; cin >> T;
    while(T--){

        //initialize
       int  x,y;
       max_x = max_y = 0;
       flag = false;
        ans.clear();
        counter = 0;
        while(!anslist.empty())
            anslist.pop_back();
        for(int i=0;i<=1000;i++){
            for(int j=0;j<=1000;j++){
                table[i][j] = false;
            }
        }

        cin >> box_Num;
        for(int i=0;i<box_Num;i++){
            cin >> x >> y;
            table[y][x] = true;
            max_x = max_x > x ? max_x : x;
            max_y = max_y > y ? max_y : y;
        }

        DFS(0,0);
        // for(int i=0;i<anslist.size();i++)
        //     cout << anslist[i] << endl;
        if(flag){
            cout << "YES\n";
            ans = anslist[0];
            for(int i=0;i<anslist.size();i++){
                if(ans > anslist[i])
                    ans = anslist[i];
            }
            cout << ans << endl;
        }
        else{
            cout << "NO\n";
        }
    }

    return 0;
}