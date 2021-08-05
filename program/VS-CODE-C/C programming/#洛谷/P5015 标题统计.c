#include<stdio.h>
int main()
{
    char ch;
    int cnt;

    while((  ch=getchar())!='\n')
    {
        if(ch==' ')continue;
        cnt++;
    }
    printf("%d",cnt);
    return 0;
}
