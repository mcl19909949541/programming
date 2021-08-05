#include<stdio.h>
int main()
{
    int y,m,d,Days,sum;
    scanf("%d-%d-%d",&y,&m,&d);
    if((y%4==0&&y%100!=0)||(y%400==0)) Days=29;
    else Days=28;
    switch(m){
    case 1:sum=d;break;
    case 2:sum=31+d;break;
    case 3:sum=31+Days+d;break;
    case 4:sum=62+Days+d;break;
    case 5:sum=92+Days+d;break;
    case 6:sum=123+Days+d;break;
    case 7:sum=153+Days+d;break;
    case 8:sum=184+Days+d;break;
    case 9:sum=215+Days+d;break;
    case 10:sum=245+Days+d;break;
    case 11:sum=276+Days+d;break;
    case 12:sum=307+Days+d;break;
    }
    printf("%d\n",sum);
    return 0;
}
