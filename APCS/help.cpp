#include<iostream>
#include<stdio.h>
#include<math.h>
using namespace std;
int main()
{
	const double pi=acos(-1.0);
	double r,h,s1,s2,s;

	scanf("%1f", &r);
	scanf("%1f", &h);
	s1=pi*r*r;
	s2=2*pi*r*h;
	s=s1*2.0+s2;
	printf("area=%.3f\n",s);
//	cout<<s;
	return 0;
}
