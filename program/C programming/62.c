#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
    double a,b,c,d;
    char a1,a2,a3,a4,a5,a6;
    scanf("%lf%lf\n",&a,&b);
    scanf("%lf%lf",&c,&d);
    if(b>0)a1='+';
    else a1='-';
    if(c>0)a2='+';
    else a2='-';
    if(b+d>0)a3='+';
    else a3='-';
    if(b-d>0) a4='+';
    else a4='-';
    if(a*c+b*d>0) a5='+';
    else a5='-';
    if((b*c-a*d/(c*c+d*d))>0) a6='+';
    else a6='-';

    printf("(%.2lf%c%.2lfi)+(%.2lf%c%.2lfi) =(%.2lf%c%.2lfi)\n",a,a1,fabs(b),c,a2,fabs(d),a+c,a3,fabs(b+d));
    printf("(%.2lf%c%.2lfi)-(%.2lf%c%.2lfi) =(%.2lf%c%.2lfi)\n",a,a1,fabs(b),c,a2,fabs(d),a-c,a4,fabs(b-d));
    printf("(%.2lf%c%.2lfi)*(%.2lf%c%.2lfi) =(%.2lf%c%.2lfi)\n",a,a1,fabs(b),c,a2,fabs(d),a*c-b*d,a5,fabs((a*d)+(b*c)));
    printf("(%.2lf%c%.2lfi)/(%.2lf%c%.2lfi) =(%.2lf%c%.2lfi)",a,a1,fabs(b),c,a2,fabs(d),(a*c+b*d)/(c*c+d*d),a6,fabs((b*c-a*d)/(c*c+d*d)));
    return 0;
}
