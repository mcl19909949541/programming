#include<stdio.h>
#include<stdlib.h>


typedef struct ThreadNode{
    char data;
    struct ThreadNode * lchild, * rchild;
    int ltag, rtag;//0为不建立前驱或后驱，1为建立
}ThreadNode, * ThreadTree;

ThreadTree InitThreadTree();
void InThread(ThreadTree p,ThreadTree pre);  //通过中序遍历对二叉树线索化
void CreateInThread(ThreadTree T);  //通过中序遍历建立中序二叉树

ThreadTree FirstNode(ThreadTree p); //求中序遍历下的第一个节点
ThreadTree NextNode(ThreadTree p);  //求节点p在中序序列下的后一个节点
void Visit(ThreadTree T);
void InOrder(ThreadTree T); //中序遍历

///线索二叉树的建立
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

///线索二叉树的线索化
/*
* 首先如果根节点的lchild为null，那么根节点的lchild为pre为null
* 第二个if的时候，pre不为null的时候才执行，第一次是不执行的
* 根节点的左孩子线索完毕之后，pre就指向了根节点了，然后递归
* 递归之后，指针pre每次都会指向刚刚访问过的节点
* 中序遍历，如果左孩子不为空，就会一直继续处理左孩子知道左孩子为空，然后处理右孩子
*/

void InThread(ThreadTree p,ThreadTree pre){
    if(p != NULL){                   //p是当前节点，pre是刚访问的节点
        InThread(p->lchild, pre);    //递归，优化左子树
        if(p->lchild == NULL){       //左子树为空，建立前驱线索
            p->lchild = pre;
            p->ltag = 1;
        }
        if(pre != NULL && pre->rchild == NULL){
            pre->rchild = p;          //右子树为空，就建立前驱节点的后及线索
            pre->rtag = 1;
        }
        pre = p;                      //p刚刚访问过了，则pre = p
        InThread(p->rchild, pre);     //递归，优化右子树
    }
}

void CreateInThread(ThreadTree T){
    ThreadTree pre = NULL;
    if(T != NULL){
        InThread(T, pre);
        pre->rchild = NULL;           //处理遍历的最后一个节点
        pre->rtag = 1;
    }
}

///线索二叉树的遍历
/*
firstnode是中序遍历下面的第一个访问的节点
nextnode是这个结点在中序遍历下面访问的下一个节点
如果有右子树的链接，则下一个节点就是rchild
如果没有，表示存在右子树，由中序遍历的递归思想，下一个节点就相当于以这个结点的右节点为根节点在中序遍历下面的首节点
nextNode = firstNode(p->rchild);
*/
ThreadTree FirstNode(ThreadTree p){
    while(p->ltag == 0) p = p->lchild;
    return p;
}

ThreadTree NextNode(ThreadTree p){
    if(p->rtag == 0) return FirstNode(p->rchild);
                                      //有右节点，访问以右节点为根的树的第一个节点
    else return p->rchild;            //rtag为1时候，rchild总是指向下一个
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

