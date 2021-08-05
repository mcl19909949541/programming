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

void createTSMatrix(TSMatrix *A)//��������
{    int i=0;     //data��0��δ��
    scanf("%d?%d",&A->m,&A->n);
    int flag = 1;
    int a,b,c;
    char c1,c2,c3;
    while(flag)
    {
        scanf("%d?%d?%d",&a,&b,&c);


          if(a==0&&b==0&&c==0)
            break;
            i++;
          A->data[i].row=a;
          A->data[i].col=b;
          A->data[i].e=c;


    }
    A->len=i;
}

void printMatrix(TSMatrix *B)//�������
{
    for(int i=1;i<=B->len;i++)
    {
        printf("%d?%d?%d\n",B->data[i].row,B->data[i].col,B->data[i].e);
    }

}

void MulTSMatrix(TSMatrix *A,TSMatrix *B,TSMatrix *C)//�������
{
    C->len=0;
    int p,q,x,cnt;
    int i1,j1;
    int sum;
    cnt=0;
    for(int i=1;i<=A->m;i++)
    {

        for(int j=1;j<=B->n;j++)
        {
           sum=0;
            for(int k=1;k<=A->n;k++)
            {    p=0;q=0;
                for(i1=1;i1<=A->len;i1++){
                    if(A->data[i1].row==i&&A->data[i1].col==k) p=A->data[i1].e;
                   }
                   for(j1=1;j1<=B->len;j1++){
                    if(B->data[j1].row==k&&B->data[j1].col==j) q=B->data[j1].e;
                   }
                sum=sum+(p*q);

            }
            if(sum!=0) {cnt++;
            C->data[cnt].e=sum;
            C->data[cnt].row=i;
            C->data[cnt].col=j;}

        }
    }
    C->len=cnt;

}

int main()
{
    TSMatrix A,B,C;
    createTSMatrix(&A);
    createTSMatrix(&B);
   MulTSMatrix(&A,&B,&C);

    printMatrix(&C);


    return 0;

}
