#include<stdio.h>
#include<string.h>
int main()
{

    char s[100]={0},ch;
    int j,i;

    scanf("%s%c%d",s,&ch,&j);
    for(i=j;i<strlen(s);i++)
    {
        s[i+1]=s[i];

    }
    s[j]=ch;
    for(i=0;i<strlen(s);i++)
        printf("%c",s[i]);
    return 0;
}
