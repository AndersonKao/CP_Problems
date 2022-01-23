// AC 2019-10-21 13:52:35
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>
#define _for(i, a, b) for (int i=(a); i < (b); i++)
using namespace std;
int readint(void);
//double makeitttt(double *ptr_mass, int num);
int charnumtointnum(char k){
    return (int)k - 48;
}
int main(){
    double W[4];
    double ans = 0;
    // 0-->C 1-->H 2-->O 3-->N
    W[0] = 12.01, W[1] = 1.008, W[2] = 16.00, W[3] = 14.01;
    int T = readint();
    cin.get();
    char Molars[T][80];
    _for(i,0,T){
        cin.getline(Molars[i],80);
    }

        
    int decider,nums;
    _for(i,0,T)
    {
        
        ans = 0;

        for (int cnt = 0; cnt < strlen(Molars[i]);cnt++)
        {
            if(isupper(Molars[i][cnt]))
            {
                //cout << "counting" << endl;
                if(Molars[i][cnt] == 'C'){
                    decider = 0;
                }else if(Molars[i][cnt] == 'H'){
                    decider = 1;
                }else if(Molars[i][cnt] == 'O'){
                    decider = 2;
                }else if(Molars[i][cnt] == 'N'){
                    decider = 3;
                }
                if(isdigit(Molars[i][cnt+1])){
                        if(isdigit(Molars[i][cnt+2])){
                            nums = charnumtointnum(Molars[i][cnt + 1]) * 10 + charnumtointnum(Molars[i][cnt + 2]);
                            ans += W[decider] * nums;
                            //cout << "+" << nums << 'X' << Molars[i][cnt] << W[decider] * nums << endl;
                        }else{
                            nums = charnumtointnum(Molars[i][cnt+1]);
                            ans += W[decider] * nums;
                            // cout << "+" << nums << 'X' << Molars[i][cnt] << W[decider] * nums << endl;
                        }
                        
                }else{
                    ans += W[decider];
                   // cout << "+" << Molars[i][cnt] << W[decider] << endl;
                }
            }

        }
        printf("%.3f\n", ans);
    
       
    }
    
    return 0;
}
int readint(void){
    int x;
    cin >> x;
    return x;
}
