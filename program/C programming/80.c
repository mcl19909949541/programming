/*
#include<stdio.h>
int paixu(int a[],int n)
{
 int b[50]={0},i,t,m=0;
 for(i=0;i<50;i++)
   for(t=1;;n*=t,t++)
   {
       if(a[i]==n)a[i]=0;
       if(n>50)break;
   }
   for(i=0;i<50;i++)
   if(a[i]!=0){b[m]=a[i],m++;};
   for(i=0;i<50;i++)a[i]=0;
   for(i=0;i<50;i++)a[i]=b[i];


}
int main()
{
    int a[50],c[20],i,j,n,student,place,cnt,x;
    int t=1;
    for(i=0;i<50;i++) a[i]=t,t++;
    scanf("%d ",&student);
    scanf("%d\n",&place);
    for(i=0;i<20;i++)
        scanf("%d",&c[i]);
    for(i=0;i<20;i++)
    {    cnt=0;
        n=c[i];
        paixu(a,n);
        for(x=0;x<50;x++)
        {
            if(a[x]!=0)cnt++;
        }
        if(cnt==place)break;

    }
    for(i=0;i<place;i++)
        printf("%d ",a[i]);
    return 0;


}
*/
#include<stdio.h>

#include<string.h>

int cardNum[20] = {0};

int isLucky[51] = {0};

int childLeft,count;

void pickChild(int n,int x){

int i,j;

while(1){

for(i = 0;i < 20;++i){

count = 0;

for(j = 1;j <= n;++j){

count+=isLucky[j];

if(count==cardNum[i]){

isLucky[j] = 0;

if(x==--childLeft)return;

count = 0;

}}}}}

int main(){

int n,x,i;

scanf("%d%d",&n,&x);

for(i = 0; i < 20; ++i){

scanf("%d",cardNum + i);

}

for(i=1;i<=n;++i)isLucky[i]=1;

childLeft = n;

pickChild(n,x);

for(i=1;i<=n;i++) if(isLucky[i]==1) printf("%d ",i);

return 0;

}
