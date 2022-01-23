// I need test numbers
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
int main(){
    int T;
    cin >> T;
    while(T--){
        int H, M;
        string sH, sM;
        string nowTime;
        cin >> nowTime;
        if((nowTime == "12:00")||(nowTime=="12:30")||(nowTime=="06:00")||(nowTime=="18:00")||(nowTime=="00:00")||(nowTime=="00:30"))
        {
            cout << nowTime << "\n";
            continue;
        }
        sH.assign(nowTime, 0, 2);
        sM.assign(nowTime, 3, 2);
        stringstream ss;
        ss << sH;
        ss >> H;
        ss.str("");
        ss.clear();
        ss << sM;
        ss >> M;
        ss.str("");
        ss.clear();
        //cout << H << ":" << M << endl;
        
            
        if (H>=12){
            H = 18 - H;
            if(M==0)
                H += 18;
            else
                H += 17;
        }else if(H < 12){
            if(M==0){
             if(H!=6 && H!=0)
                H = 12 - H;
            }else{
                H = 11 - H;
            }
        }

        if(M!=0 && M!= 30)
            M =  60-M;
        
        ss << H;
        ss >> sH;
        ss.str("");
        ss.clear();
        ss << M;
        ss >> sM;
        ss.str("");
        ss.clear();
        //cout << "int:" << H << ":" << M << endl;
        //cout <<"string:" << sH << ":" << sM << endl;
        if(M<10)
            sM.insert( 0,"0");
        if(H<10)
            sH.insert( 0,"0");
        cout << sH << ":" << sM << endl;
    }
    return 0;
}