// AC 2021-08-23 13:44:13
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

int seq[34];
bool sorted(const int n){
    for (int i = 0; i < n-1; i++){
        if(seq[i+1] < seq[i])
            return false;
    }
    return true;
}
int main(){
    string str;
    int orseq[35];
    while(getline(cin, str)){
        stringstream ss;
        int n = 0;
        ss << str;
        while(ss >> seq[n]){
            n++;
        }
        for (int i = 0; i < n;i++)
            cout << seq[i] << (i == n - 1 ? '\n' : ' ');
            /*
        do{
            cout << "permu: ";
            for (int i = 0; i < n; i++)
            {
                seq[i] = orseq[i];
                cout << seq[i] << (i == n - 1 ? '\n' : ' ');
            }
        */
            int bt = n - 1;
            vector<int> ANS;
            while(!sorted(n)){
                int maxi = 0;
                for (int i = 1; i <= bt; i++){
                    if(seq[i] > seq[maxi]){
                        maxi = i;
                    }
                }
                if(maxi == 0){
                    ANS.emplace_back(n - bt);
                }else if(maxi != bt){
                    ANS.emplace_back(n - maxi);
                    ANS.emplace_back(n - bt);
                    for (int i = 0; i <= maxi / 2; i++){
                        swap(seq[i], seq[maxi - i]);
                    }
                }else{
                    bt--;
                    continue;
                }
                //cout << "nowbt: " << bt << endl;
                for (int i = 0; i <= bt  / 2; i++)
                {
                    swap(seq[i], seq[bt - i]);
                }
                bt--;
                
                /*
                for (int i = 0; i < n; i++)
                    cout << seq[i] << (i == n - 1 ? '\n' : ' ');
                    */
            }
            //cout << "ANS:\n";
            for(auto it: ANS){
                cout << it << " ";
            }

            cout << "0\n";
        //} while (next_permutation(orseq, orseq + n));
    }
    return 0;
}