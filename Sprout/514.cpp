// AC
#include <iostream>
#include <cstring>
#define MAXN 30
#define MAXD 10

// 多項式乘法，res = a*b，並回傳 res 陣列。
int *convolution(int a[], int b[], int res[], int D){
	memset(res, 0, (2*D+1) * sizeof(int));
  // TODO
    for (int i = 0; i <= D; i++){
        for (int j = 0; j <= D; j++){
            res[i + j] += a[i] * b[j];
        }
    }
    return res;
}
// 讀一個 D 次多項式到陣列 p
void readPoly(int p[], int D){
  // TODO
  for (int i = 0; i <= D; i++){
      std::cin >> p[i];
  }
}
// 印出形如 (c_0 + c_1x^1 ... c_Dx^D) 的多項式 p
void printPoly(int p[], int D){
  // TODO
  std::cout << '(';
  for (int i = 0; i <= D; i++){
      std::cout << p[i];
    if(i != 0){
        std::cout << "x^" << i;
    }
    if(i != D){
        std::cout << " + ";
    }else
    {
        std::cout << ")";
    }
    
  }
}

int main(){
  int D, N, Q;
  int factor[MAXN][MAXD+1];
  int input[MAXD*2+1];
  int result[MAXD*2+1];
  std::cin >> D >> N >> Q;
  for(int i=0; i<N; i++)
    readPoly(factor[i], D);
  while(Q--){
    readPoly(input, D*2);
    for(int i=0; i<N; i++)
      for(int j=i; j<N; j++)
        if(memcmp(convolution(factor[i], factor[j], result, D), input, (2*D+1)*sizeof(int)) == 0){
          printPoly(factor[i], D);
          printPoly(factor[j], D);
          std::cout << std::endl;
        }
  }
}