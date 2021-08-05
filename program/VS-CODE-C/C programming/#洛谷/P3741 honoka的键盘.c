#include<stdio.h>
#include<string.h>
int sum();
int main()
{
   int n,cnt,i,j;
   char a[100],b[100];
   scanf("%d",&n);
   for(i=0;i<n;i++)
   {
       scanf("%c",&a[i]);
   }
   if(n==1) cnt=0;
   else{
        cnt=sum(a);
    for(i=0;i<n;i++)
    {
       strcpy(b,a);
       if(b[i]=='V') b[i]=='K';
       else b[i]=='V';
       j=sum(b);
       if(j>cnt) cnt=j;
    }
   }
   printf("%d",cnt);
   return 0;

}
int sum(char b[])
{
    int cnt=0,i,j;
    for(i=0;i<strlen(b);i++)
    {
        if(b[i]=='V'&&b[i+1]=='K') cnt++;
    }
    return cnt;
}

