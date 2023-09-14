// AC 2020/08/09 13:46:45
#include <iostream>
using namespace std;
char origin_str[100005];
char Ans_str[100005]; // str-> string -> 字串 ans -> answer
int counts[500] = {0};
int main(){
    int Len, Index = 0;
    cin >> Len;
    cin >> origin_str;
    for(int i = 0; i < Len; i++){
        cin >> origin_str[i];
        // cout << origin_str[i] << endl;
        if(origin_str[i] >= 'A' && origin_str[i] <= 'Z'){ // 如果是大寫
            origin_str[i] += ('a' - 'A');
        }

        if(origin_str[i] >= 'a' && origin_str[i] <= 'z'){ // 統計英文字母 以及 紀錄答案字串
            Ans_str[Index] = origin_str[i];
            counts[Ans_str[Index]]++; // Ans_str[Index] = 'z', 'z' - 'a'
            Index++;
        }
    }
    Ans_str[Index] = '\0';
    
    cout << Ans_str << endl;

    for(int i = 0; i < 26; i++){
        cout << counts[i];
        if(i == 25)
            cout << '\n';
        else
            cout << ' ';
    }
    return 0;
}