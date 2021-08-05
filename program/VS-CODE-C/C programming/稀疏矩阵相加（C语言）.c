#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 1000
typedef struct{
int row;//�ڼ���
int col;//�ڼ���
int e;//�洢��ֵ
}Triple;

typedef struct
{
    Triple data[MAXSIZE];
    int m,n,len;//ϡ�������У��У�����Ԫ�صĸ���
}TSMatrix;

void createTSMatrix(TSMatrix *A,TSMatrix *B)//��������
{    int i=1,j=1;     //data��0��δ��
    scanf("%d %d %d %d",&A->m,&A->n,&A->len,&B->len);
    B->m=A->m;
    B->n=A->n;
    int a,b,c;
   for(int j=1;j<=A->len;j++)
    {
        scanf("%d",&a);
         scanf("%d",&b);
          scanf("%d",&c);
          A->data[j].row=a;
          A->data[j].col=b;
          A->data[j].e=c;

    }
    for( i=1;i<=B->len;i++)
    {
        scanf("%d",&a);
         scanf("%d",&b);
          scanf("%d",&c);
          B->data[i].row=a;
          B->data[i].col=b;
          B->data[i].e=c;
           }

}
void EnterTriple(TSMatrix *D,int row,int col,int e)//�ṩ�������ģ��
{
    D->len++;
    D->data[D->len].row=row;
    D->data[D->len].col=col;
    D->data[D->len].e=e;
}

void SumMatrix(TSMatrix *A,TSMatrix *B,TSMatrix *C)//�������
{
    C->len=0;
   int i=1,j=1;
   while(i<=A->len&&j<=B->len)
   {
       if(A->data[i].row<B->data[j].row)
       {
           EnterTriple(C,A->data[i].row,A->data[i].col,A->data[i].e);
            i++;
       }
       else if(A->data[i].row==B->data[j].row)
        {
            if(A->data[i].col<B->data[j].col)
            {
                EnterTriple(C,A->data[i].row,A->data[i].col,A->data[i].e);
                i++;
            }
      else if(A->data[i].col>B->data[j].col)
            {
                EnterTriple(C,B->data[j].row,B->data[j].col,B->data[j].e);
                j++;
            }
            else
            {
                if(B->data[j].e+A->data[i].e!=0)
                    EnterTriple(C,B->data[j].row,B->data[j].col,B->data[j].e+A->data[i].e);
                i++;
                j++;
            }

       }
       else
       {
           EnterTriple(C,B->data[j].row,B->data[j].col,B->data[j].e);
            j++;
       }
   }
       while(i<=A->len)
    {
        EnterTriple(C,A->data[i].row,A->data[i].col,A->data[i].e);
        i++;
    }
    while(j<=B->len)
    {
        EnterTriple(C,B->data[j].row,B->data[j].col,B->data[j].e);
        j++;
    }

}
void printMatrix(TSMatrix *C)//�������
{
    for(int i=1;i<=C->len;i++)
    {
        printf("%d %d %d\n",C->data[i].row,C->data[i].col,C->data[i].e);
    }
}

int main()
{
    TSMatrix A,B,C;
    createTSMatrix(&A,&B);
    SumMatrix(&A,&B,&C);
    printMatrix(&C);
    return 0;

}
