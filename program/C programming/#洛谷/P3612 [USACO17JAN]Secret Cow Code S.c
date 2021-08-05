#include<stdio.h>
#include<stdlib.h>
void turn(char a[])
{
    int i,j,k;
    char *p1,*p2;
    i=strlen(a);
    p1=&a[i-1];
    p2=&a[i];
    *p2=*p1;
    p1=&a[0];
    p2=&a[i+1];
    for(i-=1;i>0;i--)
    {
        *p2=*p1;
        p1++;
        p2++;
    }
}
int main()
{
    int i,j;
    char a[20];
 int n;
    scanf("%s %d",a,&n);

    for(i=0;i<10;i++)
        turn(a);


    printf("%c",a[n]);
    return 0;
}
