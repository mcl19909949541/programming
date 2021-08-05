#include<stdio.h>
#include<string.h>
int main()
{
    char src[100];
    int i,num=0,flag=0,cnt=0,a[100];
    gets(src);
    for(int i=0;i<=strlen(src);i++)
    {
        if(src[i]>='0'&&src[i]<='9')
        {
            if(flag==0)
            {
                num=num*10+src[i]-48;
                flag=1,cnt++;
            }
            else
            {
                num=num*10+src[i]-48;
            }
        }
        else
        {
            if(flag==1) a[cnt-1]=num;
            num=0,flag=0;
        }
    }
    printf("%d\n",cnt);
    for(i=0;i<=cnt-1;i++)printf("%d ",a[i]);


    return 0;
}
