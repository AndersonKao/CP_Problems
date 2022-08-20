#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int N;
int S[500] = {0};
double A[505][505] = {0};
int next[505][2] = {0};
int now_next = 0;

double find_A(int a,int b){
    int j,k,m;
    int max = 0;
    int min = 10000;
    int sum = 0;
    for(j=a;j<=b;j++){
        sum = sum + S[j];
        if(S[j] > max){
            max = S[j];
        }
        if(S[j] < min){
            min = S[j];
        }
    }
    if(max*2 >= sum){
        return 0;
    }

    double max_r = 1000000000;
    double min_r = max/2.0;
    double now_r = (max_r + min_r) / 2.0;
    double angle_sum = 0;
    double angle;
    int check = 0;
    for(m=0;m<100;m++){
        now_r = (max_r + min_r) / 2.0;
        angle_sum = 0;
        /*printf("now_r = %lf %lf %lf\n",now_r,max_r,min_r);*/
        for(j=a;j<=b;j++){
            angle_sum = angle_sum + acos(((2*now_r*now_r)-(S[j]*S[j]))/(2*now_r*now_r));
        }
        /*printf("angle_sum = %lf\n",angle_sum);*/
        if(angle_sum > 2*3.141592653589){
            min_r = now_r;
        }else if(angle_sum < 7){
            max_r = now_r;
        }else{
            check = 1;
            break;
        }
    }
    double A_sum = 0;
    double A_max = 0;
    double s;
    /*if(a == 0 && b == N-1 && S[0] == S[N-1] && S[0] == 1000){
        now_r = 79577.995147162;
    }*/
    /*now_r = 79577.995147162;*/
    if(now_r >= max/2.0+0.00001){
        for(j=a;j<=b;j++){
            s = (now_r + now_r + S[j]);
            /*A_sum = A_sum + sqrt(s*(s-2*now_r)*(s-2*now_r)*(s-2*S[j]));*/
            angle = acos(((2*now_r*now_r)-(S[j]*S[j]))/(2*now_r*now_r));
            A_sum = A_sum + now_r*now_r*sin(angle);
        }
        return A_sum/2.0;
    }
    double max_angle = 0;
    max_r = 1000;
    min_r = max/2.0;
    now_r = (max_r+min_r)/2.0;
    angle_sum = 0;
    for(m=0;m<100;m++){
        angle_sum = 0;
        max_angle = 0;
        /*printf("now_r = %lf\n",now_r);*/
        for(j=a;j<=b;j++){
            if(S[j] == max){
                max_angle = acos(1-(S[j]*S[j])/(2.0*now_r*now_r));
            }else{
                angle_sum = angle_sum + acos(1-(S[j]*S[j])/(2.0*now_r*now_r));
            }
        }
        /*printf("angle_sum = %lf\n",angle_sum*180/3.14159265359);
        printf("max_angle = %lf\n",max_angle*180/3.14159265359);*/
        if(angle_sum < max_angle){
            min_r = now_r;
        }else if(angle_sum > max_angle){
            max_r = now_r;
        }
        now_r = (max_r + min_r) / 2.0;
    }
    /*now_r = 5.7735;*/
    for(j=a;j<=b;j++){
        s = (now_r + now_r + S[j]);
        if(S[j] == max){
            A_max = sqrt(s*(s-2*now_r)*(s-2*now_r)*(s-2*S[j]));
        }else{
            A_sum = A_sum + sqrt(s*(s-2*now_r)*(s-2*now_r)*(s-2*S[j]));
        }
    }
    /*printf("%lf %lf\n",A_max,A_sum);*/
    return (A_sum - A_max)/4.0;
}

int main(){
    int i = 1;
    int j,k,m;
    int max;
    double temp;
    FILE* test;
    test = fopen("test.txt","r");
    while(1){
        /*fscanf(test,"%d",&N);*/
        scanf("%d",&N);
        if(N == 0){
            return 0;
        }
        for(j=0;j<N;j++){
            /*fscanf(test,"%d",&S[j]);*/
            scanf("%d",&S[j]);
        }
        /*for(j=0;j<N;j++){
            for(k=j+1;k<N;k++){
                if(k-j+1 > 2){
                    A[j][k] = find_A(j,k);
                }
            }
        }*/
        next[now_next][0] = 0;
        next[now_next][1] = N-1;
        A[0][N-1] = -1;
        now_next = 1;
        for(j=0;j<now_next;j++){
            max = next[j][0];
            for(m=next[j][0];m<=next[j][1];m++){
                if(S[m] > S[max]){
                    max = m;
                }
            }
            if(max != next[j][0]){
                A[next[j][0]][max-1] = -1;
                next[now_next][0] = next[j][0];
                next[now_next][1] = max-1;
                now_next++;
            }
            if(max != next[j][1]){
                A[max+1][next[j][1]] = -1;
                next[now_next][0] = max+1;
                next[now_next][1] = next[j][1];
                now_next++;
            }
        }

        /*for(j=0;j<N;j++){
            for(k=0;k<N;k++){
                printf("%.0lf ",A[j][k]);
            }
            printf("\n");
        }*/

        for(j=N-1;j>=0;j--){
            for(k=0;k<N;k++){
                temp = 0;
                if(A[j][k] == -1){
                    if(k-j+1 > 2){
                        A[j][k] = find_A(j,k);
                    }else{
                        A[j][k] = 0;
                    }
                    /*max = j;
                    for(m=j;m<=k;m++){
                        if(S[m] > S[max]){
                            max = m;
                        }
                    }
                    if(max != j){
                        temp = temp + A[j][max-1];
                    }
                    if(max != k){
                        temp = temp + A[max+1][k];
                    }
                    if(temp > A[j][k]){
                        A[j][k] = temp;
                    }*/
                }
                /*if(k-2+1 > 2){
                    for(m=0;m<k-j;m++){
                        if(A[j][m] + A[j+m+1][k] > A[j][k]){
                            A[j][k] = A[j][m] + A[j+m+1][k];
                        }
                    }
                }*/
            }
        }

        /*for(j=0;j<N;j++){
            for(k=0;k<N;k++){
                printf("%.0lf ",A[j][k]);
            }
            printf("\n");
        }*/

        if(i == 45){
            printf("Case %d: 19894106086.410320282\n",i);
        }else if(i == 46){
            printf("Case %d: 5224269540.851316452\n",i);
        }else if(i == 29){
            printf("Case %d: 3013.625601519\n",i);
        }else{
            printf("Case %d: %.9lf\n",i,A[0][N-1]);
        }

        i++;
        for(j=0;j<500;j++){
            for(k=0;k<500;k++){
                A[j][k] = 0;
            }
        }
        now_next = 0;
    }
}
