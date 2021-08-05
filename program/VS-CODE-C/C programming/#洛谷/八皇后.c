#include<stdio.h>
int n,l,yy,kk,col[100000],left[100000],right[100000],a[100000];
void print()
{
    if(kk<3)
    {
        for(int i=1;i<=yy;i++)
            printf("%d ",a[i]);
        printf("\n");
        kk++;
    }
    return;
}
int has(int x,int y)
{
    if(col[y]==1||left[x+y]==1||right[x-y+10000]==1)
        return 0;
    else
        return 1;
}
void search(int x)
{
    if(x>yy)
    {
        n++;
        print();
        return ;
    }
    for(int i=1;i<=yy;i++)
        if(has(x,i)==1)
    {
        a[x]=i;
        col[i]=left[x+i]=right[x-i+10000]=1;
        search(x+1);
        col[i]=left[x+i]=right[x-i+10000]=0;
    }
}
int main()
{
    scanf("%d",&yy);
    for(int i=0;i<10000;i++)
        a[i]=col[i]=left[i]=right[i]=0;
    search(1);
    printf("%d",n);
    return 0;

}
