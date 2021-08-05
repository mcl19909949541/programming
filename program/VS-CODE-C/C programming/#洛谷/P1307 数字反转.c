#include<stdio.h>
#include<string.h>
int main()
{    char n,i[12],j,x=0,y=0;
    gets(i);
    n = strlen(i);
    if(i[0] == '-')
        {
            printf("-");
            y=1;
        }
    for(j=n-1;j>=0;j--)
    {
            if(y==1 && j==0)
                break;
            if(x==0 && i[j]=='0')
                continue;
            else
                {
                    printf("%c",i[j]);
                    x=1;
                }
    }
    return 0;
}
