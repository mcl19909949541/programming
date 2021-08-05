#include<stdio.h>
#include<stdlib.h>

typedef struct BinTreeNode{
    char data;
    struct BinTreeNode *left;
    struct BinTreeNode *right;
}BinTreeNode;

void CreatBinTree(BinTreeNode *T){
    char data1,data2;
    T->left = NULL;
    T->right = NULL;
    data1 = getchar();
    data2 = getchar();
    //ÿ�ζ�ȡ�����ַ����ж�����XΪ������Ҷ
    //1.data��X+����������Ϊ��
    //2.data��X+����������ΪҶ
    //3.data��X+����������ΪҶ
    //4.data����+X+����������Ϊ��
    //5.data����+X+����������ΪҶ
    if(data1==','){
        T->data = data2;
        data1 = getchar();
        if(data1=='('){
            T->left = (BinTreeNode*)malloc(sizeof(BinTreeNode));
            CreatBinTree(T->left);
            T->right = (BinTreeNode*)malloc(sizeof(BinTreeNode));
            CreatBinTree(T->right);
        }
    }
    else{
        T->data = data1;
        if(data2=='('){
            T->left = (BinTreeNode*)malloc(sizeof(BinTreeNode));
            CreatBinTree(T->left);
            T->right = (BinTreeNode*)malloc(sizeof(BinTreeNode));
            CreatBinTree(T->right);
        }
    }
}

void preOrderOutput(BinTreeNode *T){
    printf("%c",T->data);
    if(T->left){
        preOrderOutput(T->left);
    }
    if(T->right){
        preOrderOutput(T->right);
    }
}

int main(){
    BinTreeNode *T;
    T = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    CreatBinTree(T);
    preOrderOutput(T);
    return 0;
}

