// 2019-10-20 14:04:34 AC
#include <stdio.h>

int main(){
    int N;
    scanf("%d", &N);
    int meetingtime[4];
    int wifetime[4];
    for (int i = 0; i < N;i++){
        scanf("%d:%d %d:%d",&wifetime[0],&wifetime[1],&wifetime[2],&wifetime[3]);
        scanf("%d:%d %d:%d", &meetingtime[0], &meetingtime[1], &meetingtime[2], &meetingtime[3]);
        int meetime[2];
        meetime[0] = meetingtime[0] * 60 + meetingtime[1];
        meetime[1] = meetingtime[2] * 60 + meetingtime[3];
        int wifet[2];
        wifet[0] = wifetime[0] * 60 + wifetime[1];
        wifet[1] = wifetime[2] * 60 + wifetime[3];
        if(((meetime[0]<wifet[0]) && (meetime[1]<wifet[0]))||( (meetime[0]>wifet[1]) && (meetime[1]>wifet[1])))
            printf("Case %d: Hits Meeting\n", i + 1);
        else
            printf("Case %d: Mrs Meeting\n", i + 1);
    }

    return 0;
}