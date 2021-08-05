#include<stdio.h>
#include<stdlib.h>

typedef struct node{
int *data;
int length;
int rear;
int N;
}Queue;

void creatqueue(Queue *Q,int n)
{
    Q->N=n+1;
    Q->data=(int*)malloc(sizeof(int)*(Q->N));
    Q->length=Q->rear=0;
}

void addelem(Queue *Q,int num)
{
    if((Q->rear+1)%(Q->N)==(Q->rear-Q->length)%Q->N){
        return;
    }
    else{
        Q->rear=(Q->rear+1)%(Q->N);
        Q->data[Q->rear]=num;
        Q->length++;
    }
}

int deletefrontelem(Queue *Q){
  Q->length--;
  return Q->data[(Q->rear-Q->length)%(Q->N)];
}

int popfrontelem(Queue *Q){
return Q->data[(Q->rear-Q->length+1)];
}
int main()
{
    int n,i,len,outnum;
    int A[1000];
    char yesorno[5];
    scanf("%d",&n);
    Queue *Q;
    Q=(Queue*)malloc(sizeof(Queue));
    creatqueue(Q,n);
    for(i=0;;i++)
    {
        scanf("%d",&A[i]);
        char c=getchar();
            if(c=='\n'){
                break;
            }

    }
    len=i+1;
    for(i=0;i<len&&i<n;i++)
    {
        addelem(Q,A[i]);
    }
    scanf("%s",&yesorno);
    scanf("%d",&outnum);
    while(popfrontelem(Q)!=outnum)
    {
        deletefrontelem(Q);
    }
    deletefrontelem(Q);
    int new_front = popfrontelem(Q);
    while(Q->length!=0)
    {
        printf("%d ",deletefrontelem(Q));

    }
    printf("\n%d",new_front);
    return 0;
}
