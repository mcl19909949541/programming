#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct node{
    char data;
    struct node *next;
}Node;

typedef struct LinkStack{//这是一个链栈，其成员是栈元素的节点的指针
    Node *top;
}Stack;

//*****辅助函数*****//
int IsEmpty(Stack *PStack){//判断栈顶是否为空
    if(PStack->top==NULL){
        return TRUE;
    }
    return FALSE;
}

void Push(Stack *PStack, char c){//压入栈
    Node *p;
    p = (Node*)malloc(sizeof(Node));
    p->data = c;
    //将原来的栈顶值PS->top,转换成了新栈顶值的下项即PS->next->top
    p->next = PStack->top;
    PStack->top = p;
}

char Pop(Stack *PStack){//弹出栈
    Node *p;
    char elem;
    p = PStack->top;
    elem = p->data;
    PStack->top = PStack->top->next;
    free(p);
    return elem;
}

char GetTopElement(Stack *PStack){//返回栈顶元素
    return PStack->top->data;
}

int Match(char ch_left,char ch_right){//判断ch_left、ch_right是否括号能合法配对，合法配对返回TRUE，否则返回FALSE
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
//*****辅助函数*****//

void IsLegel(Stack *S,char ch[]){//判断字符串是否括号能完全合法配对，合法配对返回TRUE，否则返回FALSE
    char elem,*p = ch;//这里之所以用地址表示ch，是方便之后对ch的遍历
    while(*p){
        switch(*p){
            //当出现左括号，压入栈
            case'(':
            case'[':
            case'{':
                Push(S,*p++);break;
            case')':
            case']':
            case'}':
            //当出现右括号，需要配对时
                if(IsEmpty(S)==TRUE){//栈为空，配对失败
                    printf("no");
                    return;
                }
                else{
                    elem = GetTopElement(S);
                    if(Match(elem,*p)){//该右括号配对成功，弹出栈中与之配对的左括号
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


