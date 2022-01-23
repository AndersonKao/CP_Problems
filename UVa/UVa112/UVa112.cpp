// accept
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

bool solved;
bool DFS_ans(long long sum, long long asking){
    char ch;
    do{
        ch = getc(stdin);
    } while (ch != '(');
    do{
        ch = getc(stdin); 
    }
    while(!isdigit(ch) && ch != ')' && ch != '-');
    
    if(ch == ')'){
        return false;
    }
    
    ungetc((char)ch, stdin);
    long long data;
    scanf("%lld", &data);
    bool haveleft, haveright;
    haveleft = DFS_ans(sum + data, asking);
    haveright = DFS_ans(sum + data, asking);

    if(!haveleft && !haveright)
        if(sum + data == asking)
            solved = true;
    return true;
}
int main(){
    long long asking;

    while (scanf("%lld ", &asking) != EOF)
    {
        solved = false;
        DFS_ans(0, asking);
        if (solved)
            printf("yes\n");
        else printf("no\n");
        char ch;
        do{
            ch = getc(stdin);
        }while(ch != '\n');
    }
    return 0;
}
/* Sample Input
22 (5(4(11(7()())(2()()))()) (8(13()())(4()(1()()))))
20 (5(4(11(7()())(2()()))()) (8(13()())(4()(1()()))))
10 (3
(2 (4 () () )
(8 () () ) )
(1 (6 () () )
(4 () () ) ) )
5 ()
*/
/* Sample Output
yes
no
yes
no
*/