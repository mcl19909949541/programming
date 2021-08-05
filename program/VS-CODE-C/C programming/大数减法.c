#include<stdio.h>
#include<string.h>
int x[100]={0},y[100]={0},z[105]={0};//将数组元素全部初始化为0
void sub(int x[],int y[],int len)
{
    int i,j;
    for(i=0;i<len;i++)
    {
        if(x[i]>=y[i])//如果x[i]>=y[i]，不用向前一位借1，可直接减
            z[i]=x[i]-y[i];
        else  //如果x[i]<y[i]，向前一位借1，同时前一位应减1
        {
            z[i]=x[i]+10-y[i];
            x[i+1]=x[i+1]-1;
        }
    }
    for(i=len-1;i>0;i--)//删除前缀0
    {
        if(z[i]==0)
            len--;
        else
            break;
    }
    for(i=len-1;i>=0;i--)  //倒序输出数组
        printf("%d",z[i]);
    printf("\n");
}
int main()
{
    char a[100],b[100];//通过字符串对大数进行输入并储存
    int len1,len2;
    while(scanf("%s -%s",a,b))
    {
        int i,j=0,k=0;
        len1=strlen(a);
        len2=strlen(b);
        for(i=len1-1,j=0;i>=0;i--)//将两个字符串中的字符转化为数字，并倒序储存到数组中，即字符串为123456，则数组为654321
            x[j++]=a[i]-'0';
        for(i=len2-1,k=0;i>=0;i--)
            y[k++]=b[i]-'0';
        if(len1>len2)  //若减数长度 > 被减数，正常减
            sub(x,y,len1);
        else if(len1<len2)  //若减数长度 < 被减数，被减数 减 减数
        {
            printf("-");
            sub(y,x,len2);
        }
        else  //若减数长度 == 被减数，判断两个数的大小
        {
            for(i=len1-1;i>=0;i--)//判断每一位两个数的大小
            {if(x[i]==y[i])
                    continue;
                if(x[i]>y[i])//即减数大
                {
                    sub(x,y,len1);
                    break;
                }
                if(x[i]<y[i])//即被减数大
                {
                    printf("-");
                    sub(y,x,len1);
                    break;
                }
            }
        }
    }
    return 0;
}

