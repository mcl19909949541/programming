#include<stdio.h>
#include<stdlib.h>

#define ORDER 3     //B树的阶数

typedef int KeyType;  //关键字数据类型
typedef struct BTNode	//B树结点
{
    int keynum;                        //结点中关键字的个数
    KeyType key[ORDER-1];                // 关键字数组，长度=阶数-1
    struct BTNode* child[ORDER];        // 孩子指针数组，长度=阶数
    int isLeaf;
    struct BTNode* parent;                 // 是否是叶子节点的标志

}BTNode,*BTree;

void BTree_init(BTNode **bt);
void BTree_create(BTNode **tree,int length);//建立b树
int isfull(BTNode *node);//判断节点是否是满节点
void BTree_init(BTNode **bt);//b树初始化
int isfull(BTNode *node);//判断节点是否是满节点
void BTree_insert(BTree *tree,KeyType key);//b树插入
void split_tree(BTree *tree);//子树分裂

void BTree_init(BTNode **bt)
{
    (*bt)=(BTNode*)malloc(sizeof(BTNode));
    (*bt)->isLeaf=1;
    (*bt)->keynum=0;
    (*bt)->parent=NULL;
}

void BTree_create(BTNode **tree,int length)//建立b树
{   int data;
    BTree_init(&(*tree));//初始化一个B树节点
    for(int i=0;i<length;i++)
    {
        scanf("%d",&data);
        BTree_insert(tree,data);
    }
}

///以下为插入环节

int isfull(BTNode *node)//判断节点是否是满节点
{
    if(node->keynum < ORDER)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void BTree_insert(BTree *tree,KeyType key)//b树插入
{
    BTNode *bnp = *tree;
    //节点满，直接进行分裂
    if(isfull(*tree))
    {
        split_tree(tree);
        BTree_insert(tree,key);
        return;
    }
    //是叶子节点且不满，直接插入
    if(bnp->isLeaf && !isfull(bnp))
    {
        //比最大的关键字都大，直接插在末尾
        if(key>=bnp->key[bnp->keynum -1])
        {
            bnp->keynum++;
            bnp->key[bnp->keynum-1] = key;
        }
        else
        {
            for(int i = 0;i<ORDER-1;i++)
            {
                //找到一个比待插入关键字大的关键字，则直接插入
                if(key< bnp->key[i] )
                {
                    KeyType  temp= bnp->key[i];
                    bnp->key[i] = key;
                    bnp->keynum++;
                    for(int j = i + 1;j< bnp->keynum;j++)
                    {
                        key = bnp->key[j];
                        bnp->key[j] = temp;
                        temp = key;
                    }

                    break;
                }
            }
        }
        return;
    }
    //不是叶子节点，查找对应的子树，递归插入
    if(!bnp->isLeaf)
    {
        for(int i = 0;i < bnp ->keynum;i++)
        {
            if(key<bnp->key[i])
            {
                BTree_insert(&((*tree)->child[i]),key);
                return;
            }
        }
        BTree_insert(&((*tree)->child[bnp->keynum]),key);
    }
}

void split_tree(BTree *tree)//子树分裂
{
    BTree bnp1 = *tree;
    BTree bnp2;
    BTree_init(&(bnp2));
    BTree bp;
    int num = bnp1->keynum;
    int split = num/2;
    if(bnp1->parent == NULL)
    {
         BTree_init(&(bp));
         bp->parent = NULL;
         bp->keynum = 1;
         bp->isLeaf = 0;
         bp->key[0] = bnp1->key[split];
         bp->child[0] = bnp1;
         bp->child[1] = bnp2;
    }
    else
    {
        bp = bnp1->parent;
        bp->isLeaf = 0;
        bp->keynum++;
        KeyType temp1, temp2;
        BTNode *tcp1, *tcp2;
        for(int i = 0;i < bp->keynum;i++)
        {
            //新关键字插到末尾
            if(i == bp->keynum-1)
            {
                bp->key[i] = bnp1->key[split];
                bp->child[i] = bnp1;
                bp->child[i+1] = bnp2;
                break;
            }
            //新关键字插到中间
            if(bp->key[i]>bnp1->key[split])
            {
                tcp2 = bnp2;
                temp2 = bnp1->key[split];
                for(int k = i;k<bp->keynum;k++)
                {
                    //关键字后移
                    temp1 = bp->key[k];
                    bp->key[k] = temp2;
                    temp2 = temp1;
                    //子树指针后移
                    tcp1 = bp->child[k+1];
                    bp->child[k+1] = tcp2;
                    tcp2 = tcp1;
                }
            }

        }
    }

    bnp1->keynum = split;
    bnp2->keynum = num - split -1;
    for(int i = 0, j = split+1;j<num;j++)
    {
        bnp2->key[i]=bnp1->key[j];
        bnp2->child[i]=bnp1->child[j];
    }
    bnp2->child[bnp2->keynum] = NULL;
    bnp2->isLeaf = bnp1->isLeaf;
    bnp2->parent = bp;
    bnp1->parent = bp;

    (*tree) = bp;
}

void BTree_print(BTNode *tree)
{
    for(int i=0;i<tree->keynum;i++)
    {
       if(tree->child[i]!=NULL) BTree_print(tree->child[i]);
       printf("%d ",tree->key[i]);
    }
    if(tree->child[tree->keynum]!=NULL) BTree_print(tree->child[tree->keynum]);
}

int main()
{
    int length;
    BTNode *tree=(BTNode*)malloc(sizeof(BTNode));
    scanf("%d",&length);
    printf("1");
    BTree_create(&tree,length);
     printf("2");
    BTree_print(tree);
    return 0;
}




