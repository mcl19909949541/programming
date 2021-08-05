#include<stdio.h>
#include<stdlib.h>

#define MAX 200

typedef struct EgdeNode
{
    int endvex; //���ڶ����ֶ�
    int weight;//�ߵ�Ȩ
    struct EdgeNode *nextedge;//���ֶ�
}EdgeList;//�߱�

typedef struct {
int vertex;//������Ϣ
EdgeList *edgelist;//�߱�ͷָ��
}VexNode;//�����

typedef struct {
VexNode vexs[MAX];
int vexNum,edgeNum;//ͼ�Ķ���ͱ߸���

}GraphList;

void CreatGraphList(GraphList *G,int n,int m)
{
    G->vexNum=n;
    G->edgeNum=m;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&G->vexs[i].vertex);//���������
        G->vexs[i].edgelist=NULL;
    }
    int v1,v2;
    for(int j=0;j<m;j++)
    {
        scanf("%d %d",&v1,&v2);//�����߱�
        EdgeList *g=(EdgeList*)malloc(sizeof(EdgeList));
        g->endvex=v2;
        g->nextedge=G->vexs[v1].edgelist;
        G->vexs[v1].edgelist=g;

    }
}


int DFS(GraphList *G,int v1,int v2)
{
    int visited[MAX]={0};
    visited[v1]=1;
    EdgeList *g=G->vexs[v1].edgelist;
    while(g)
    {
        if(g->endvex==v2)
        {
            return 1;
        }
        if(!(visited[g->endvex])&&DFS(G,g->endvex,v2))
        {
            return 1;
            g=g->nextedge;
        }
    }
    return 0;
}

int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    GraphList *G;
    G=(GraphList*)malloc(sizeof(GraphList));
    CreatGraphList(G,n,m);
    int v1,v2;
    scanf("%d %d",&v1,&v2);
    if(DFS(G,v1,v2)){
        printf("yes\n");
    }
    else{
        printf("no\n");
    }
    return 0;

}
