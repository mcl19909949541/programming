#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct node{
    char data;
    struct node *next;
}Node;

typedef struct LinkStack{//����һ����ջ�����Ա��ջԪ�صĽڵ��ָ��
    Node *top;
}Stack;

//*****��������*****//
int IsEmpty(Stack *PStack){//�ж�ջ���Ƿ�Ϊ��
    if(PStack->top==NULL){
        return TRUE;
    }
    return FALSE;
}

void Push(Stack *PStack, char c){//ѹ��ջ
    Node *p;
    p = (Node*)malloc(sizeof(Node));
    p->data = c;
    //��ԭ����ջ��ֵPS->top,ת��������ջ��ֵ�����PS->next->top
    p->next = PStack->top;
    PStack->top = p;
}

char Pop(Stack *PStack){//����ջ
    Node *p;
    char elem;
    p = PStack->top;
    elem = p->data;
    PStack->top = PStack->top->next;
    free(p);
    return elem;
}

char GetTopElement(Stack *PStack){//����ջ��Ԫ��
    return PStack->top->data;
}

int Match(char ch_left,char ch_right){//�ж�ch_left��ch_right�Ƿ������ܺϷ���ԣ��Ϸ���Է���TRUE�����򷵻�FALSE
    if(ch_left=='(' && ch_right==')'){
        return TRUE;
    }
    else if(ch_left=='[' && ch_right==']'){
        return TRUE;
    }
    else if(ch_left=='{' && ch_right=='}'){
        return TRUE;
    }
    else{
        return FALSE;
    }
}
//*****��������*****//

void IsLegel(Stack *S,char ch[]){//�ж��ַ����Ƿ���������ȫ�Ϸ���ԣ��Ϸ���Է���TRUE�����򷵻�FALSE
    char elem,*p = ch;//����֮�����õ�ַ��ʾch���Ƿ���֮���ch�ı���
    while(*p){
        switch(*p){
            //�����������ţ�ѹ��ջ
            case'(':
            case'[':
            case'{':
                Push(S,*p++);break;
            case')':
            case']':
            case'}':
            //�����������ţ���Ҫ���ʱ
                if(IsEmpty(S)==TRUE){//ջΪ�գ����ʧ��
                    printf("no");
                    return;
                }
                else{
                    elem = GetTopElement(S);
                    if(Match(elem,*p)){//����������Գɹ�������ջ����֮��Ե�������
                        Pop(S);
                    }
                    else{
                        printf("no");
                        return;
                    }
                }
            default:
                p++;
        }
    }
    if(IsEmpty(S)){
        printf("yes");
        return;
    }
    else{
        printf("no");
        return;
    }
}

int main(){
    char ch[100];
    gets(ch);
    Stack *S;
    S = (Stack*)malloc(sizeof(Stack));
    S->top = NULL;
    IsLegel(S,ch);
    return 0;
}


