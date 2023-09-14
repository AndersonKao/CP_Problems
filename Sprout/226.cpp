// AC
int range(int array[],int size){
    int min = 10000000;
    int max = 0;
    for(int i = 0; i < size; i++){
        if(min > array[i])
            min = array[i];
        if(max < array[i])
            max = array[i];
    }
    return max - min;
}
double average(int array[],int size){
    double ans = 0;
    for(int i = 0; i < size; i++){
        ans += (double)array[i];
    }
    ans = ans / size;
    return ans;
}