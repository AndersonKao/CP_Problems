#include&lt;iostream&gt;
#include&lt;cstring&gt;
#include&lt;algorithm&gt;
#define int long long
using namespace std;
const int maxn &#61; 2e5 &#43; 10;
int a[maxn],n;
void solve()
{
	int k;
	cin &gt;&gt;n&gt;&gt;k;
	for (int i &#61; 1; i &lt;&#61; n; i&#43;&#43;)
		cin &gt;&gt; a[i];
	int resn &#61; 1;
	a[n] &#61; 1;//最后一个不要白不要
	for (int i &#61; n-1; i &gt;&#61; 1; i--){
		if (a[i] &gt; resn) {
			resn&#43;&#43;;//代表此时智商是被减小的地方
			a[i] &#61; 1;
		}
		else//此时直接白嫖
			a[i] &#61; 1;
		if (resn &gt; k)//最大值是k
		{
			resn &#61; k;
			a[i] &#61; 0;
		}
		
	}
	for (int i &#61; 1; i &lt;&#61; n; i&#43;&#43;)
		cout &lt;&lt; a[i];
	cout &lt;&lt; endl;
}
signed main()
{
	int t;
	cin &gt;&gt; t;
	while (t--)
		solve();
	return 0;
}
