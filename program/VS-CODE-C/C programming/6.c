#include<stdio.h>
int main()
{
    double l,bon;
    scanf("%lf",&l);
    if(l<=10) bon=l*0.1;
            else if(l<20) bon=1+(l-10)*0.075;
                else if(l<40) bon=1.75+(l-20)*0.05;
                    else if(l<60) bon=2.75+(l-40)*0.03;
                        else if(l<100) bon=3.35+(l-60)*0.015;
                            else bon=3.95+(l-100)*0.01;
    printf("%lf\n",bon);
    return 0;
}
