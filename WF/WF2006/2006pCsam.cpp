// ref: https://www.cnblogs.com/mmlz/p/6062464.html
/*
将每根杆子当做变量。
对于不在地面上的每个小球，我们可以列出一个方程。即每根与他相连的杆子给球的力的矢量和为(0,0,1)(注意：相互作用力等大反向)，由于是个三元组，我们需要把他拆成三个方程，对x,y,z分别列即可。最后是否静止只需判断方程有没有解即可。

对于是否稳定，即给予一个外力，方程是否还有解。但是在原方程上调整值复杂度太高，不可行。我们考虑问题的本质，即我们只改变常量，未知量的系数什么的都不变。因此，若消元后方程出现了0=0的情况，改变右边常量，方程明显无解了，反之肯定有解(可用增广矩阵来理解)。
*/
#include<cstring>
#include<cmath>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define eps (1e-8)
#define maxn (310)
int J,R,tot,con[maxn][maxn],T; double val[maxn][maxn];
void pG(){
	cout << "polynomials now ---------------:\n";
	for (int i = 0; i < 3 * J; i++)
	{
		cout << setw(3) << i << ": ";
		for (int j = 0; j <= R+1; j++){
			cout << setw(4) << val[i][j] << " ";
		}
		cout << endl;
	}
}


struct Node
{
	double x,y,z;
	inline void read() { scanf("%lf %lf %lf",&x,&y,&z); }
	friend inline Node operator -(const Node &a,const Node &b) { return (Node){ a.x-b.x,a.y-b.y,a.z-b.z }; }
}joints[maxn];

inline int guass()
{
	int now = 0;
	pG();
	for (int i = 1, j; i <= R; ++i)
	{
		for (j = now+1;j <= tot;++j) if (fabs(val[j][i]) > eps) break;
		if (j == tot+1) continue; ++now;
		for (int k = 1;k <= R+1;++k) swap(val[now][k],val[j][k]);
		for (j = 1;j <= tot;++j)
		{
			if (j == now) continue; double t = val[j][i]/val[now][i];
			for (int k = 1;k <= R+1;++k) val[j][k] -= t*val[now][k];
		}
		pG();
	}
	for (int i = now+1;i <= tot;++i) if (fabs(val[i][R+1]) > eps) return 0;
	cout << "now: " << now << endl;
	cout << "tot: " << tot<< endl;

	if (now < tot)
		return 1;
	return 2;
}
int main()
{
	freopen("pC.in","r",stdin);
	freopen("pCsam.out","w",stdout);
	while (++T)
	{
		tot = 0; memset(val,0,sizeof(val)); memset(con,0,sizeof(con));
		scanf("%d %d\n",&J,&R); if (!J) break;
		for (int i = 1;i <= J;++i) joints[i].read();
		for (int i = 1,a,b;i <= R;++i) scanf("%d %d",&a,&b),con[a][b] = con[b][a] = i;
		for (int i = 1;i <= J;++i)
		{
			if (fabs(joints[i].z) <= eps) continue; tot += 3;
			for (int j = 1;j <= J;++j)
			{
				if (!con[i][j]) continue; int id = con[i][j];
				Node vec = joints[i]-joints[j];
				val[tot-2][id] = vec.x,val[tot-1][id] = vec.y,val[tot][id] = vec.z;
			}
			val[tot][R+1] = 1;
		}
		int res = guass();
		if (!res) printf("Sculpture %d: NON-STATIC\n",T);
		else if (res == 1) printf("Sculpture %d: UNSTABLE\n",T);
		else printf("Sculpture %d: STABLE\n",T);
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
