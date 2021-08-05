#include<stdio.h>
#include<string.h>
int merge_array(char a[],int intlena,char b[],int intlenb,char c[],int intlenc)
{
    int i,j,cnt;
    j=intlena;
    for(i=0;i<intlenb;i++)

    {
        a[intlena]=b[i];
        intlena++;
    }
    intlenc=j+intlenb;
    return intlenc;
}
int main()
{
    char a[4]={1,2,3,4},b[4]={1,2,3,4},c[30];int i,j,cnt,intlena,intlenb,intlenc=8;
  intlena=strlen(a);
   intlenb=strlen(b);

      merge_array(a,intlena,b,intlenb,c,intlenc);
     printf("%d",intlenc);
     return 0;



}
