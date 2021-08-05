#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    FILE *f1=fopen("DATA5613.TXT","r");
    FILE *f2=fopen("DATA5613.CPP","r");
    int line=0;
    if(f1!=NULL&&f2!=NULL)
    {
        char s1[100]= {0},s2[100]= {0};
        while(!feof(f1)&&!feof(f2))
        {
            if(fgets(s1,sizeof(s1)-1,f1)==NULL) continue;
            if(fgets(s2,sizeof(s2)-1,f2)==NULL) continue;
            line++;
            for(int i=0; i<strlen(s1); i++)
            {
                if( s1[i]!=s2[i])printf("%d %d\n",line,i+1);
            }
        }
        fclose(f1);
        fclose(f2);
    }
    return 0;

}
