#include <stdio.h>
int a[2000001];
int main()
{
	int i,j;
	for(i=2;i<=2000000;i++)
		a[i]=i;
	a[1]=0;
	a[0]=0;
	for(i=2;i<=2000000;i++)
	{
		if(a[i]!=0)
			for(j=i+i;j<=2000000;j+=i)
				a[j]=0;
	}

	int n;
	while(scanf("%ld",&n)!=EOF )
	{
		if(n==0)
                      break;
		for(i=0;i<=n;i++)
		{
			if(a[i]!=0)
				printf("%d ",a[i]);
		}
		printf("\n");
	}
	return 0;
}
