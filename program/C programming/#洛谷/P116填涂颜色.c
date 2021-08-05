#include<stdio.h>
int x1[4]={1,-1,0,0};
int y1[4]={0,0,1,-1};
int n;
int map[32][32],book[32][32];

void search(int x,int y)
{
    if(x<0||x>=n||y<0||y>=n||book[x][y]!=0) return ;
    book[x][y]=1;
    for(int i=0;i<4;i++)
        search(x+x1[i],y+y1[i]);
}
int main()
{
    int i,j,k;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
    {
        scanf("%d",&map[i][j]);
        if(map[i][j]==0) book[i][j]=0;
        else book[i][j]=2;
    }
    search(0,0);

   for(i=0;i<n;i++)

       {

        for(j=0;j<n;j++)
        {
            if(book[i][j]==0) printf("2 ");
            else printf("%d ",map[i][j]);

        }
        printf("\n");
       }
       return 0;
}
