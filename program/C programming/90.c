#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main()
{
    char s[5000],s1[5000];int i,j,m=0,pri[5000],max=0,x,y,n;
    gets(s);
    n=strlen(s);
    for (i=0;i<n;i++)
    {
      if(isalpha(s[i]))
      {
          pri[m]=i;
          s1[m++]=toupper(s[i]);
      }
    }
    for (i=0;i<m;i++)
    {
            for (j=0;j<=i&&i+j<m;j++)
        {
            if(s1[i-j]!=s1[i+j])break;//ÆæÊý
            if((2*j+1)>max)
              {
                  max=2*j+1;
                  x=pri[i-j];
                  y=pri[i+j];
              }
        }
             for (j=0;j<=i&&i+j<m;j++)
        {
            if (s1[i-j]!=s1[i+j+1])break;//Å¼Êý
            if ((2*j+2)>max)
            {
                max=2*j+2;
                x=pri[i-j];
                y=pri[i+j+1];
            }
        }


    }
    for (i=x;i<=y;i++)
        printf("%c",s[i]);
    return 0;
}
