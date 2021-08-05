#include<stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
        if((1000<n<10000)&&(n/1000==n%10)&&(n/100%10==n/10%10)) printf("yes\n");
        else if((100<n<=1000)&&(n/100==n%10)) printf("yes\n");
        else if((10<n<=100)&&(n/10==n%10)) printf("yes\n");
        else if(0<n<=10) printf("yes\n");
        else  printf("no\n");
        return  0;

}
