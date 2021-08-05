/*#include<stdio.h>
int paixu(int a[100],int cnt)
{
    int i;
    for(i=0;i<100;i++)
    {
        a[i]+=1;
        if(a[i]==2) a[i]=0;
    }
    if(a[cnt]==0) a[cnt]=1;
    else a[cnt]=0;

}
int main()
{
    int a[100]={0},n,i,j,cnt=0;
    scanf("%d",&n);
    printf("%d\n",n);
    for(i=0;i<n;i++)
    {
        paixu(a,cnt);
        cnt++;
        for(j=0;j<n;j++)
        {
            printf("%d",a[j]);
        }
        printf("\n");
    }
    return 0;


}*/
#include <stdio.h>
int main(){
    int a,b,n,spot=0,i,r;
    scanf("%d",&n);
    printf("%d\n",n);
    r=n*n;
    while(r)
	{
	    a=0;
	    a=a+1;
	    b=n-a;
    for(i=0;i<a;i++)
        {
            r--;
            printf("%d",spot);
        }
        for(i=0;i<b;i++)
        {
            r--;
            printf("%d",!spot);
        }
        printf("\n");
        spot=!spot;
    }
	return 0;
}
