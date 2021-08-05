#include<stdio.h>

#define MAXSIZE 100

typedef int ElemType;

//注意define和typedef区别，前者为替换，后者为重命名
typedef struct
{
    ElemType data[MAXSIZE];
	int last;
} SeqList;


void CreatList(SeqList *L)
{
    int i;
    int flag=1;
    L->last=0;
    while(flag)
    {
        scanf("%d",&i);
        if(i!=-1&&L->last<=MAXSIZE)
        {
            L->data[L->last]=i;
            L->last++;
        }
        else flag=0;
    }

}

int ListLength(SeqList L)//返回长度
{
    return L.last;
}

int GetData(SeqList L,int i)//返回第i个元素值
{
    if(i>L.last||i<=0) return -1;
    else return L.data[i-1];
}

void InsList(SeqList *L,int i,ElemType e)//在第i个元素后插入e
{
    int k;
    if((i<1)||(i>(L->last+1)))
    {
        printf("NOT LEGAL");
        return;  //return的括号可有可无
    }
            if(L->last>=MAXSIZE+1)
            {
                printf("FULL");
                return ;
            }
            for(k=L->last;k>=i-1;k--) //注意，最好画图理解

                L->data[k+1]=L->data[k];
                L->data[i]=e;
                L->last++;
                return;

}

void DelList(SeqList *L,int i,ElemType *e)//删除第i个元素，用e返回其值
{
    int k;
    if(i<1||i>L->last+1)
    {
        printf("NOT LEGAL");
        return ;
    }
    *e=L->data[i-1];
    for(k=i;k<=L->last;k++)
       L->data[k-1]=L->data[k];
    L->last--;
    return ;

}
void paixu(SeqList *a,SeqList *b,SeqList *c)  //由小到大排序
{
    c->last=a->last+b->last;
    int i=1,j=1,k=0;
    while(i<=a->last&&j<=b->last)
    {
        if(a->data[i]<b->data[j])
        {   k++;
            c->data[k]=a->data[i];
            i++;
        }
        else if(a->data[i]==b->data[j])

        {
            k++;
            c->data[k]=a->data[i];
            i++;
            k++;
            c->data[k]=b->data[j];
            j++;
        }
        else
        {
            k++;
            c->data[k]=b->data[j];
            j++;
        }
    }
    while(i<=a->last)
    {       k++;
            c->data[k]=a->data[i];
            i++;

    }
    while(j<=b->last)
    {       k++;
            c->data[k]=b->data[j];
            j++;

    }
}

void ListErgodic(SeqList *L) //输出所有数据(可传值也可传地址,毕竟只是输出数据)
{
    for(int i=0;i<L->last;i++)
        printf("%d ",L->data[i]);
    printf("\n");
    return;
}
int main()
{   int e;
    SeqList L;    //初始化顺序表
    printf("输入数据（小于100个）(输入-1为止)");
    CreatList(&L);//要传地址，不然不行
    printf("当前长度为%d\n",ListLength(L));
     printf("当前数据为");
    ListErgodic(&L);
    printf("输出第3个元素的值为%d\n",GetData( L,3));
    InsList(&L,2,66);  //注意，要对顺序表操作必须传地址
    printf("在第2个数后加入66,输出第3个元素的值为%d\n",GetData( L,3));
    printf("当前长度为%d\n",ListLength(L));
    printf("当前数据为");
    ListErgodic(&L);
    DelList(&L,1,&e);
    printf("当前长度为%d\n",ListLength(L));
    printf("删除第一个元素为%d\n",e);
    printf("当前数据为");
    ListErgodic(&L);


    return 0;

}
