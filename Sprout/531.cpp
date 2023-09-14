#include <iostream>
#include <list>
#include <string>
using namespace std;
struct Car{
    string name;
    int WithStandNum; // 可接受的隊伍長度
    int HighestPrice; // 可接受最低票價
};
int main(){
    int S, T;
    string Option;
    cin >> S >> T;
    list<Car> CarList;
    while(T--){
        cin >> Option;
        if(Option == "Leave"){
            S++;
        }else if(Option == "Car"){
            Car NewCar;
            cin >> NewCar.name >> NewCar.WithStandNum >> NewCar.HighestPrice;
            CarList.push_back(NewCar);
        }else if(Option == "Price"){
            int Price;
            cin >> Price;
            while(!CarList.empty() && CarList.back().HighestPrice >= Price){
                CarList.pop_back();
            }
        }
        // List moving
        while(!CarList.empty() && S > 0){
            CarList.pop_front();  
            S--;
        }
        // Can't stand anymore
        if(!CarList.empty() && CarList.back().WithStandNum < CarList.size()){
            CarList.pop_back();
        } 
    }
    // Answer Output
    if(CarList.size() == 0)
        cout << "empty\n";
    else{
        list<Car>::iterator it = CarList.begin();
        for(it = CarList.begin(); it != CarList.end();){
            cout << (*it).name;
            it++;
            if(it != CarList.end())
                cout << ' ';
        }
        cout << "\n";
    }
    return 0;
}