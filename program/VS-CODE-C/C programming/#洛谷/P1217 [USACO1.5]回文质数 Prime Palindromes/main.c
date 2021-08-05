#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void prime_judgement(int A[],int i)
{
    int *p1,*p2,j,k;
   p1=A;
   p2=A+i;
   if(i%2!=0) return;
   for(j=0;;)
   {
       if(*p1==*p2)p1++,p2--,j++;
       else return;
       if(j==(i/2))
       {
    for(k=0;k<=i;k++) printf("%d",A[k]);
    printf("\n");
       return ;
       }
   }

}

int main()
{
   int A[3],i=2;
   A[0]=3;
   A[1]=0;
   A[2]=2;
 prime_judgement(A, i);
 return 0;
}
