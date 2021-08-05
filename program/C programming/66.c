#include<stdio.h>
#include<string.h>
int main()
{
    char dest[100],ch;
    int i,j=0,cnt=0;
    gets(dest);
    scanf("%c",&ch);
    for(i=0;i<strlen(dest);i++)
    {
        if(dest[i]==ch)j++;
        if(dest[i]!=ch){if(j>cnt)cnt=j,j=0;}

    }
    for(i=0;i<cnt;i++)
        dest[i]=ch;
    for(i=0;i<cnt;i++)
        printf("%c",dest[i]);
        return 0;
}
