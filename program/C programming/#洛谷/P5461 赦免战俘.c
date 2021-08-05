#include<stdio.h>
 int A[100][100];
void cut(int bc,int a,int b);

int main()
{
    int n,bc=1,a,b,i,j;

    scanf("%d",&n);
    for(i=0;i<n;i++)
        bc*=2;
    for(i=0;i<bc;i++)
        for(j=0;j<bc;j++)
        A[i][j]=1;
    cut(bc,0,0);
    for(i=0;i<bc;i++)
        {for(j=0;j<bc;j++)
            printf("%d ",A[i][j]);
        printf("\n");}
        return 0;
}

void cut(int bc,int a,int b)
{  int i,j;
    if(bc==2)
    {
        A[a][b]=0;
        return ;
    }
    for(i=a;i<=(a+(bc)/2-1);i++)
       for(j=b;j<=(b+(bc)/2-1);j++)
       A[i][j]=0;
       cut(bc/2,a+(bc)/2,b);
       cut(bc/2,a,b+(bc)/2);
       cut(bc/2,a+(bc)/2,b+(bc)/2);

}
