#include<stdio.h>

#define MAXSIZE 100

typedef int ElemType;

//ע��define��typedef����ǰ��Ϊ�滻������Ϊ������
typedef struct
{
    ElemType data[MAXSIZE];
	int last;
} SeqList;


void CreatList(SeqList *L)
{
    int i;
    int flag=1;
    L->last=0;
    while(flag)
    {
        scanf("%d",&i);
        if(i!=-1&&L->last<=MAXSIZE)
        {
            L->data[L->last]=i;
            L->last++;
        }
        else flag=0;
    }

}

int ListLength(SeqList L)//���س���
{
    return L.last;
}

int GetData(SeqList L,int i)//���ص�i��Ԫ��ֵ
{
    if(i>L.last||i<=0) return -1;
    else return L.data[i-1];
}

void InsList(SeqList *L,int i,ElemType e)//�ڵ�i��Ԫ�غ����e
{
    int k;
    if((i<1)||(i>(L->last+1)))
    {
        printf("NOT LEGAL");
        return;  //return�����ſ��п���
    }
            if(L->last>=MAXSIZE+1)
            {
                printf("FULL");
                return ;
            }
            for(k=L->last;k>=i-1;k--) //ע�⣬��û�ͼ���

                L->data[k+1]=L->data[k];
                L->data[i]=e;
                L->last++;
                return;

}

void DelList(SeqList *L,int i,ElemType *e)//ɾ����i��Ԫ�أ���e������ֵ
{
    int k;
    if(i<1||i>L->last+1)
    {
        printf("NOT LEGAL");
        return ;
    }
    *e=L->data[i-1];
    for(k=i;k<=L->last;k++)
       L->data[k-1]=L->data[k];
    L->last--;
    return ;

}
void paixu(SeqList *a,SeqList *b,SeqList *c)  //��С��������
{
    c->last=a->last+b->last;
    int i=1,j=1,k=0;
    while(i<=a->last&&j<=b->last)
    {
        if(a->data[i]<b->data[j])
        {   k++;
            c->data[k]=a->data[i];
            i++;
        }
        else if(a->data[i]==b->data[j])

        {
            k++;
            c->data[k]=a->data[i];
            i++;
            k++;
            c->data[k]=b->data[j];
            j++;
        }
        else
        {
            k++;
            c->data[k]=b->data[j];
            j++;
        }
    }
    while(i<=a->last)
    {       k++;
            c->data[k]=a->data[i];
            i++;

    }
    while(j<=b->last)
    {       k++;
            c->data[k]=b->data[j];
            j++;

    }
}

void ListErgodic(SeqList *L) //�����������(�ɴ�ֵҲ�ɴ���ַ,�Ͼ�ֻ���������)
{
    for(int i=0;i<L->last;i++)
        printf("%d ",L->data[i]);
    printf("\n");
    return;
}
int main()
{   int e;
    SeqList L;    //��ʼ��˳���
    printf("�������ݣ�С��100����(����-1Ϊֹ)");
    CreatList(&L);//Ҫ����ַ����Ȼ����
    printf("��ǰ����Ϊ%d\n",ListLength(L));
     printf("��ǰ����Ϊ");
    ListErgodic(&L);
    printf("�����3��Ԫ�ص�ֵΪ%d\n",GetData( L,3));
    InsList(&L,2,66);  //ע�⣬Ҫ��˳���������봫��ַ
    printf("�ڵ�2���������66,�����3��Ԫ�ص�ֵΪ%d\n",GetData( L,3));
    printf("��ǰ����Ϊ%d\n",ListLength(L));
    printf("��ǰ����Ϊ");
    ListErgodic(&L);
    DelList(&L,1,&e);
    printf("��ǰ����Ϊ%d\n",ListLength(L));
    printf("ɾ����һ��Ԫ��Ϊ%d\n",e);
    printf("��ǰ����Ϊ");
    ListErgodic(&L);


    return 0;

}
