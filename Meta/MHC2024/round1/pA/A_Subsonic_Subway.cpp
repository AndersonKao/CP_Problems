#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define eb emplace_back
#define st first
#define nd second
#define pr printf
#define sc scanf
#define ll long long int

int main() {
    int _case;
    sc("%d",&_case);
    for(int i=0;i<_case;i++){
        pr("Case #%d: ",i+1);
        int N;
        int test = 0;
        double min_spd = 0;
        sc("%d",&N);
        vector<pair<int,int>> time(N+1);
        for(int j=1;j<=N;j++){
            sc("%d %d",&time[j].st,&time[j].nd);
            min_spd = max(min_spd,(1.0)*j/time[j].nd);
        }
        //pr("%.20lf\n",min_spd);
        for(int j=1;j<=N;j++){
            if((1/min_spd)*j < 1.0*time[j].st){
                //pr("%lf %lf\n",min_spd*j,1.0*time[j].st);
                test = 1;
                break;
            }
        }
        if(test == 0) pr("%.10lf\n",min_spd);
        else pr("-1\n");
    }
    
    return 0;
}
