#include<stdio.h>
void strlupper(char str[])
{int i;
    for(i=0;i<8;i++)
        if(str[i]>=97&&str[i]<=122)
        str[i]=str[i]-32;
}
int main()
{
    char str[8]={'a','b','c','d','A','B','C','D'};
    int i;
    strlupper(str);
    for(i=0;i<8;i++)
        printf("%c",str[i]);
    return 0;
}
