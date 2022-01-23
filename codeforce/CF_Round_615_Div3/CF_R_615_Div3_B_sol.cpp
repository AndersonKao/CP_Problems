
#include<iostream>
#include<algorithm>
#include<map>
#define PI acos(-1)
#define ll long long
using namespace std;
 
struct point{
    int x,y;
}a[1050];
 
bool cmp(struct point a,struct point b)
{
    if(a.x==b.x)
        return a.y<b.y;
    return a.x <b.x;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    ll b,c,d,dis,n,m,x,y,z,p,q,i,j,k,l,flag=0,mx,mn,cnt=0,t,pos;
    cin>>t;
    for(i=0;i<t;i++){
        cin>>n;
        for(j=0;j<n;j++){
            cin>>a[j].x>>a[j].y;
        }
        sort(a,a+n,cmp);
        string s="";
        x=0,y=0;
        for(j=0;j<n;j++){
            if(a[j].x>=x && a[j].y>=y){
                for(k=x;k<a[j].x;k++)
                    s+='R';
                for(k=y;k<a[j].y;k++)
                    s+='U';
                x=a[j].x;
                y=a[j].y;
            }
            else{
                cout<<"NO"<<endl;
                break;
            }
        }
        if(j==n){
            cout<<"YES"<<endl<<s<<endl;
        }
    }
 
    return 0;
}