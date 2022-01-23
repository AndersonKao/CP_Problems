#include<bits/stdc++.h>
#pragma optimize(Ofast)
#define pb push_back
#define x first
#define y second
#define pdd pair<double,double>
#define pii pair<int,int>
#define pll pair<LL,LL>
#define mp make_pair
#define LL long long
#define ULL unsigned long long
#define sqr(x) ((x)*(x))
#define pi acos(-1)
#define MEM(x) memset(x,0,sizeof(x))
#define MEMS(x) memset(x,-1,sizeof(x))
using namespace std;
#define MXN 500005
int a[105];
pii p[105];
int w[105];
vector<int> v[105];
int match[105];
int match2[105];
int vis[105];
bool dfs(int x){
    if(vis[x])return false;
    vis[x]=1;
    for(auto it:v[x]){
        if(match[it]==-1||dfs(match[it])){
            match[it]=x;
            match2[x]=it;
            return true;
        }
    }
    return false;
}
bool dfs2(int x){
    if(vis[x])return false;
    vis[x]=1;
    for(auto it:v[x]){
        if(match[it]==-1||dfs2(match[it])){
            return true;
        }
    }
    return false;
}
int Max_match(vector<int> v){
    MEMS(match);
    int res=0;
    for(auto it:v){
        MEM(vis);
        if(dfs(it))res++;
    }
    return res;
}
int f[105];
int Find(int x){
    if(f[x]==x)return x;
    return f[x]=Find(f[x]);
}
vector<pii> E[105];
vector<int> stk;
bool dfs(int s,int f,int t){
    if(s==t)return true;
    for(auto it:E[s]){
        if(it.x!=f){
            stk.pb(it.y);
            if(dfs(it.x,s,t)){
                return true;
            }
            stk.pop_back();
        }
    }
    return false;
}
vector<int> mE[105];
int dis[105];
int from[105];
int inq[105];
void cal(int n,int m){
    vector<int> candidate;
    int ans=0;
    int MMax=0;
    for(int t = 1;t<n;t++){
        for(int j = 1;j<=n;j++)f[j]=j,E[j].clear();
        for(int j = 1;j<=m;j++)mE[j].clear();
        assert(Max_match(candidate)==candidate.size());
      //  for(auto it:candidate)printf("%d %d\n",it,match2[it]);
        int use[105];
        MEM(use);
        int oka[105],okb[105];
        for(auto it:candidate){
            int x=p[it].x,y=p[it].y;
            int a=Find(x),b=Find(y);
            assert(a!=b);
          //  printf("%d %d\n",x,y);
            f[a]=b;
            use[it]=1;
            E[x].pb(mp(y,it));
            E[y].pb(mp(x,it));
        }
        MEM(oka),MEM(okb);
        for(int i = 1;i<=m;i++){
          //  printf("%d\n",i);
            if(!use[i]){
                int a=Find(p[i].x),b=Find(p[i].y);
            //    printf("%d\n",i);
                if(a!=b)oka[i]=1;
                else{
                    dfs(p[i].x,0,p[i].y);
                    for(auto it:stk)mE[it].pb(i),assert(use[it]);
                    stk.clear();
                }
             //   printf("%d\n",i);
                MEM(vis);
                if(dfs2(i))okb[i]=1;
                else{
                    for(int j =1;j<=m;j++){
                        if(vis[j]&&i!=j){
                            mE[i].pb(j);
                            assert(use[j]);
                        }
                    }
                }
            }
           // printf("%d\n",i);
        }
        //printf("!\n");
        queue<int> q;
        for(int i=1;i<=m;i++){
            if(oka[i]){
                q.push(i);
                dis[i]=w[i];
            }
            else{
                dis[i]=-1e9;
            }
            from[i]=0;
        }
        while(!q.empty()){
            int x=q.front();
            q.pop();
            inq[x]=0;
            for(auto it:mE[x]){
                if(use[it]){
                    if(dis[it]<dis[x]-w[it]){
                        dis[it]=dis[x]-w[it];
                        from[it]=x;
                        if(!inq[it]){
                            q.push(it);
                            inq[it]=1;
                        }
                    }
                }
                else{
                     if(dis[it]<dis[x]+w[it]){
                        dis[it]=dis[x]+w[it];
                        from[it]=x;
                        if(!inq[it]){
                            q.push(it);
                            inq[it]=1;
                        }
                    }
                }
            }
        }
        int Max=-1e9,Maxi;
        for(int j = 1;j<=m;j++){
            if(okb[j]){
                if(Max<dis[j]){
                    Max=dis[j];
                    Maxi=j;
                }
            }
        }
        if(Max==-1e9){
            for(int k = t;k<n;k++){
                printf("-1");
                if(k==n-1)break;
                printf(" ");
            }
            printf("\n");
            cerr<<MMax<<endl;
            return;
        }
        ans+=Max;
        int now=Maxi;
        int tot=0;
        while(now){
            tot++;
            MMax=max(MMax,tot);
            use[now]^=1;
            now=from[now];
            
        }
        candidate.clear();
        for(int j = 1;j<=m;j++){
            if(use[j])candidate.pb(j);
        }
        printf("%d",ans);
        if(t==n-1)break;
        printf(" ");
    }
    printf("\n");
    cerr<<MMax<<endl;
}
void solve(int T){
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i = 1;i<=m;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        p[i]=mp(x,y);
        w[i]=sqrt(a[x]+a[y]);
    }
    int k;
    scanf("%d",&k);
    for(int i = 0;i<k;i++){
        int x;
        scanf("%d",&x);
        for(int j = 0;j<x;j++){
            int y;
            scanf("%d",&y);
            v[y].pb(i);
        }  
    }
    cal(n,m);
    /*
    int ans[105];
    MEMS(ans);
    for(int i = 0;i<(1<<m);i++){
        int res=0;
        int ok=1;
        for(int j=0;j<n;j++)f[j]=j;
        vector<int> v;
        for(int j = 0;j<m;j++){
            if(i&(1<<j)){
                res+=w[j+1];
                int a=Find(p[j+1].x),b=Find(p[j+1].y);
                if(a==b)ok=0;
                else f[a]=b;
                v.pb(j+1);
            }
        }
        if(Max_match(v)!=v.size())ok=0;
        if(ok){
            ans[__builtin_popcount(i)]=max(ans[__builtin_popcount(i)],res);
        }
    }
    for(int i = 1;i<n;i++)
    printf("%d ",ans[i]);
    printf("\n");*/
}
int main(){

    int t=1;0000;
  //  scanf("%d",&t);
    for(int i = 1;i<=t;i++){
       // cerr<<i<<endl;
        solve(i);
    }
    return 0;
}
/*
60.0 0.0 50.0 170.0 
3
40.0 0.0 0.0 0.0
5.0 20.0 5.0 170.0
95.0 0.0 95.0 80.0


0.0 1.0 4.0 1.0 
1
0.0 0.0 4.0 0.0
*/