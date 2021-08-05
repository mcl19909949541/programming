#include<stdio.h>
int main()
{
    int a[1000],ans=0;
    int n,w,t;
    scanf("%d %d",&w,&n);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    for(int i=0;i<n;i++)
    for(int j=i;j<n+1;j++)
    {
        if(a[i]<a[j]){t=a[i];a[i]=a[j];a[j]=t;}
    }
   int *p1=a,*p2=&a[n-1];
   while(p1<=p2){
        int x=*p1,y=*p2;

    if((x+y)<=w){ans++;p1++;p2--;}
    else{p1++;ans++;}

   }
        printf("%d",ans);
        return 0;
}
