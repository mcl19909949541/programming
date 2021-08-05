#include<stdio.h>
#include<stdlib.h>

typedef struct hashnode
{
    int data;
    int flag;
}hashtable;

int HashAlgorithm(int data)
{
    return (3*data)%11;
}

hashtable *createHashnode(int data, int flag)
{
    hashtable *p;
    p=(hashtable*)malloc(sizeof(hashtable));
    p->data=data;
    p->flag=flag;
}

void Gethashtable(hashtable *HT[],int datalist[])
{
    int position,flag;
    for(int i=0;i<8;i++)
    {
        flag=1;
        position = HashAlgorithm(datalist[i]);
        while(HT[position]!=NULL)
            {
                position++;
                flag++;
            }

    HT[position]=createHashnode(datalist[i],flag);
    }
}

void PrintAverageLength(hashtable *HT[])
{
    int ASL=0;
    for(int i=0;i<11;i++)
    {
        if(HT[i]!=NULL)
        {
            ASL+=HT[i]->flag;
        }
    }
    ASL=ASL/8;
    printf("%d",ASL);
}

int main()
{
    int datalist[8]={22,41,53,46,30,13,01,67};
    hashtable *HT[11]={NULL};
    Gethashtable(HT,datalist);
    PrintAverageLength(HT);
    return 0;
}
