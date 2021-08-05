#include<stdio.h>
#include<stdlib.h>

#define ORDER 3     //B���Ľ���

typedef int KeyType;  //�ؼ�����������
typedef struct BTNode	//B�����
{
    int keynum;                        //����йؼ��ֵĸ���
    KeyType key[ORDER-1];                // �ؼ������飬����=����-1
    struct BTNode* child[ORDER];        // ����ָ�����飬����=����
    int isLeaf;
    struct BTNode* parent;                 // �Ƿ���Ҷ�ӽڵ�ı�־

}BTNode,*BTree;

void BTree_init(BTNode **bt);
void BTree_create(BTNode **tree,int length);//����b��
int isfull(BTNode *node);//�жϽڵ��Ƿ������ڵ�
void BTree_init(BTNode **bt);//b����ʼ��
int isfull(BTNode *node);//�жϽڵ��Ƿ������ڵ�
void BTree_insert(BTree *tree,KeyType key);//b������
void split_tree(BTree *tree);//��������

void BTree_init(BTNode **bt)
{
    (*bt)=(BTNode*)malloc(sizeof(BTNode));
    (*bt)->isLeaf=1;
    (*bt)->keynum=0;
    (*bt)->parent=NULL;
}

void BTree_create(BTNode **tree,int length)//����b��
{   int data;
    BTree_init(&(*tree));//��ʼ��һ��B���ڵ�
    for(int i=0;i<length;i++)
    {
        scanf("%d",&data);
        BTree_insert(tree,data);
    }
}

///����Ϊ���뻷��

int isfull(BTNode *node)//�жϽڵ��Ƿ������ڵ�
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

void BTree_insert(BTree *tree,KeyType key)//b������
{
    BTNode *bnp = *tree;
    //�ڵ�����ֱ�ӽ��з���
    if(isfull(*tree))
    {
        split_tree(tree);
        BTree_insert(tree,key);
        return;
    }
    //��Ҷ�ӽڵ��Ҳ�����ֱ�Ӳ���
    if(bnp->isLeaf && !isfull(bnp))
    {
        //�����Ĺؼ��ֶ���ֱ�Ӳ���ĩβ
        if(key>=bnp->key[bnp->keynum -1])
        {
            bnp->keynum++;
            bnp->key[bnp->keynum-1] = key;
        }
        else
        {
            for(int i = 0;i<ORDER-1;i++)
            {
                //�ҵ�һ���ȴ�����ؼ��ִ�Ĺؼ��֣���ֱ�Ӳ���
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
    //����Ҷ�ӽڵ㣬���Ҷ�Ӧ���������ݹ����
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

void split_tree(BTree *tree)//��������
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
            //�¹ؼ��ֲ嵽ĩβ
            if(i == bp->keynum-1)
            {
                bp->key[i] = bnp1->key[split];
                bp->child[i] = bnp1;
                bp->child[i+1] = bnp2;
                break;
            }
            //�¹ؼ��ֲ嵽�м�
            if(bp->key[i]>bnp1->key[split])
            {
                tcp2 = bnp2;
                temp2 = bnp1->key[split];
                for(int k = i;k<bp->keynum;k++)
                {
                    //�ؼ��ֺ���
                    temp1 = bp->key[k];
                    bp->key[k] = temp2;
                    temp2 = temp1;
                    //����ָ�����
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




