#include<stdio.h>
#include<stdlib.h>

typedef struct OLNode//定义一个结点
{
    int row,col;//行，列
    int e;//存储的值
    struct OLNode *down,*right;//向下的指针与向右的指针向量
}Node,*LNODE;

typedef struct
{
    LNODE *row_head,*col_head;//行，列头指针向量(注意此处已经为二级指针）
    int m,n,len;//行数，列数，非零元素个数
}CrossList;

void CreateCrossList(CrossList *M)//采用十字链表方试创建稀疏矩阵
{
    int i;
    Node *p,*temp;
    M->row_head=(Node**)malloc((M->m+1)*sizeof(Node*));//注意此处分配的方式和数量(【0】不用所以要多分配一个）
    M->col_head=(Node**)malloc((M->n+1)*sizeof(Node*));//此处像在分配一维数组，M->col_head[i]即为一维指针
    for(i=1;i<=M->m;i++)
    {
        M->row_head[i]=NULL;//初始化头指针向量，各行为空的链表
    }
    for(i=1;i<=M->n;i++)
    {
        M->col_head[i]=NULL;//初始化头指针向量，各列为空的链表
    }
    if(M->len!=0)
    {
        for(i=1;i<=M->len;i++)
        {
            p=(Node*)malloc(sizeof(Node));
            scanf("%d %d %d",&p->row,&p->col,&p->e);

            //建立行链表
            if(M->row_head[p->row]==NULL)//若输入数据的所在行没数据，即将数据直接插入所在行
            {
                p->right=NULL;
                M->row_head[p->row]=p;
            }
            else//若输入数据的所在行有数据
            {
                temp=M->row_head[p->row];
                while(temp->right!=NULL&&temp->right->col<p->col)//头节点开始向右搜索直到比所插入数据列数大
                {
                    temp=temp->right;
                }
                p->right=temp->right;//经典头插
                temp->right=p;
                p->right=NULL;

            }

            //建立列链表
            if(M->col_head[p->col]==NULL)//若输入数据的所在列没数据，即将数据直接插入所在列

            {
                p->down=NULL;
                M->col_head[p->col]=p;
             }
             else//若输入数据的所在列有数据
            {
                temp=M->col_head[p->col];
                while(temp->down!=NULL&&temp->down->row<p->row)//头节点开始向下搜索直到比所插入数据行数大
                {
                    temp=temp->down;
                }
                p->down=temp->down;//经典头插
                temp->down=p;
                p->down=NULL;

            }

        }
    }
}//建立完啦！！！


void PlusCrossList(CrossList *A,CrossList *B)//相加并存到A中(这里只用遍历行节点方式就可以了，似乎目前用不到列节点）
{
      int i;
      Node *p,*temp1,*temp2;
      for(i=1;i<=A->m;i++)//一行一行处理
      {
          if(B->row_head[i]==NULL)continue;//和A的行对应的B的行中没有元素则换A的下一行
          else
          {
              if(A->row_head[i]==NULL)//若A的行中没有元素则把对应B行第一个元素复制到A中
              {
                  p=(Node*)malloc(sizeof(Node));
                  p->col=B->row_head[i]->col;
                  p->row=B->row_head[i]->row;
                  p->e=B->row_head[i]->e;
                  A->row_head[i]=p;
                  p->right=NULL;
                  B->row_head[i]=B->row_head[i]->right;//头节点位置前进
              }
              if(B->row_head==NULL) continue;//和A的行对应的B的行中没有元素则换A的下一行
              for(temp1=B->row_head[i];; temp1=temp1->right)//遍历B中某个行的元素
            {
                for(temp2=A->row_head[i];; temp2=temp2->right)//遍历A中某个行的元素
                {
                    if(temp2->col == temp1->col)//两数位置一样则相加并退出换下一个B的元素判断
                    {
                        temp2->e+=temp1->e;
                        break;
                    }
                    else if(temp2==A->row_head[i] && temp1->col<temp2->col)//头节点位置而且B位置靠前，把B元素插入进A
                    {
                        p=(Node*)malloc(sizeof(Node));
                        p->col = temp1->col;
                        p->row = temp1->row;
                        p->e = temp1->e;
                        p->right = temp2->right;
                        p->right =temp2;
                        A->row_head[i]=p;//头节点位置前进
                        break;
                    }
                    else if((temp2->right == NULL || temp2->right->col>temp1->col)  && temp1->col>temp2->col)
                    {
                        p=(Node*)malloc(sizeof(Node));
                        p->col = temp1->col;
                        p->row = temp1->row;
                        p->e = temp1->e;
                        p->right = temp2->right;
                        temp2->right=p;
                        break;
                    }

                }

                if(temp1->right == NULL) break;
          }
      }
  }
}
void PrintCross(CrossList *A)//输出矩阵
{
    int i;
    Node *p;
    for(i=1;i<=A->m;i++)//遍历行的方式从列数从大到小输出(也可改下变成遍历列结点的）
    {
        p=A->row_head[i];
        while(p!=NULL)
        {
            printf("%d %d %d\n",p->row,p->col,p->e);
            p=p->right;
        }
    }
}

int main()
{
    CrossList *A=(CrossList*)malloc(sizeof(CrossList));
    CrossList *B=(CrossList*)malloc(sizeof(CrossList));
    scanf("%d %d %d %d",&A->m,&A->n,&A->len,&B->len);
    B->m=A->m;

    B->n=A->n;

    CreateCrossList(A);
    CreateCrossList(B);
    PlusCrossList(A,B);
    PrintCross(A);
    return 0;
}
