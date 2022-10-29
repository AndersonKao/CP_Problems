#include<bits/stdc++.h>
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
#define pi acosl(-1)
#define MEM(x) memset(x,0,sizeof(x))
#define MEMS(x) memset(x,-1,sizeof(x))
using namespace std;
struct node{
    node *l,*r;
    LL sum,sum2;
    int a,b;
    LL tag;
    LL vis,tag2;
    node(int _a,int _b):a(_a),b(_b),l(NULL),r(NULL),sum(0),sum2(0),tag(0),tag2(0),vis(0){
        
    }
}*root;
LL sum(node *n){ // value sum.
	ll res = 0;
	if ( n->vis )
		res += n->tag2 * ( n->b - n->a + 1);
	else
		res += n->sum;
	res += n->tag*( n->b - n->a + 1);
	return res;
//    return (n->vis?n->tag2*(n->b-n->a+1):n->sum)+n->tag*(n->b-n->a+1);
}
LL sum2(node *n){
	ll res = 0;	
	if ( n->vis )
		res += n->tag2 * ( n->b - n->a + 1) * ( n->b + n->a ) / 2;
	else
		res += n->sum2;
	res += n->tag * ( n->b - n->a + 1) * (n->b +n->a)/2
	return res;	
//    return (n->vis?n->tag2*(n->b-n->a+1)*(n->b+n->a)/2:n->sum2)+n->tag*(n->b-n->a+1)*(n->b+n->a)/2;
}
void pull(node *n){
    n->sum=sum(n->l)+sum(n->r);
    n->sum2=sum2(n->l)+sum2(n->r);
}
void push(node *n){
    if(n->vis){
        n->l->vis=1;
        n->l->tag2=n->tag2;
        n->l->tag=0;
        n->r->vis=1;
        n->r->tag2=n->tag2;
        n->r->tag=0;
    }
    n->vis=0;
    n->l->tag+=n->tag;
    n->r->tag+=n->tag;
    n->tag=0;
}
void build(node *n,LL *a){
    if(n->a==n->b){
        n->sum=a[n->a];
        n->sum2=a[n->a]*n->a;
        return;
    }
    int mid=(n->a+n->b)/2;
    n->l=new node(n->a,mid);
    n->r=new node(mid+1,n->b);
    build(n->l,a);
    build(n->r,a);
    pull(n);
}
void add(node *n,int l,int r,int k){
    if(n->a>=l&&n->b<=r){
        n->tag+=k;
        return;
    }
    if(n->b<l||n->a>r)return;
    push(n);
    add(n->l,l,r,k);
    add(n->r,l,r,k);
    pull(n);
}
void assign(node *n,int l,int r,int k){
    if(n->a>=l&&n->b<=r){
        n->tag2=k;
        n->tag=0;
        n->vis=1;
        return;
    }
    if(n->b<l||n->a>r)return ;
    push(n);
    assign(n->l,l,r,k);
    assign(n->r,l,r,k);
    pull(n);
}
pll query(node *n,int l,int r){
    if(n->a>=l&&n->b<=r){
        return mp(sum(n),sum2(n));
    }
    if(n->b<l||n->a>r)return mp(0,0);
    push(n);
    pll a=query(n->l,l,r);
    pll b=query(n->r,l,r);
    pull(n);
    return mp(a.x+b.x,a.y+b.y);
}
void solve(int T){
    int n,q;
    scanf("%d %d",&n,&q);
    LL a[200005];
    for(int i = 1;i<=n;i++)scanf("%lld",&a[i]);
    root=new node(1,n);
    build(root,a);
    while(q--){
        int t;
        scanf("%d",&t);
        if(t==1){
            int l,r,k;
            scanf("%d %d %d",&l,&r,&k);
            add(root,l,r,k);
        }
        else if(t==2){
            int l,r,k;
            scanf("%d %d %d",&l,&r,&k);
            assign(root,l,r,k);
            
        }
        else{
            int l,r;
            scanf("%d %d",&l,&r);
            pll p=query(root,l,r);

            int res=0;
            if(p.x==0){
                if(p.y==0)printf("Yes\n"),res=1;
                else printf("No\n");
            }
            else{
                if(p.y%p.x==0){
                    int x=p.y/p.x;
                    if(x>=l&&x<=r)printf("Yes\n"),res=1;
                    else printf("No\n");
                }
                else printf("No\n");
            }
        }
    }
    
}
int main(){
    int t=1;
  //  scanf("%d",&t);
    for(int T=1;T<=t;T++){
        solve(T);
    }
   // printf("%d\n",s.size());
}

/*
*/
