#include<bits/stdc++.h>
using namespace std;
int main(){
    
    stack<pair<int,int>> buyer;

    stringstream ss;
    
    int T;
    cin >> T;
    cin.get();
    
    while(T--){

        string str; 
        getline(cin,str);
        
        ss.clear();
        ss << str;
        
        int numOfPeople ;
        ss >> numOfPeople;

        bool *valid = new bool[numOfPeople+1];
        for(int i = 1;i <= numOfPeople; i++) { valid[i] = true; }

        for(int i = 1,price ; ; i = (i % (numOfPeople)) + 1){
            ss >> price;
            if( ss.fail() ){ break; }
            while( !valid[i] ){ i = (i % (numOfPeople)) + 1; }
            if( price == -1 ){ 
                valid[i] = false;  
            }
            else{
                if( buyer.empty() ){
                    buyer.push( {i,price} );
                }
                else{
                    while( !valid[buyer.top().first] ){
                        buyer.pop();
                    }
                    if( price > buyer.top().second ){        
                        buyer.push( {i,price} );
                    }
                }
            }
        }
           
        while(!buyer.empty() && !valid[buyer.top().first]) { buyer.pop(); }
        if(buyer.empty()){
            cout << "0 -1" << endl;
        } else {
            cout << buyer.top().first << ' ' << buyer.top().second << endl;
        }
        delete valid;
        while( !buyer.empty() ){ buyer.pop(); }
        // cout << "====" << endl;
    }

}