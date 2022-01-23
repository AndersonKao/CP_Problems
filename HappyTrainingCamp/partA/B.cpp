#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

void convertTime(char * str, int *hour, int *minute)
{
    unsigned int len = strlen(str);
    *hour = 0;
    *minute = 0;
    if(len == 5)
    {
        *hour = (str[0] - '0') * 10 + (str[1] - '0');
        *minute = (str[3] - '0') * 10 + (str[4] - '0');
    }else if(len == 4){
        *hour = (str[0] - '0');
        *minute = (str[2] - '0') * 10 + (str[3] - '0');
    }
}


int main(){

    int hour, minute;
    char str[10];
    double hourangle, minuteangle;
    while(~scanf("%s", str))
    {
        hourangle = minuteangle = 0.0;
        convertTime(str, &hour, &minute);
        if(hour == 0 && minute == 0){
            break;
        }
//        printf("%d : %d entered.\n", hour, minute);
        hourangle = hour * 30.0 + minute * 30.0 / 60.0;
        minuteangle = minute * 6.0;
        
        double ans1 = max(hourangle, minuteangle) - min(hourangle, minuteangle);
        double ans2 = 360.0 - ans1;
        printf("%.3lf\n", min(ans1, ans2));
    }
        
    

    return 0;
}