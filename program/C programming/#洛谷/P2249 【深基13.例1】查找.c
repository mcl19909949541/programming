#include<stdio.h>
 int n,m,k;
int search(int a[],int left,int right,int k)
{
    if(left==right)
    {
        if(a[right]==k) return right+1;
        else return -1;
    }
    int middle=(right+left)/2;
    if(k<=a[middle])
        search(a,left,middle,k);
    else search(a,middle+1,right,k);

}
int main()
{

    int a[10000];
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);

    }
    for(;m>0;m--)
    {
        scanf("%d",&k);
        printf("%d ",search(a,0,n-1,k));
    }
    return 0;
}
