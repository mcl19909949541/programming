#include<stdio.h>
#include<stdlib.h>

#define N 30
#define M 2*N-1
typedef struct
{
    int weight;
    int parent;
    int Lchild;
    int Rchild;
    int flag;
} HTNode, HuffmanTree[M + 1];
int select(HuffmanTree ht, int n);

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

void creatTree(HuffmanTree ht,int n)
{
    for (int i = n + 1; i <= 2 * n - 1;i++)
    {
        int s1 = select(ht, i - 1);
        int s2 = select(ht, i - 1);
        ht[i].weight = ht[s1].weight + ht[s2].weight;
        ht[s1].parent = i;
        ht[s2].parent = i;
        ht[i].Lchild = s1;
        ht[i].Rchild = s2;
    }
}

int select(HuffmanTree ht,int n)
{
    int temp, min;
    for (int i = 1; i <= n;i++)
    {
        if(ht[i].flag==0)
        {
            temp = ht[i].weight;
            min = i;
            break;
        }
    }
    for (int i = 1; i <= n;i++)
    {
        if(ht[i].flag==0&&temp>ht[i].weight)
        {
            temp = ht[i].weight;
            min = i;
        }
    }
    ht[min].flag = 1;
    return min;
}

void printTree(HuffmanTree ht,int n)
{ 
    for(int i=1;i<=n;i++)
    {//\t为补全的意思
        printf("%d\t%d\t%d\t%d\t%d\n",i,ht[i].weight,ht[i].parent,ht[i].Lchild,ht[i].Rchild);
    }
    printf("\n");
}

int main()
{
    HuffmanTree ht;
    int n;
    scanf("%d", &n);
    InitHuffmanTree(ht,n);
    creatTree(ht,n);
    printTree(ht,n);
    return 0;
}