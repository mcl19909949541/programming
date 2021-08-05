#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int sort(const void *a,const void *b)
{
     return strlen((char*)a) > strlen((char*)b) ? -1: 1;
}
void paixu(char p1[][10])
{   char temp[10];
    int i,j;
    for(i=0;i<5;i++)
        for(j=i+1;j<5;j++)
    {
       if( strcmp(p1[i],p1[j])>0)
       {
           strcpy(temp,p1[i]);
             strcpy(p1[i],p1[j]);
               strcpy(p1[j],temp);
       }
    }
}
void paixu2(char*p1[])
{
    char *temp;
    int i,j;
    for(i=0;i<4;i++)
        for(j=i+1;j<5;j++)
    {
        if(strcmp(p1[i],p1[j])>0)
        {
            temp=p1[i];
            p1[i]=p1[j];
            p1[j]=temp;
        }
    }
}


int main()
{
    char A[5][10]={"aa","aaa","aaaa","aaaaaaaa","aaaaaaaa"};
    int i,k,j;
    char *p[5];
    for(i=0;i<5;i++)
        p[i]=A[i];
    paixu2(p);
//qsort(A,5,sizeof(char)*10,sort);
//paixu(A);
    for(i=0;i<5;i++)
        printf("%s\n",A[i]);
    return 0;
}
