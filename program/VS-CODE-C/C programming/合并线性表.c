#include<stdio.h>

#define MAXSIZE 100

typedef int ElemType;


//ע��define��typedef����ǰ��Ϊ�滻������Ϊ������
typedef struct
{
    ElemType data[MAXSIZE];
	int last;
} SeqList;


void CreatList(SeqList *L,int m)
{
    int i;
    int flag=1;
    L->last=0;
    for(i=1;i<=m;i++)
    {      L->last++;
        scanf("%d",&L->data[L->last]);

    }


}

void ListErgodic(SeqList *L) //�����������(�ɴ�ֵҲ�ɴ���ַ,�Ͼ�ֻ���������)
{
    for(int i=1;i<=L->last;i++)
        printf("%d ",L->data[i]);
    printf("\n");
    return;
}
void paixu(SeqList *a,SeqList *b,SeqList *c)
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

int main()
{
    SeqList a,b,c;
    int m,n;
    scanf("%d",&m);
    CreatList(&a,m);
     scanf("%d",&n);
    CreatList(&b,n);
    paixu(&a,&b,&c);
    ListErgodic(&c);
    return 0;

}
