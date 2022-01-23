#include <iostream>
#include <cstring>
using namespace std;

char str[1005];
int take[1005];
int ans = 0;

void dp(int L,int R){
    bool leftfind = false,rightfind = false;
    int newL= L,newR = R;
    // cout << "start!";
    while(newL < newR){
        leftfind = rightfind = false;
        int i ,j;
        for( i = newL;i<newR;i++){
            if(str[i] == '('){
                leftfind = true;
                break;
            }
        }
        for( j=newR;j>newL;j--){
            if(str[j] == ')'){
                rightfind = true;
                break;
            }
        }
        if(leftfind && rightfind){
            ans+=2;
            take[i] = take[j] = 1;
            newL = i+1;
            newR = j-1;
        }else{
            break;
        }
    }
}

int main(){
    cin >> str;
    int len = strlen(str);
    dp(0,len-1);
    if(ans > 0){
        cout << 1 << endl;
        cout << ans << "\n";
        for(int i=0;i< len;i++){
            if(take[i]){
                cout << i+1 << " ";
            }
        }
        cout << endl;

    }else{
        cout << 0 << "\n";
    }
    return 0;
}