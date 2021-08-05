#include<stdio.h>
#include<stdlib.h>


typedef struct ThreadNode{
    char data;
    struct ThreadNode * lchild, * rchild;
    int ltag, rtag;//0Ϊ������ǰ���������1Ϊ����
}ThreadNode, * ThreadTree;

ThreadTree InitThreadTree();
void InThread(ThreadTree p,ThreadTree pre);  //ͨ����������Զ�����������
void CreateInThread(ThreadTree T);  //ͨ����������������������

ThreadTree FirstNode(ThreadTree p); //����������µĵ�һ���ڵ�
ThreadTree NextNode(ThreadTree p);  //��ڵ�p�����������µĺ�һ���ڵ�
void Visit(ThreadTree T);
void InOrder(ThreadTree T); //�������

///�����������Ľ���
ThreadTree InitThreadTree(){
    char ch;
    ThreadTree T;
    scanf("%c", &ch);
    if(ch == '#') T = NULL;
    else{
        T = (ThreadTree)malloc(sizeof(ThreadNode));
        T->data = ch;
        T->lchild = InitThreadTree();
        T->rchild = InitThreadTree();
    }
    return T;
}

///������������������
/*
* ����������ڵ��lchildΪnull����ô���ڵ��lchildΪpreΪnull
* �ڶ���if��ʱ��pre��Ϊnull��ʱ���ִ�У���һ���ǲ�ִ�е�
* ���ڵ�������������֮��pre��ָ���˸��ڵ��ˣ�Ȼ��ݹ�
* �ݹ�֮��ָ��preÿ�ζ���ָ��ոշ��ʹ��Ľڵ�
* ���������������Ӳ�Ϊ�գ��ͻ�һֱ������������֪������Ϊ�գ�Ȼ�����Һ���
*/

void InThread(ThreadTree p,ThreadTree pre){
    if(p != NULL){                   //p�ǵ�ǰ�ڵ㣬pre�Ǹշ��ʵĽڵ�
        InThread(p->lchild, pre);    //�ݹ飬�Ż�������
        if(p->lchild == NULL){       //������Ϊ�գ�����ǰ������
            p->lchild = pre;
            p->ltag = 1;
        }
        if(pre != NULL && pre->rchild == NULL){
            pre->rchild = p;          //������Ϊ�գ��ͽ���ǰ���ڵ�ĺ�����
            pre->rtag = 1;
        }
        pre = p;                      //p�ոշ��ʹ��ˣ���pre = p
        InThread(p->rchild, pre);     //�ݹ飬�Ż�������
    }
}

void CreateInThread(ThreadTree T){
    ThreadTree pre = NULL;
    if(T != NULL){
        InThread(T, pre);
        pre->rchild = NULL;           //������������һ���ڵ�
        pre->rtag = 1;
    }
}

///�����������ı���
/*
firstnode�������������ĵ�һ�����ʵĽڵ�
nextnode�����������������������ʵ���һ���ڵ�
����������������ӣ�����һ���ڵ����rchild
���û�У���ʾ����������������������ĵݹ�˼�룬��һ���ڵ���൱������������ҽڵ�Ϊ���ڵ����������������׽ڵ�
nextNode = firstNode(p->rchild);
*/
ThreadTree FirstNode(ThreadTree p){
    while(p->ltag == 0) p = p->lchild;
    return p;
}

ThreadTree NextNode(ThreadTree p){
    if(p->rtag == 0) return FirstNode(p->rchild);
                                      //���ҽڵ㣬�������ҽڵ�Ϊ�������ĵ�һ���ڵ�
    else return p->rchild;            //rtagΪ1ʱ��rchild����ָ����һ��
}

void Visit(ThreadTree T){
    printf("%c ", T->data);
}

void InOrder(ThreadTree T){
    for(ThreadTree p = FirstNode(T); p != NULL; p = NextNode(p))
        Visit(p);
}

int main()
{
    ThreadNode *T=(ThreadNode*)malloc(sizeof(ThreadNode));
    T=InitThreadTree();
    InThread(T,NULL);
    InOrder(T);
    return 0;
}

