#include <iostream>
#include <cstring>
#include <string>
using namespace std;
 
bool flag;
bool visited[2000005];
void dfs(const string &str,const int range,int index){
    if(index==str.length()+1)
        flag = true;
    if(index > str.length()+1)
        return;
    if(visited[index])
        return ;
    visited[index] = true;
    bool dir;
    if(index == 0 || str[index-1] == 'R')
        dir = true;
    else
        dir = false;
    for(int i = 1;i<=range;i++)
    {
        if(dir)
            dfs(str,range,index + i);
        else
            dfs(str,range,index - i);
    }
    visited[index] = false;
}
 
int main(){
    int T;
    cin >> T;
    while(T--){
        string str;
        cin >> str;
        int range;
        bool allR = true,allL = true;
        for(int i =0;i<str.length();i++){
            if(str[i] == 'R')
                allL = false;
            else if(str[i] == 'L')
                allR = false;
            if(!allR && !allL)
                break;
        }
        if(allR){
            cout << "1\n";
            continue;
        }else if(allL){
            cout << str.length()+1 << "\n";
            continue;
        }
        for(range = 1;range<=str.length();range++){
            flag = false;
            memset(visited,0,sizeof(visited));
            dfs(str,range,0);
            if(flag){
                cout << range << "\n";
                break;
            }
        }
        if(range == str.length()+1)
            cout << range << "\n";
    }
    return 0;
}