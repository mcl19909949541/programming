#include<stdio.h>
#include<string.h>
void stringmerge(char S1[],char S2[])
{
    int t=strlen(S1);
    for(int i=0;i<strlen(S2);i++)
        S1[t++]=S2[i];
        }


int main()
{
    char S1[10],S2[10];
    scanf("%s",S1);
    scanf("%s",S2);
      stringmerge(S1,S2);
    printf("%s",S1);
    return 0;

}
