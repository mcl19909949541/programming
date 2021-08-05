#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int main()
{
    char a[10],b[100],c[100],d[100];
    int h=0,i;
    gets(a);

    for(i=0;i<strlen(a);i++)
    {
        if(a[i]==119&&a[i+1]==104&&a[i+2]==105&&a[i+3]==108&&a[i+4]==101){b[h]=115,b[h+1]=116,b[h+2]=114,b[h+3]=117,b[h+4]=99;b[h+5]=116,i=i+4,h=h+6;}
        else b[h]=a[i],h++;
    }


    printf("%s",b);


    return 0;




}
