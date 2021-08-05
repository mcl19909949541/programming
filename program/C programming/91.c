#include<stdio.h>
int main()
{
  int n;
    scanf("%d",&n);
    while (n!=-1)
    {
        int info[n][2];
        int begin=0,dis=0;
        for(int i=0;i<n;i++)
        {
            scanf("%d%d",&info[i][0],&info[i][1]);
            dis=dis+info[i][0]*(info[i][1]-begin);
            begin=info[i][1];


        }
        printf("%d\n",dis);
        scanf("%d",&n);
        return 0;
    }
}
