#include<stdio.h>
int main()
{
    char s1[1000],s2[1000];
    int cnt=0;
    FILE *in,*out;
    in=fopen("#text3.c","r");
    if(in!=NULL)
    {  out=fopen("ÎÄ¼þ¸´ÖÆ.c","w");
    while(!feof(in)){
        if(fgets(s1,sizeof(s1)-1,in)==NULL) continue;
                sprintf(s2,"%s",s1);
        fputs(s2,out);
    }
    }
fclose(out);
    fclose(in);
    return 0;
}
