#include<stdio.h>
int main()
{
    int sum,i;
    scanf("%d",&sum);
    if(sum%5==0)i=sum/5-1;
    else i=sum/5;
    printf("%d",i);
    return 0;
}
