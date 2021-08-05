#include<stdio.h>

double avg(int A[100],int s,int e)
{
    double sum;



    for(sum=0;s<=e;s++)sum=sum+A[s];
    return sum;
}
int main()
{
    double a;
    int i,n,A[100],s,e;
     scanf("%d",&n);
    for(i=0;i<n;i++)scanf("%d",&A[i]);
scanf("%d%d",&s,&e);



    a=avg(A,s,e)/(e-s+1);
    printf("%lf",a);
    return 0;
}
