// AC Aug/24/2020 15:05UTC+8
#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;
// #define LOCAL_TEST
vector<int> G[27];
int indeg[27] = {0};
bool inqu[27] = {false};
string ans = "";
void Ginfor(){
    for (int i = 0; i < 26; i++){
        cout << (char)(i + 'a') << ": ";
        for (int j = 0; j < G[i].size(); j++){
            cout << (char)(G[i][j] + 'a') << " ";
        }
        cout << endl;
    }
}
void infor(){
    for (int i = 0; i < 26; i++){
        cout << indeg[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 26; i++){
        cout << inqu[i] << " ";
    }
    cout << endl;
    
}
int main(){
    #ifdef LOCAL_TEST
        freopen("test1.txt", "r", stdin);
    #endif
    int N;
    cin >> N;
    string str[105];
    for (int i = 0; i < N; i++){
            cin >> str[i];
    }
    for (int i = 0; i < N; i++){
        for (int j = i + 1; j < N; j++){
            int index = 0;
            int minLen = min(str[i].length(), str[j].length());
            while(index < minLen && str[i][index] == str[j][index])
                index++;
            if(index == minLen){
                if(str[j].length() < str[i].length()){
                    cout << "Impossible\n";
                    return 0;
                }
                continue;
            }
            G[(int)(str[i][index] - 'a')].emplace_back((int)(str[j][index] - 'a'));
            indeg[(int)(str[j][index] - 'a')]++;
        }
    }
    // Ginfor();
    queue<int> q;
    for (int i = 0; i < 26; i++){
        if(indeg[i] == 0){
            q.emplace(i);
            inqu[i] = true;
        }
    }
    // for (int i = 0; i < q.size(); i++){
    //     cout << (char)((char)q[i] + 'a') << " ";
    // }
    // cout << endl;
    // infor();
    while (q.size())
    {
        int v = q.front();
        q.pop();
        ans += (char)((char)v + 'a');
        for (int w : G[v])
        {
            if(indeg[w] > 0)       
                indeg[w]--;

            if (indeg[w] == 0 && !inqu[w])
            {
                q.emplace(w);
                inqu[w] = true;
            }
        }
        // infor();
    }
    // cout << ans << endl;
    if(ans.length() != 26){
        cout << "Impossible\n";
    }else{
        cout << ans << endl;
    }
    return 0;
}