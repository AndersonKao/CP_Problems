// AC 2020/04/23 21:43:22
#include <iostream>
using namespace std;

struct Color{
	int pigment1;
	int pigment2;
	int pigment3;
};

struct Customer{
	char name[20];
	int lastBuyMonth;
	int lastBuyDate;
	Color color;	
};
 
bool isValid(Customer customer); //距離上次購買是否超過7天，即是否為4/11以前(含)購買
bool isAvailable(Customer customer); //指定的顏色是否有足夠的顏料可以製作口罩
// void getCustomer(Customer* customerPtr){
//     cin >> (*customerPtr).name;
//     cin >> (*customerPtr).lastBuyMonth; 
//     cin >> (*customerPtr).lastBuyDate;
//     cin >> (*customerPtr).color.pigment1;
//     cin >> (*customerPtr).color.pigment2;
//     cin >> (*customerPtr).color.pigment3;
// } //這隻程式已經幫你實作好了~

//你的程式會被放在這裡

bool isValid(Customer Customer){
    if(Customer.lastBuyMonth == 4 && Customer.lastBuyDate > (18 - 7))
        return false;
    return true;
}

bool isAvailable(Customer customer){
    static bool called = false;
    static Color Storement;
    if(!called){
        Storement.pigment1 = 10000;
        Storement.pigment2 = 10000;
        Storement.pigment3 = 10000;
        called = true;
    }

    if(Storement.pigment1 < customer.color.pigment1)
        return false;
    if(Storement.pigment2 < customer.color.pigment2)
        return false;
    if(Storement.pigment3 < customer.color.pigment3)
        return false;
    Storement.pigment1 -= customer.color.pigment1;
    Storement.pigment2 -= customer.color.pigment2;
    Storement.pigment3 -= customer.color.pigment3;
    // cout << "Remaining\n";
    // cout << Storement.pigment1 << " " << Storement.pigment2
    // << " " << Storement.pigment3 << endl;
    return true;
}


int main(){
	int N;
	cin >> N;
	Customer customer;
	while(N--){
		getCustomer(&customer); //把資料讀到customer裡

		if( !isValid(customer) ){
			cout << "InValid.\n";
		}
		else if( !isAvailable(customer) ){
			cout << "Unavailable.\n";
		}
		else{
			cout << "You get what you want.\n";
		}
	}
    return 0;
}