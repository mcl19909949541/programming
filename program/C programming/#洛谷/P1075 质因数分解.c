#include<stdio.h>
#define N 1000
int search_prime_number(int A[])
{  int n=0,j;
    for(int i=2;i<N;i++)
    {
        for(j=2;;j++)
            if(i%j==0) break;
        if(j==i) {A[n]=i;n++;}
    }
}
int main()

{ int A[100];
int n,i,j,p,flag=0;
     search_prime_number( A);
    scanf("%d",&p);
    for(i=0;i<100;i++)
        {   for(j=0;j<100;j++)
    {
        if(p==(A[i]*A[j])){flag=1;p=A[i]>A[j]?A[i]:A[j]; break;}

    }
       if(flag==1) break; }
       printf("%d\n",p);

       return 0;
}
