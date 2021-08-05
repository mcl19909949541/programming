#include<stdlib.h>
#include<stdio.h>
#include<string.h>


void put(char s[])
{
    printf("%s", s);
}
int main()
{
    char s[20];
    
    gets(s);
    int a = strlen(s);
    printf("%d", a);
    put(s);
}