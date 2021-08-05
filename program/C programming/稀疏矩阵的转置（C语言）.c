#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 1000
typedef struct{
int row;//第几行
int col;//第几列
int e;//存储的值
}Triple;

typedef struct
{
    Triple data[MAXSIZE];
    int m,n,len;//稀疏矩阵的行，列，非零元素的个数
}TSMatrix;


void createTSMatrix(TSMatrix *A)//创建矩阵
{    int i=1;     //data【0】未用
    scanf("%d %d",&A->m,&A->n);
    int flag = 1;
    int a,b,c;
    char c1,c2;
    while(flag)
    {
        scanf("%d",&a);
        c1 = getchar();
         scanf("%d",&b);
         c2 = getchar();
          scanf("%d",&c);
          if(c1=='?'&&c2=='?')
            break;
          A->data[i].row=a;
          A->data[i].col=b;
          A->data[i].e=c;
          i++;

    }
    i--;
    A->len=i;
}

void TransMatrix(TSMatrix A,TSMatrix *B)//序列递增转置法
{
    int i,j,k;
    B->n=A.m;
    B->m=A.n;
    B->len=A.len;
    if(B->len)
    {
        j=1;//辅助计数器，记录转置后的三元组元素下标值
        for(k=1;k<=A.n;k++)//扫描矩阵A的列次或B的行次

            for(i=1;i<=A.len;i++)  //扫描A找列为k的元素
        {
            if(A.data[i].col==k)
            {
                B->data[j].row=A.data[i].col;
                B->data[j].col=A.data[i].row;
                B->data[j].e=A.data[i].e;
                j++;
            }
        }
    }
}

void FastTransMatrix(TSMatrix A,TSMatrix *B)//快速转置法
{
    int col,t,p,q;
    int num[MAXSIZE],position[MAXSIZE];
    B->n=A.m;
    B->m=A.n;
    B->len=A.len;
    if(B->len)
    {
        for(col=1;col<=A.n;col++)
            num[col]=0;
        for(t=1;t<=A.len;t++)
            num[A.data[t].col]++;
        position[1]=1;
        for(col=2;col<=A.n;col++)
        {
            position[col]=position[col-1]+num[col-1];
        }
        for(p=1;p<=A.len;p++)
        {
            col=A.data[p].col;
            q=position[col];
            B->data[q].row=A.data[p].col;
            B->data[q].col=A.data[p].row;
            B->data[q].e=A.data[p].e;
            position[col]++;
        }
    }
}

void printMatrix(TSMatrix *B)//输出矩阵
{
    for(int i=1;i<=B->len;i++)
    {
        printf("%d %d %d\n",B->data[i].row,B->data[i].col,B->data[i].e);
    }
}

int main()
{
    TSMatrix A,B;//A为初始矩阵，B为转置后的矩阵
    createTSMatrix(&A);
    FastTransMatrix(A,&B);
    printMatrix(&B);
    return 0;
}
