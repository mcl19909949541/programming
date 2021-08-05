#include<stdio.h>
#include<math.h>
int main()
{
    int n;
    scanf("%d",&n);
    while(n!=0)
    {
        int A[n+1];
        int sum=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&A[i]);
            sum+=A[i];
        }
        int m=sum/n;
        int min=sum;
        int minx1;
        for(int x1=A[n]*-1;x1<=A[1];x1++)
        {
           int movesum=0,temp=0;

        for(int i=1;i<=n;i++)
        {
            movesum+=fabs(x1-(temp-(i-1)*m));
            temp+=A[i];
        }
        if(movesum<min)
        {
            min=movesum;
            minx1=x1;
        }
        }
        printf("%d",min);
        return 0;
    }

}
