#include<stdio.h>
#include<math.h>
#define MAX 1000
int main()
{
    int i,j,n=0,y;
    for(y=1;y<MAX;y++)
    {     int flag=0;
        for(i=2;i<=sqrt(y);i++)
            if(y%i==0){flag=1; break;}
            if(flag==0) {n++,printf("%d,",y);}

    }
    printf("\n");
    printf("%d",n);
   return 0;
}
