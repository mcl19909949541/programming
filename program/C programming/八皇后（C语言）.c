#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXVEX 10
typedef char VerType;	//顶点值类型

struct EdgeNode{
	int adjvex;	//邻接点域，存储该顶点对应的下标
	int weight;	//用于存储权值，对于非网图可以不需要
	struct EdgeNode* next;	//下一个结点
};

struct VertexNode{
	int in;	//入度
	VerType data;	//值
	struct EdgeNode* firstedge;	//邻接表头指针
};

struct Graph{
	struct VertexNode vers[MAXVEX];
	int numVertexes, numEdges;	//顶点数和边数
};

/* 拓扑排序，若G没有回路，则输出拓扑排序序列并返回OK，若有回路返回ERROR */
bool TopologicalSort(struct Graph* G){
	struct EdgeNode* e;
	int i, k, gettop;
	int top = 0;	//栈指针下标
	int count = 0;	//统计输出顶点个数
	int* stack;	//存储入度为0的顶点
	stack = (int*)malloc(G->numVertexes * sizeof(int));

	for(i = 0;i<G->numVertexes;i++)	//遍历所有结点
		if(G->vers[i].in == 0)
			stack[++top] = i;	//将入度为0的顶点入栈

	while(top != 0){
		gettop = stack[top--];	//出栈
		printf("%c ",G->vers[gettop].data);
		count++;	//统计输出顶点数
		for(e=G->vers[gettop].firstedge; e; e = e->next){
			//弧表遍历
			k = e->adjvex;
			if(!(--G->vers[k].in))	//将k号顶点邻接点的入度减1
				stack[++top] = k;	//若为0则入栈，以便下次循环输出
		}
	}
	if(count < G->numVertexes)	//如果count小于顶点数，说明存在环
		return false;
	else
		return true;
}

/* 图初始化 */
void CreateGraph(struct Graph* G){
	int i, m, n;

	printf("输入顶点数和边数：\n");
	scanf("%d,%d",&G->numVertexes, &G->numEdges);
	printf("输入顶点值：\n");
	for(i=0;i<G->numVertexes;i++){
		getchar();	//吃掉回车
		scanf("%c",&G->vers[i].data);
	}
	//初始化图头结点指针和入度值
	for(i=0;i<G->numVertexes;i++){
		G->vers[i].firstedge = NULL;
		G->vers[i].in = 0;	//入度为0
	}
	printf("输入边：\n");
	for(i=0;i<G->numEdges;i++){
		scanf("%d,%d",&m, &n);
		struct EdgeNode *newNode = (struct EdgeNode*)malloc(sizeof(struct EdgeNode));
		newNode->next = G->vers[m].firstedge == NULL ? NULL : G->vers[m].firstedge;
		newNode->adjvex = n;
		G->vers[m].firstedge = newNode;
		G->vers[n].in++;	//入度+1
	}
}

int main(){

	struct Graph *G=(struct Graph*)malloc(sizeof(struct Graph)) ;
	CreateGraph(G);
	if(TopologicalSort(G)){
		printf("拓扑排序完成！\n");
	}else{
		printf("图存在环");
	}
	return 0;
}
