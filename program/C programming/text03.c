#include<stdio.h>

int fun(int a,int b)
        {
           if(a>b) return a;
           return b;
        }
int main()
{
    int i,j,k,t,n,m,x,y,N=2,M=2,flag1,flag2,flag=0;
    scanf("%d %d",&x,&y);

    for(n=2;n<300;n++)
        for(m=2;m<300;m++)
    {   flag1=0;
        flag2=0;
        M=m;
        N=n;

             for(i=fun(M,N);i<=(M*N);i++)
    {
        if(i%M==0&&i%N==0)
        {
            if(i==y) flag1=1;
            break;
        }
    }
     for(i=N;i>=1;i--)
     {
         if(M%i==0&&N%i==0)
         {
             if(i==x) flag2=1;
             break;
         }
     }
     if(flag1==1&&flag2==1)
     {
        flag++;

     }


    }


    printf("%d",flag);

    return 0;
}
