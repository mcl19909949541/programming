#include<stdio.h>
void count_dup(char c[],int strlenc)
{
    int i,j=1;
    for(i=1;i<strlenc;i++)
    if(c[0]==c[i]) j++;
    c[1]=j;

}
int main()
{
    char c[4]={1,1,3,4};
    int strlenc=4,i;
    count_dup(c,strlenc);
    for(i=0;i<2;i++)
        printf("%d ",c[i]);
    return 0;
}
