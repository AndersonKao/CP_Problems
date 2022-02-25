#include <iostream>
#include <algorithm>
using namespace std;
#define sport 1
#define code 2
#define rest 3
bool map[4][2]= {{0, 0},{0, 1},{1, 0},{1, 1}};
int n = 0;

int rec(int a[], int act, int j){
    if(j==n-1){
        if(map[a[j]][0] && map[a[j]][1]){
            return 1;
        }
        else if(map[a[j]][0]){
            if(act == sport)
                return 1;
            else
                return 0;
        }
        else if(map[a[j]][1]){
            if(act == code)
                return 1;
            else
                return 0;
        }
        else 
            return 1;
    }
    if(!j || act==rest){
        if(map[a[j]][0] && map[a[j]][1]) return min(rec(a, sport, j+1), min(rec(a, code, j+1), rec(a, rest, j+1) +1));
        else if(map[a[j]][0]) return min(rec(a, sport, j+1), rec(a, rest, j+1) + 1);
        else if(map[a[j]][1]) return min(rec(a, code, j+1), rec(a, rest, j+1) + 1);
        else return rec(a, rest, j+1) + 1;
    }
    if(act==sport){
        cout << 'sport' << '\n';
        if(map[a[j]][1]) 
            return min(rec(a, code, j+1), rec(a, rest, j+1) + 1);
        else
            return rec(a, rest, j + 1) + 1;
    }
    else{
        cout << 'sport' << '\n';
        if(map[a[j]][0]) return min(rec(a, sport, j+1), rec(a, rest, j+1) + 1);
        else
            return rec(a, rest, j + 1) + 1;
    }
    return 0;
}

int a[100000];
int main(){
    cin >> n;
    int m = n;
    while(m){
        cin >> a[n - m];
        m--;
    }
    
    cout << rec(a, rest, 0);
    return 0;
}