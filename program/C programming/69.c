#include<stdio.h>
#include<string.h>
int main()
{
    char s[100],t[100];
    int i,j=0;
    gets(s);
    for (i=0;i<strlen(s);i++)
    {


    if (s[i]%2!=0&&i%2!=0) t[j]=s[i],j++;
    }
    printf("%s",t);
    return 0;

}
