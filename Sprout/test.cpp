#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib> // for rand, srand
 
using namespace std;
struct people{
    int age;
    int height;
    int weight;
    string name;
    people(){}
    people(int age, int height, int weight, string name):
        age(age), height(height), weight(weight), name(name){}
    bool operator<(people b){
        return this->name < b.name;
    }
    friend ostream &operator<<(ostream &os, const people &data);
};
    ostream& operator<<(ostream& os, const people& data){
        os << data.age << " " << data.height<< " " << data.weight << " " << data.name;
        return os;
    }
int getRandNum(int L, int R){
    if(L>R)
        swap(L, R);
    return rand() % (R - L + 1) + L;
}
bool cmp(const people& a, const people& b){
    if(a.weight != b.weight)
        return (a.weight < b.weight);
    else if(a.height != b.height)
        return (a.height < b.height);
    else if(a.age != b.age)
        return (a.age < b.age);
    return false;
}
bool cmp2(const people &a, const people &b){
    if(a.weight < b.weight)
        return true;
    else if(a.height < b.height)
        return true;
    else if(a.age < b.age)
        return true;
    return false;
}
 
int main(){
    srand(time(NULL));
 
    vector<people> v;
	v.push_back(people(getRandNum(1,90), getRandNum(160, 200), getRandNum(40, 100), "Alice"));
    v.emplace_back(getRandNum(1, 90), getRandNum(160, 200), getRandNum(40, 100), "Bob");
    v.emplace_back(getRandNum(1, 90), getRandNum(160, 200), getRandNum(40, 100), "Cathy");
    v.emplace_back(getRandNum(1, 90), getRandNum(160, 200), getRandNum(40, 100), "Danny");
    v.emplace_back(getRandNum(1, 90), getRandNum(160, 200), getRandNum(40, 100), "Eggo");
    v.emplace_back(getRandNum(1, 90), getRandNum(160, 200), getRandNum(40, 100), "Frank");
    v.emplace_back(getRandNum(1, 90), getRandNum(160, 200), getRandNum(40, 100), "Gilbert");
    v.emplace_back(getRandNum(1, 90), getRandNum(160, 200), getRandNum(40, 100), "Inn");
    v.emplace_back(getRandNum(1, 90), getRandNum(160, 200), getRandNum(40, 100), "Jack");
    v.emplace_back(getRandNum(1, 90), getRandNum(160, 200), getRandNum(40, 100), "Ken");
 
    vector<people> v2(v);
    vector<people> v3(v);
    sort(v2.begin(), v2.end());
    sort(v3.begin(), v3.end(), cmp);
    for(int i = 0; i < v2.size(); i++){
    	cout << v2[i] << endl;
    }
    return 0;
    cout << "----------------\n";
    for(auto it: v3){
    	cout << it << endl;
    }
    cout << "----------------\n";
    return 0;
}