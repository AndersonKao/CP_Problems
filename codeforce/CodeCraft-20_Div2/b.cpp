#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int anstime;
char ans[5005],str[5005],tmpstr[5005];
void swap(char *a,char *b){
    char c = *a;
    *a = *b;
    *b = c;
}

void reverse(char * str, int l,int r){
    char tmpL = l, tmpR = r;
    while(tmpL < tmpR){
        swap(str+tmpL,str+tmpR);
        tmpL++;
        tmpR--;
    }
}

void swep(char * str,int k,int len){
    for(int i = 0;i<len - k + 1;i++){
        reverse(str,i,i+k-1);
    }
}

void dp(char * str,int len){
    for(int i = 2;i<=len; i++)
    {
        memset(tmpstr,0,sizeof(tmpstr));
        strncpy(tmpstr,str,len);
        swep(tmpstr,i,len);
        if(strncmp(ans,tmpstr,len) > 0){
           strncpy(ans,tmpstr,len);
           anstime = i;
        }
    }
}

int main(){
    int T;
    cin >> T;
    while(T--){
        int Len;
        memset(str,0,sizeof(str));
        memset(ans,0,sizeof(ans));
        anstime = 1;
        cin >> Len;
        cin >> str;
        strncpy(ans,str,Len);
        dp(str,Len);
        cout << ans << endl << anstime << endl;
    }
    
    return 0;
}