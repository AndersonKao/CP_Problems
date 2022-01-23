#include <iostream>
using namespace std;
int Robo[105];
int Bionic[105];
int main(){
    int Num;
    cin >> Num;
    for(int i =0;i< Num;i++)
        cin >> Robo[i];
    for(int i=0;i< Num;i++)
        cin >> Bionic[i];
    int RoboOnly = 0;
    int BioOnly = 0;
    int Both = 0;
    for(int i =0;i< Num;i++){
        if(Robo[i] && !Bionic[i])
            RoboOnly++;
        else if(!Robo[i] && Bionic[i])
            BioOnly++;
        else if(Robo[i] && Bionic[i])
            Both++;
    }
    if(RoboOnly <= 0){
        // cout << "Robo = 0 ";
        cout << "-1\n";
    }
    else if(BioOnly <= 0){
        // cout << "Bio = 0";
        cout << "1\n";

    }else if(RoboOnly == BioOnly){
        
        cout << 2 <<"\n";
    }
    
    else 
        cout << BioOnly / RoboOnly + 1 << endl;
}