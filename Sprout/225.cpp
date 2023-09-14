// AC 
int san_n_jia_i(int n){
    if(n == 1)
        return 1;
    if(n % 2 == 1){
        return n / 2;
    }
    return 3 * n  + 1;
    
}