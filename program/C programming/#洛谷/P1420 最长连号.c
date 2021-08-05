#include<stdio.h>
int main()
{
    int A[100];
    int i,j=0,sum=1,n;
    scanf("%d",&n);
    for(i=0;i<n;i++) scanf("%d",&A[i]);
    for(i=0;i<n;)
    {
        if(A[i+1]==(A[i]+1)){sum++;i++;continue;}
        else{
            if(sum>j) {j=sum;sum=1;i++;continue;}
            else {sum=1;i++;continue;}
        }
    }
    if(sum>j) j=sum;
    printf("%d",j);
    return 0;
}
