// AC 2020/04/24 08:51:31  
#include <iostream>
double girls_average(Student ss[], int size)
{
    if (size == 0)
        return -1;
    double ans = 0;
    int girlNum = 0;
    for (int i = 0; i < size; i++)
    {
        if(ss[i].gender == 'F'){
            ans += ss[i].score;
            girlNum++;
        }
    }
    if(girlNum == 0)
        return -1;
    return ans / girlNum;
}

double boys_average(Student ss[], int size)
{
    if (size == 0)
        return -1;
    double ans = 0;
    int boyNum = 0;
    for (int i = 0; i < size; i++)
    {
        if(ss[i].gender == 'M'){
            ans += ss[i].score;
            boyNum++;
        }
    }
    if(boyNum == 0)
        return -1;
    return ans / boyNum;
}

void print(Student s)
{
    std::cout << s.name << " [" << s.gender << "]: " << s.score << "\n";
}