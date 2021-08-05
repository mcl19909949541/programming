#include <stdio.h>
#include <stdlib.h>

struct Triple
{
    int ti;
    int tj;
    int value;
};

struct tripleList
{
    struct Triple T[2000];
    int li;
    int lj;
    int ln;
};

void createNewTripleList (struct tripleList *list);
void getRowPot (struct tripleList *list,int rowPot[]);
void clear (struct tripleList *list);
void printTripleList (struct tripleList *list);
void mul (struct tripleList *list1,struct tripleList *list2,struct tripleList *list3,int rowPot1[],int rowPot2[]);
void run ();

int main()
{
    run ();

    return 0;
}

void run ()
{
    int rowPot1[2000]={0},rowPot2[2000]={0};
    struct tripleList list1,list2,list3;

    createNewTripleList (&list1);//输入两个三元组表
    createNewTripleList (&list2);
    getRowPot (&list1,rowPot1);//得到它们的位置数组
    getRowPot (&list2,rowPot2);

    mul (&list1,&list2,&list3,rowPot1,rowPot2);//相乘
    printTripleList (&list3);//输出
}
void createNewTripleList (struct tripleList *list)
{
    int i=0,a,b,c;
    scanf ("%d?%d",&(list->li),&(list->lj));//输入行数列数
    while (1)
    {
        scanf ("%d?%d?%d",&a,&b,&c);//输入行 列 数据
        if (a==0&&b==0&&c==0)//都为0时停止输入
        {
            break;
        }
        list->T[i].ti=a-1;//赋值，因为题目输入的行列数据是从1开始的，这里将它转为以0开始，最后输出时在加上1
        list->T[i].tj=b-1;
        list->T[i].value=c;
        i++;
    }
    list->ln=i;//得到三元组表元素个数
}

void printTripleList (struct tripleList *list)
{
    int i;
    for (i=0;i<=list->ln-1;i++)//输出三元组表的所有元素
    {
        printf ("%d?%d?%d\n",list->T[i].ti+1,list->T[i].tj+1,list->T[i].value);
    }
}

void mul (struct tripleList *list1,struct tripleList *list2,struct tripleList *list3,int rowPot1[],int rowPot2[])
{
    int i,j,k,l,no,max,n,len1,len2,A[2000]={0};
    list3->li=list1->li;//得到行列
    list3->lj=list2->lj;
    for (i=0,n=0;i<=list1->li-1;i++)//遍历第一个矩阵的行
    {
        len1=rowPot1[i+1]-1;//得到这一行的所有非0元在三元组表的位置区间的右端
        for (j=rowPot1[i],max=0;j<=len1;j++)//在这一行所有非0元在三元组表中的位置区间中遍历
        {
            len2=rowPot2[list1->T[j].tj+1]-1;//得到第二个矩阵中列号与上一个for中的行号相等的所有非0元在三元组表的位置区间的最左端
            for (k=rowPot2[list1->T[j].tj];k<=len2;k++)//在这一行所有非0元在三元组表中的位置区间遍历
            {
                no=list2->T[k].tj;
                A[no]+=list1->T[j].value*list2->T[k].value;//在数组中添加相乘结果
                max=no>max?no:max;
            }
        }
        for (l=0;l<=max;l++)
        {
            if (A[l]!=0)//将非0的结果存入新的三元组表中
            {
                list3->T[n].ti=list1->T[j-1].ti;
                list3->T[n].tj=l;
                list3->T[n].value=A[l];
                ++n;
                A[l]=0;
            }
        }
    }
    list3->ln=n;//得到新三元组表的元素个数
}

void getRowPot (struct tripleList *list,int rowPot[])
{
    int n[2000]={0};
    int i,pre1=0,pre2=0;
    for (i=0;i<=list->ln-1;i++)//得到矩阵每行的非0元个数
    {
        (n[list->T[i].ti])++;
    }
    for (i=0;i<=list->li;i++)
    {
        rowPot[i]=pre1+pre2;//本行第一个非0元素在三元组表中的位置，上一行的非0元个数加上上一行第一个非0元在三元组表中的位置
        pre1=n[i];
        pre2=rowPot[i];
    }
}
