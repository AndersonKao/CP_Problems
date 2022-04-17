#include <iostream>
#include <cmath>

/* 
 * 判斷娃娃魚是否能吃到所有增益。 
 * 8個傳入參數依序為：a, b, c, 霸霸位置, 咩咩位置, 喵喵位置, x, y.  
 * 若能吃到所有增益，回傳true；否則回傳false 
 */
bool isValid(int, int, int, int[], int[], int[], int, int);
/*
 * 4個參數分別為：第一個點的x, y座標、第二個點的x, y座標
 * 回傳此二點的平面座標距離 
 */
double distance(int, int, int, int);

/* your code will be placed at here */

int main()
{
	int a, b, c, x, y;
	int baba[20005];	// 霸霸 
	int mie[20005];		// 咩咩
	int miao[20005];	// 喵喵
	
	// input
	std::cin >> a >> b >> c;	// 霸咩喵數量 
	for(int i=0; i<a; ++i)		// 霸霸位置 
		std::cin >> baba[2*i] >> baba[2*i+1];
	for(int i=0; i<b; ++i)		// 咩咩位置 
		std::cin >> mie[2*i] >> mie[2*i+1];
	for(int i=0; i<c; ++i)		// 喵喵位置 
		std::cin >> miao[2*i] >> miao[2*i+1];
	std::cin >> x >> y;		// 娃娃魚當前位置 
	
	// output
	if(isValid(a,b,c,baba,mie,miao,x,y))
		std::cout << "Good Place! =)";
	else
		std::cout << "Not that well... =("; 
	return 0;
}

double distance(int x1, int y1, int x2, int y2){
    long long sqrx = (x1 - x2) * (x1 - x2);
    long long sqry = (y1 - y2) * (y1 - y2);
    return sqrt(sqrx + sqry);
}
const double eps = 1e-8;
int dcmp(double a, double b){
    if(fabs(a - b) <= eps)
        return 0;
    return (a - b > 0) * 2 - 1;
}
// ver1
/*
bool isValid(int a, int b, int c, int baba[], int meme[], int meow[], int x, int y){
    bool getbaba, getmeme, getmeow;
    getbaba = getmeme = getmeow = false;
    for(int i = 0; i < a; i++) {
        double disbaba = distance(x, y, baba[i * 2], baba[i * 2 + 1]);
        if (dcmp(disbaba, 10.0) <= 0) {
            getbaba = true;
            break;
        }
    }
    for(int i = 0; i < b; i++) {
        double dismeme= distance(x, y, meme[i * 2], meme[2 * i + 1]);
        if (dcmp(dismeme, 10.0) <= 0) {
            getmeme = true;
            break;
        }
    }
    for(int i = 0; i < c; i++) {
        double dismeow= distance(x, y, meow[i * 2], meow[2 * i + 1]);
        if (dcmp(dismeow, 12.0) <= 0) {
            getmeow = true;
            break;
        }
    }
    if(getmeow && getmeme && getbaba)
        return true;
    return false;
}
*/

// ver2
bool isValid(int a, int b, int c, int baba[], int meme[], int meow[], int x, int y){
    bool getbaba, getmeme, getmeow;
    getbaba = getmeme = getmeow = false;
    for(int i = 0; i < a; i++) {
        double disbaba = distance(x, y, baba[i * 2], baba[i * 2 + 1]);
        if (disbaba <= 10.0) {
            getbaba = true;
            break;
        }
    }
    for(int i = 0; i < b; i++) {
        double dismeme= distance(x, y, meme[i * 2], meme[2 * i + 1]);
        if (dismeme <= 10.0) {
            getmeme = true;
            break;
        }
    }
    for(int i = 0; i < c; i++) {
        double dismeow= distance(x, y, meow[i * 2], meow[2 * i + 1]);
        if (dismeow <= 12.0) {
            getmeow = true;
            break;
        }
    }
    if(getmeow && getmeme && getbaba)
        return true;
    return false;
}


// ver3

int distance2(int x1, int y1, int x2, int y2){
    int sqrx = (x1 - x2) * (x1 - x2);
    int sqry = (y1 - y2) * (y1 - y2);
    return (sqrx + sqry);
}

bool isValid(int a, int b, int c, int baba[], int meme[], int meow[], int x, int y){
    bool getbaba, getmeme, getmeow;
    getbaba = getmeme = getmeow = false;
    for(int i = 0; i < a; i++) {
        int disbaba = distance2(x, y, baba[i * 2], baba[i * 2 + 1]);
        if (disbaba <= 100) {
            getbaba = true;
            break;
        }
    }
    for(int i = 0; i < b; i++) {
        int dismeme= distance2(x, y, meme[i * 2], meme[2 * i + 1]);
        if (dismeme <= 100) {
            getmeme = true;
            break;
        }
    }
    for(int i = 0; i < c; i++) {
        int dismeow= distance2(x, y, meow[i * 2], meow[2 * i + 1]);
        if (dismeow <= 144) {
            getmeow = true;
            break;
        }
    }
    if(getmeow && getmeme && getbaba)
        return true;
    return false;
}