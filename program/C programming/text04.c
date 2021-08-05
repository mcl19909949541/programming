#include <stdio.h>
#include <stdlib.h>

struct Triple
{
    int ti;
    int tj;
    int value;
};

struct tripleList
{
    struct Triple T[2000];
    int li;
    int lj;
    int ln;
};

void createNewTripleList (struct tripleList *list);
void getRowPot (struct tripleList *list,int rowPot[]);
void clear (struct tripleList *list);
void printTripleList (struct tripleList *list);
void mul (struct tripleList *list1,struct tripleList *list2,struct tripleList *list3,int rowPot1[],int rowPot2[]);
void run ();

int main()
{
    run ();

    return 0;
}

void run ()
{
    int rowPot1[2000]={0},rowPot2[2000]={0};
    struct tripleList list1,list2,list3;

    createNewTripleList (&list1);//����������Ԫ���
    createNewTripleList (&list2);
    getRowPot (&list1,rowPot1);//�õ����ǵ�λ������
    getRowPot (&list2,rowPot2);

    mul (&list1,&list2,&list3,rowPot1,rowPot2);//���
    printTripleList (&list3);//���
}
void createNewTripleList (struct tripleList *list)
{
    int i=0,a,b,c;
    scanf ("%d?%d",&(list->li),&(list->lj));//������������
    while (1)
    {
        scanf ("%d?%d?%d",&a,&b,&c);//������ �� ����
        if (a==0&&b==0&&c==0)//��Ϊ0ʱֹͣ����
        {
            break;
        }
        list->T[i].ti=a-1;//��ֵ����Ϊ��Ŀ��������������Ǵ�1��ʼ�ģ����ｫ��תΪ��0��ʼ��������ʱ�ڼ���1
        list->T[i].tj=b-1;
        list->T[i].value=c;
        i++;
    }
    list->ln=i;//�õ���Ԫ���Ԫ�ظ���
}

void printTripleList (struct tripleList *list)
{
    int i;
    for (i=0;i<=list->ln-1;i++)//�����Ԫ��������Ԫ��
    {
        printf ("%d?%d?%d\n",list->T[i].ti+1,list->T[i].tj+1,list->T[i].value);
    }
}

void mul (struct tripleList *list1,struct tripleList *list2,struct tripleList *list3,int rowPot1[],int rowPot2[])
{
    int i,j,k,l,no,max,n,len1,len2,A[2000]={0};
    list3->li=list1->li;//�õ�����
    list3->lj=list2->lj;
    for (i=0,n=0;i<=list1->li-1;i++)//������һ���������
    {
        len1=rowPot1[i+1]-1;//�õ���һ�е����з�0Ԫ����Ԫ����λ��������Ҷ�
        for (j=rowPot1[i],max=0;j<=len1;j++)//����һ�����з�0Ԫ����Ԫ����е�λ�������б���
        {
            len2=rowPot2[list1->T[j].tj+1]-1;//�õ��ڶ����������к�����һ��for�е��к���ȵ����з�0Ԫ����Ԫ����λ������������
            for (k=rowPot2[list1->T[j].tj];k<=len2;k++)//����һ�����з�0Ԫ����Ԫ����е�λ���������
            {
                no=list2->T[k].tj;
                A[no]+=list1->T[j].value*list2->T[k].value;//�������������˽��
                max=no>max?no:max;
            }
        }
        for (l=0;l<=max;l++)
        {
            if (A[l]!=0)//����0�Ľ�������µ���Ԫ�����
            {
                list3->T[n].ti=list1->T[j-1].ti;
                list3->T[n].tj=l;
                list3->T[n].value=A[l];
                ++n;
                A[l]=0;
            }
        }
    }
    list3->ln=n;//�õ�����Ԫ����Ԫ�ظ���
}

void getRowPot (struct tripleList *list,int rowPot[])
{
    int n[2000]={0};
    int i,pre1=0,pre2=0;
    for (i=0;i<=list->ln-1;i++)//�õ�����ÿ�еķ�0Ԫ����
    {
        (n[list->T[i].ti])++;
    }
    for (i=0;i<=list->li;i++)
    {
        rowPot[i]=pre1+pre2;//���е�һ����0Ԫ������Ԫ����е�λ�ã���һ�еķ�0Ԫ����������һ�е�һ����0Ԫ����Ԫ����е�λ��
        pre1=n[i];
        pre2=rowPot[i];
    }
}
