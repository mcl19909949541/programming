#include<stdio.h>
int main()
{
   int a[2000],b,c[10]={6,2,5,5,4,5,6,3,7,6},s=0,i,j;
   scanf("%d",&b);
   for(i=1;i<2000;i++)
   {
       j=i;
       while(j>=1)
       {
           a[i]+=c[j%10];
           j/=10;
       }
   }
       for(i=0;i<1000;i++)
       {
           for(j=0;j<=1000;j++)
            if(a[i]+a[j]+a[i+j]+4==b) s++;

       }

   printf("%d",s);
   return 0;
}
