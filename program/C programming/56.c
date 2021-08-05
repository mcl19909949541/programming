#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    char a[13][5]={"Null","¢ñ","II","III","IV","V","VI","VII","VIII","IX","X","XI","XII"};
    char b[5];
    scanf("%s",b);
    for(int i=1;i<13;i++)
        if(strcmp(a[i],b)==0)
            {printf("%d\n",i);
            break;}
        return 0;


}
