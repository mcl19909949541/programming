#include<stdio.h>
int c[100005]={0};
int get(int root)//��ͬһ�����ڵ�
{
    if(c[root]==root)//��ʾ���ҵ�
        return root;
    else
    {
        c[root]=get(c[root]);//�ݹ飬ֱ���ҵ�Ϊֹ
        return c[root];
    }
}
void join(int a,int b)
{
    int t1,t2;//�ֱ�Ϊ���˵ĸ��ڵ�
    t1=get(a);
    t2=get(b);
    if(t1!=t2)//�ж����������ڵ��Ƿ���ͬһ����Ȧ
    {
        c[t2]=t1;
    }
    return;
}
int main()
{
    int n,m,i,a,b,sum;
    while(~scanf("%d%d",&n,&m))
    {
        sum=0;
        for(i=1;i<=n;i++)
            c[i]=i;
        while(m--)
        {
            scanf("%d%d",&a,&b);
            join(a,b);
        }
        for(i=1;i<=n;i++)
        {
            if(c[i]==i)
                sum++;
        }
        printf("%d\n",sum);
    }
    return 0;
}
