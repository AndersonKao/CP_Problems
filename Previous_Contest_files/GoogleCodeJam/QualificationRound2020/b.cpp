#include <iostream>
#include <string>
using namespace std;

string rightpara = "))))))))))";
string leftpara = "((((((((((";

int main(){
    string str;
    int T, cases = 0;
    cin >> T;
    while(T--){
        cin >> str;
        printf("Case #%d: ", ++cases);
        // for(int i = 0; i < str.length();i++){
        //     if(str[i] != '(' && str[i] != ')'){
        //         int times = str[i] - '0';
        //         str.insert(i+1,"))))))))))",times);
        //         str.insert(i,"((((((((((",times);
        //         i = i + times * 2;
        //     }
        //     cout << str << endl;
        // }
        // for(int i = 0;i < str.length();i++){

        // }
        int current,rightnum,leftnum;       
        for(int i = 0; i < str.length() ;i++){
            current = str[i] - '0';
            if(i == 0){
                for(int j = 0;j < current;j++){
                    printf("(");
                }
                printf("%c",str[i]);
                if(str.length() != 1){
                    rightnum = current - (str[i+1] - '0');
                    if(rightnum > 0){
                        for(int j = 0; j < rightnum; j++){
                            printf(")");
                        }
                    }
                }else{
                    for(int j = 0;j < current;j++){
                        printf(")");
                    }
                }
            }else if(i == str.length()-1){
                leftnum = current - (str[i-1] - '0');
                if(leftnum > 0){
                    for(int j = 0; j < leftnum; j++){
                        printf("(");
                    }
                }
                printf("%c",str[i]);
                for(int j = 0;j < current;j++){
                    printf(")");
                }
            }else{
                current = str[i] - '0';
                leftnum = current - (str[i-1] - '0');
                rightnum = current - (str[i+1] - '0');
                for(int j = 0;j < leftnum;j++){
                    printf("(");
                }
                printf("%c",str[i]);
                for(int j = 0;j < rightnum;j++){
                    printf(")");
                }
            }
        }
        printf("\n");
    }

    return 0;
}