#include <iostream>
#include <string.h>
int findstring(char s1[], char f1[])
{
    //bool flag;
    int lens = strlen(s1), lenf = strlen(f1);
    for (int i = 0; i < lens;i++)
        for (int j = 0; j < lenf;j++)
        {
            if(s1[i+j] != f1[j])
            {

                break;
            }
            if(j == lenf-1)
            {
                return i;
            }
        }
    return -1;
}


using namespace std;
int main()
{
    char s[] = "IamsAtsushiKao";
    char f[] = "Ats";
    cout << findstring(s,f );
    return 0;
    
}