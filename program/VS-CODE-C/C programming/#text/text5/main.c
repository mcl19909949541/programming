#include<stdio.h>
int book[100];
int a[100];
int n;
void print(int j)
{
    for(int i=0;i<=j;i++)
       {
           if(i==0) printf("%d",a[i]);
   else  printf("+%d",a[i]);
       }
       printf("\n");
}
void search(int sum,int j)
{
  for(int i=1;i<=n;i++)
  if(book[i]==0){sum+=i;
      if(sum>n) return;
      if(sum==n) {a[j]=i;print(j);return;}
      a[j]=i;
      book[i]=1;
      search(sum,j+1);

      book[i]=0;
        sum-=i;
  }
}
int main()
{
    while(scanf("%d",&n))
    {
        search(0,0);
    }
    return 0;
}
