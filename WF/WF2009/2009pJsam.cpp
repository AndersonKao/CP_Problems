#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
int f[105][500],tmp[500];
int mid,l,r;
const int inf=1000000;
struct node
{
	int v,c,next;
}edge[300];
int g[105];
int tt=0,n;

int addedge(int a,int b,int c)
{
	edge[++tt].v=b;
	edge[tt].c=c;
	edge[tt].next=g[a];
	g[a]=tt;
	return 0;
}

int updata(int &a,int b)
{
	if(b>a)
		a=b;
	return 0;
}

int check(int a)
{
	if(a>=-mid&&a<=mid)
		return 1;
	return 0;
}

int dfs(int x,int fa)
{
	for(int i=0;i<=mid;i++)
		f[x][i]=-inf;
	f[x][0]=0;
	int y;
	for(int i=g[x];i;i=edge[i].next)
		if(edge[i].v!=fa)
		{
			dfs(edge[i].v,x);
			for(int j=0;j<=mid;j++)
			{
				tmp[j]=f[x][j];
				f[x][j]=-inf;
			}
			y=edge[i].v;
			for(int j=0;j<=mid;j++)	if(tmp[j]!=-inf)
				for(int k=0;k<=mid;k++) if(f[y][k]!=-inf)
				{
					if(check(j+k-edge[i].c)&&check(tmp[j]+f[y][k]-edge[i].c))
						updata(f[x][max(j,k-edge[i].c)],min(tmp[j],f[y][k]-edge[i].c));
					edge[i].c-=60;
					if(check(j+k-edge[i].c)&&check(tmp[j]+f[y][k]-edge[i].c))
						updata(f[x][max(j,k-edge[i].c)],min(tmp[j],f[y][k]-edge[i].c));
					edge[i].c+=60;
				}
		}
	return 0;
}

int main()
{
	int a,b,c,test=0;
	while(scanf("%d",&n)&&n)
	{
		for(int i=1;i<=n;i++)
			g[i]=0;
		tt=0;
		for(int i=1;i<n;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			c=c%60;
			addedge(a,b,c);
			addedge(b,a,c);
		}
		l=-1;r=300;
		while(l+1<r)
		{
			mid=(l+r)/2;
			dfs(1,0);
			int i;
			for(i=0;i<=mid;i++)
				if(f[1][i]>-inf)
					break;
			if(i==mid+1)
				l=mid;
			else
				r=mid;
		}
		printf("Case %d: %d\n",++test,r);
	}
	return 0;
}
