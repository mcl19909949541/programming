#include<stdio.h>
#define MAX 100
struct node
{
    int head;
    char name[MAX];
};
int main()
{
    int n,m,x,y;
    struct node a[100];
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        scanf("%d %s",&a[i].head,a[i].name);
    }
    int now=0;
    for(int i=1;i<=m;i++)
       {

       scanf("%d %d",&x,&y);
        if(a[now].head==0&&x==0)now=(now+n-y)%n;
        else if(a[now].head==0&&x==1)now=(now+y)%n;
        else if(a[now].head==1&&x==0)now=(now+y)%n;
        else if(a[now].head==1&&x==1)now=(now+n-y)%n;
       }
       printf("%s",a[now].name);
       return 0;
}
