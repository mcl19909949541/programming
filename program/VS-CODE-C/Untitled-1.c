#include<stdio.h>
#include<stdlib.h>

#define N 30 //叶子结点最大值
#define M 2*N-1 //所有结点最大值

typedef struct{
    int weight;
    int parent;
    int Lchild;
    int Rchild;
    int flag;
}HTNode,HuffmanTree[M+1]; //0号单元不用


int select(HuffmanTree ht,int n);
void InitHuffmanTree(HuffmanTree ht,int n);
void crtHuffmanTree(HuffmanTree ht,int n);
void printHuffmanTree(HuffmanTree ht,int n);

void InitHuffmanTree(HuffmanTree ht,int n)//初始哈夫曼树
{
    for(int i=1;i<=n;i++)//初始化叶子节点
    {
        ht[i].Lchild=0;
        ht[i].Rchild=0;
        ht[i].weight=0;
        ht[i].parent=0;
        ht[i].flag=0;
        scanf("%d",&ht[i].weight);
    }
    int m=2*n-1;
    for(int i=n+1;i<=m;i++)//初始化非叶子节点
    {
        ht[i].Lchild=0;
        ht[i].Rchild=0;
        ht[i].weight=0;
        ht[i].parent=0;
         ht[i].flag=0;
    }

}

void crtHuffmanTree(HuffmanTree ht,int n)//构建哈夫曼树
{
   for(int i=n+1;i<=(2*n-1);i++)
   {
       int s1=select(ht,i-1);//注意这里的i-1
       int s2=select(ht,i-1);
       ht[i].weight = ht[s1].weight+ht[s2].weight;
       ht[s1].parent=i;
       ht[s2].parent=i;
       ht[i].Lchild=s1;
       ht[i].Rchild=s2;
   }
}

int select(HuffmanTree ht,int n)//选择最小权值的结点下标
{
    int i,temp,min;
    for(i=1;i<=n;i++)//设置初始下标和权值
    {
        if(ht[i].flag==0)
        {
            temp = ht[i].weight;//初始权值
            min=i;//初始下标
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

void printHuffmanTree(HuffmanTree ht,int n)//打印哈夫曼树
{   printf("结点  weigh  parent Lchild Rchild\n");
    for(int i=1;i<=n;i++)
    {//\t为补全的意思
        printf("%d\t%d\t%d\t%d\t%d\n",i,ht[i].weight,ht[i].parent,ht[i].Lchild,ht[i].Rchild);
    }
    printf("\n");
}
int main()
{
    HuffmanTree ht;
    int n;//n为所需的结点数
    printf("输入所需创建的结点数为:");
    scanf("%d",&n);

     InitHuffmanTree(ht,n);//初始化
     printf("初始的哈夫曼树为\n");
     printHuffmanTree(ht,2*n-1);//打印初始的哈夫曼树

     crtHuffmanTree(ht,n);//构建哈夫曼树
     printf("构建后的哈夫曼树为\n");
     printHuffmanTree(ht,2*n-1);//打印构建的哈夫曼树

     return 0;
}