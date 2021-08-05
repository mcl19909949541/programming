#include<stdio.h>
#include<stdlib.h>

#define N 30 //Ҷ�ӽ�����ֵ
#define M 2*N-1 //���н�����ֵ

typedef struct{
    int weight;
    int parent;
    int Lchild;
    int Rchild;
    int flag;
}HTNode,HuffmanTree[M+1]; //0�ŵ�Ԫ����


int select(HuffmanTree ht,int n);
void InitHuffmanTree(HuffmanTree ht,int n);
void crtHuffmanTree(HuffmanTree ht,int n);
void printHuffmanTree(HuffmanTree ht,int n);

void InitHuffmanTree(HuffmanTree ht,int n)//��ʼ��������
{
    for(int i=1;i<=n;i++)//��ʼ��Ҷ�ӽڵ�
    {
        ht[i].Lchild=0;
        ht[i].Rchild=0;
        ht[i].weight=0;
        ht[i].parent=0;
        ht[i].flag=0;
        scanf("%d",&ht[i].weight);
    }
    int m=2*n-1;
    for(int i=n+1;i<=m;i++)//��ʼ����Ҷ�ӽڵ�
    {
        ht[i].Lchild=0;
        ht[i].Rchild=0;
        ht[i].weight=0;
        ht[i].parent=0;
         ht[i].flag=0;
    }

}

void crtHuffmanTree(HuffmanTree ht,int n)//������������
{
   for(int i=n+1;i<=(2*n-1);i++)
   {
       int s1=select(ht,i-1);//ע�������i-1
       int s2=select(ht,i-1);
       ht[i].weight = ht[s1].weight+ht[s2].weight;
       ht[s1].parent=i;
       ht[s2].parent=i;
       ht[i].Lchild=s1;
       ht[i].Rchild=s2;
   }
}

int select(HuffmanTree ht,int n)//ѡ����СȨֵ�Ľ���±�
{
    int i,temp,min;
    for(i=1;i<=n;i++)//���ó�ʼ�±��Ȩֵ
    {
        if(ht[i].flag==0)
        {
            temp = ht[i].weight;//��ʼȨֵ
            min=i;//��ʼ�±�
            break;
        }
    }
    for(i=1;i<=n;i++)
    {
        if(ht[i].flag==0&&temp>ht[i].weight)
        {
            temp=ht[i].weight;
            min = i;
        }
    }
    ht[min].flag=1;
    return min;
}

void printHuffmanTree(HuffmanTree ht,int n)//��ӡ��������
{   printf("���  weigh  parent Lchild Rchild\n");
    for(int i=1;i<=n;i++)
    {//\tΪ��ȫ����˼
        printf("%d\t%d\t%d\t%d\t%d\n",i,ht[i].weight,ht[i].parent,ht[i].Lchild,ht[i].Rchild);
    }
    printf("\n");
}
int main()
{
    HuffmanTree ht;
    int n;//nΪ����Ľ����
    printf("�������贴���Ľ����Ϊ:");
    scanf("%d",&n);

     InitHuffmanTree(ht,n);//��ʼ��
     printf("��ʼ�Ĺ�������Ϊ\n");
     printHuffmanTree(ht,2*n-1);//��ӡ��ʼ�Ĺ�������

     crtHuffmanTree(ht,n);//������������
     printf("������Ĺ�������Ϊ\n");
     printHuffmanTree(ht,2*n-1);//��ӡ�����Ĺ�������

     return 0;
}
