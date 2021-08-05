#include<stdio.h>
int main()
{
    int a[100][100]={0};
    int n,m,t,j,i;
    scanf("%d%d",&m,&n);
    a[1][1]=1;
    a[2][1]=1;
    for(i=3;i<100;i++)
        {
		for( j=1;j<100;j++)
		a[i][j]=a[i-1][j]+a[i-2][j];
		for( j=1;j<100;j++)
		{
			while(a[i][j]>9)
			{
				a[i][j+1]++;
				a[i][j]-=10;
			}
		}
	}
	int flag=0;
	for(i=100;i>=1;i--)
    {
        if(flag==0&&a[1+n-m][i]==0) continue;
        flag=1;
        printf("%d",a[1+n-m][i]);
    }
    return 0;

}
