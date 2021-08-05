#include<stdio.h>
#include<stdlib.h>

typedef struct OLNode//����һ�����
{
    int row,col;//�У���
    int e;//�洢��ֵ
    struct OLNode *down,*right;//���µ�ָ�������ҵ�ָ������
}Node,*LNODE;

typedef struct
{
    LNODE *row_head,*col_head;//�У���ͷָ������(ע��˴��Ѿ�Ϊ����ָ�룩
    int m,n,len;//����������������Ԫ�ظ���
}CrossList;

void CreateCrossList(CrossList *M)//����ʮ�������Դ���ϡ�����
{
    int i;
    Node *p,*temp;
    M->row_head=(Node**)malloc((M->m+1)*sizeof(Node*));//ע��˴�����ķ�ʽ������(��0����������Ҫ�����һ����
    M->col_head=(Node**)malloc((M->n+1)*sizeof(Node*));//�˴����ڷ���һά���飬M->col_head[i]��Ϊһάָ��
    for(i=1;i<=M->m;i++)
    {
        M->row_head[i]=NULL;//��ʼ��ͷָ������������Ϊ�յ�����
    }
    for(i=1;i<=M->n;i++)
    {
        M->col_head[i]=NULL;//��ʼ��ͷָ������������Ϊ�յ�����
    }
    if(M->len!=0)
    {
        for(i=1;i<=M->len;i++)
        {
            p=(Node*)malloc(sizeof(Node));
            scanf("%d %d %d",&p->row,&p->col,&p->e);

            //����������
            if(M->row_head[p->row]==NULL)//���������ݵ�������û���ݣ���������ֱ�Ӳ���������
            {
                p->right=NULL;
                M->row_head[p->row]=p;
            }
            else//���������ݵ�������������
            {
                temp=M->row_head[p->row];
                while(temp->right!=NULL&&temp->right->col<p->col)//ͷ�ڵ㿪ʼ��������ֱ��������������������
                {
                    temp=temp->right;
                }
                p->right=temp->right;//����ͷ��
                temp->right=p;
                p->right=NULL;

            }

            //����������
            if(M->col_head[p->col]==NULL)//���������ݵ�������û���ݣ���������ֱ�Ӳ���������

            {
                p->down=NULL;
                M->col_head[p->col]=p;
             }
             else//���������ݵ�������������
            {
                temp=M->col_head[p->col];
                while(temp->down!=NULL&&temp->down->row<p->row)//ͷ�ڵ㿪ʼ��������ֱ��������������������
                {
                    temp=temp->down;
                }
                p->down=temp->down;//����ͷ��
                temp->down=p;
                p->down=NULL;

            }

        }
    }
}//��������������


void PlusCrossList(CrossList *A,CrossList *B)//��Ӳ��浽A��(����ֻ�ñ����нڵ㷽ʽ�Ϳ����ˣ��ƺ�Ŀǰ�ò����нڵ㣩
{
      int i;
      Node *p,*temp1,*temp2;
      for(i=1;i<=A->m;i++)//һ��һ�д���
      {
          if(B->row_head[i]==NULL)continue;//��A���ж�Ӧ��B������û��Ԫ����A����һ��
          else
          {
              if(A->row_head[i]==NULL)//��A������û��Ԫ����Ѷ�ӦB�е�һ��Ԫ�ظ��Ƶ�A��
              {
                  p=(Node*)malloc(sizeof(Node));
                  p->col=B->row_head[i]->col;
                  p->row=B->row_head[i]->row;
                  p->e=B->row_head[i]->e;
                  A->row_head[i]=p;
                  p->right=NULL;
                  B->row_head[i]=B->row_head[i]->right;//ͷ�ڵ�λ��ǰ��
              }
              if(B->row_head==NULL) continue;//��A���ж�Ӧ��B������û��Ԫ����A����һ��
              for(temp1=B->row_head[i];; temp1=temp1->right)//����B��ĳ���е�Ԫ��
            {
                for(temp2=A->row_head[i];; temp2=temp2->right)//����A��ĳ���е�Ԫ��
                {
                    if(temp2->col == temp1->col)//����λ��һ������Ӳ��˳�����һ��B��Ԫ���ж�
                    {
                        temp2->e+=temp1->e;
                        break;
                    }
                    else if(temp2==A->row_head[i] && temp1->col<temp2->col)//ͷ�ڵ�λ�ö���Bλ�ÿ�ǰ����BԪ�ز����A
                    {
                        p=(Node*)malloc(sizeof(Node));
                        p->col = temp1->col;
                        p->row = temp1->row;
                        p->e = temp1->e;
                        p->right = temp2->right;
                        p->right =temp2;
                        A->row_head[i]=p;//ͷ�ڵ�λ��ǰ��
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
void PrintCross(CrossList *A)//�������
{
    int i;
    Node *p;
    for(i=1;i<=A->m;i++)//�����еķ�ʽ�������Ӵ�С���(Ҳ�ɸ��±�ɱ����н��ģ�
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
