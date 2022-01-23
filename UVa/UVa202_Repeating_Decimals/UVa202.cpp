#include <stdio.h>
#include <string.h>
char number[101];
int main()
{
    int a, b;
    while (scanf("%d%d", &a, &b) == 2)
    {
        int intergerPart = a / b;
        int r = a % b, flag = 1, i = 0;
        while (r > 0 && i <= 100)
        {
            int num = (r / b);
            if (!num)
            {
                r *= 10;
                if (!flag)
                {
                    number[i++] = '0';
                }
                else
                    flag = 0;
                continue;
            }
            number[i++] = (char)(num + 48);
            r = (r % b) * 10;
        }
        number[i] = '\0';
        printf("%s\n", number);
        int anslen, starter, len = strlen(number);
        char s1[120];
        char s2[120],s3[120];
        flag = 1;
        char *pointer1, *pointer2;
        while(flag)
        {
            for (anslen = 1;anslen<)
                pointer1 = &number[starter]
        }
    }

    return 0;
}