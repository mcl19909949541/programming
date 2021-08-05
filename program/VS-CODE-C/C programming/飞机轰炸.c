#include<stdio.h>
int main()
{
    int n,m,x,y,i,j,k,t,cnt,use1,use2;;
    int city[100][100],x1[10],x2[10],y1[10],y2[10];
    scanf("%d %d %d %d",&n,&m,&x,&y);
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
        city[i][j]=0;
    for(i=0;i<x;i++)
        scanf("%d %d %d %d",&x1[i],&y2[i],&x2[i],&y2[i]);
    for(i=0;i<y;i++)
    {scanf("%d %d",&use1,&use2);
    city[use1-1][use2-1]=1;}
    for(i=0;i<x;i++)
    {
        for(j=y1[i]-1;j<=y2[i]-1;j++)
            for(k=x1[i]-1;k<=x2[i]-1;k++)
        {
            if(city[j][k]!=0) city[j][k]++;
        }
    }
      for(i=0;i<m;i++)
        for(j=0;j<n;j++)
       {
            if(city[i][j]!=0&&city[i][j]!=1)  printf("Y %d %d\n",city[i][j]-1,city[i][j]-1);
             if(city[i][j]==1)  printf("N");
       }
       return 0;
}
