#include<stdio.h>
#include<string.h>
int main()
{
    char dir[4][6]={"West","North","East","South"};
    char loc[6];
    int cnt,inf,locindex;
    scanf("%s%d",loc,&cnt);
    for(int i=0;i<4;i++)
    {
        if(strcmp(loc,dir[i])==0)
        {
            locindex=i;
            break;
        }
    }
    for(int i=0;i<cnt;i++)
    {
        scanf("%d",&inf);
        if(inf==1) locindex++;
        if(inf==0) locindex--;
        if(locindex==4) locindex=0;
        if(locindex==-1) locindex=3;
    }
    puts(dir[locindex]);
    return 0;
}
