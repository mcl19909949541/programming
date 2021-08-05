#include<stdio.h>
int map[10][10];
int book[10][10];
int x1[4]={1,-1,0,0};
int y1[4]={0,0,1,-1};
int n,m,t,sx,sy,mx,my,fx,fy;
int cnt=0;
void walk(int x,int y)
{
    int i,j,k;
    if(x==fx&&y==fy)
    {
    cnt++;
    return;
    }
    else
    for(i=0;i<4;i++)
    {
        if(map[x+x1[i]][y+y1[i]]==1&&book[x+x1[i]][y+y1[i]]==0)
        {
            book[x][y]=1;
            walk(x+x1[i],y+y1[i]);
             book[x][y]=0;
        }
    }

}
int main()
{
    int i,j,k;
    scanf("%d %d %d",&n,&m,&t);
    scanf("%d %d %d %d",&sx,&sy,&fx,&fy);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
        map[i][j]=1;
    for(i=0;i<t;i++)
    {
        scanf("%d %d",&mx,&my);
        map[mx][my]=0;
    }
    walk(sx,sy);
    printf("%d",cnt);
    return 0;
}
