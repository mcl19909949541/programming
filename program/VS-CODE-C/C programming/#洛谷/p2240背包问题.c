#include<stdio.h>
#include<stdlib.h>
struct node
{
    double w;
    double v;
    double p;
}node;
int n;
double sum,c;
int inc(const void *a, const void *b)
{

	return ( * (node * )a).p > ( * (node * )b).p ? 1 : -1;


 }
int main()
{    struct node q[100];
    scanf("%d%lf",&n,&c);
    for(int i=1;i<=n;i++)
    {
        scanf("%lf%lf",&q[i].w,&q[i].v);
        q[i].p=q[i].v/q[i].w;
    }
    qsort(q,100,sizeof(node),inc);
    for(int i=1;i<=n;i++)
    {
        if(c>=q[i].w)
        {
            c-=q[i].w;
            sum+=q[i].v;
        }
        else{
            sum+=c*q[i].p;
            break;
        }
    }
    printf("%.2f",sum);
    return 0;
}
