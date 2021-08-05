#include<stdio.h>
#include<math.h>
int main()
{
    double a;
    int n=0;
    scanf("%lf",&a);
    a=fabs(a);
    if(a<=1)printf("0\n");
    else{
        while(a>1){
            a=a/10;
            n++;
        }
        printf("%d\n",n);
    }
    return 0;
}
