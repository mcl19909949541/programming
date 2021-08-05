#include<stdio.h>
int a[500][500],m,n,x,y,z,r,b[500][500];
void in();
void change();
void work();
void out();
int main()
{
    in();
    work();
    out();
    return 0;

}
void in()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        a[i][j]=(i-1)*n+j;
}
void change()
{
    int sx=x-r,sy=y-r,tr=2*r+1;
    if(z)
    {
        for(int i=1;i<=tr;i++)
            for(int j=1;j<=tr;j++)
            b[i][j]=a[sx+i-1][sy+j-1];
        for(int i=1;i<=tr;i++)
            for(int j=1;j<=tr;j++)
            a[i+sx-1][j+sy-1]=b[j][tr-i+1];
    }
    else
    {
         for(int i=1;i<=tr;i++)
            for(int j=1;j<=tr;j++)
                b[i][j]=a[sx+i-1][sy+j-1];
             for(int i=1;i<=tr;i++)
            for(int j=1;j<=tr;j++)
                a[i+sx-1][j+sy-1]=b[tr-j+1][i];
    }
}
void out()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        printf("%d ",a[i][j]);
        printf("\n");

    }
}
void work()
{
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&x,&y,&r,&z);
        change();
    }
}
