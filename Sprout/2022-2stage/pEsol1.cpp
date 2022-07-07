#include<iostream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;
int main()
{
    int n;
    cin >> n; cin.get();
    for(int i = 0; i < n; i++)
    {
        string input;
        getline(cin, input);
        stringstream ss; ss << input;

        string tmp ; vector<int> vec;
        while(getline(ss, tmp,' '))
            vec.push_back(stoi(tmp));
         
        int m = vec[0];
        int tmpPrice = -1;
        int maxPrice = -1; 
        int maxID = 0;
        int counter = 0;

        int curArr[1005] = {0};
        for(int j = 0; j < vec.size() - 1; j++)
        {
            while(curArr[counter + 1] == -1 )
                counter = (counter + 1) % m;
                
            int price = vec[j+1];
            if(price == -1){
                curArr[counter + 1] = price; //quit
            } else if(price > tmpPrice){
                curArr[counter + 1] = price;
                tmpPrice = price;  
            } 
            counter = (counter + 1) % m;
        }

        bool flag = false;

        for(int j = 1; j <= m; j++){
            if(curArr[j] > maxPrice){
                maxID = j;
                maxPrice = curArr[j];
            }
        }
        cout << maxID << " " << maxPrice << endl;
    }
}