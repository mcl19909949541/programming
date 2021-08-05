#include<stdio.h>
#include<stdlib.h>

typedef struct map
{
    int num;
    int Map[100][100];
} map;

typedef struct queue
{
    int front ;
    int  near ;
    int elem[100];
} queue;
int visit[100] = {0};
void createmap(map *p,int n)
{
    int u,v;
    for (int i = 1; i <= n;i++)
        for (int j = 1; j <= n;j++)
            p->Map[i][j] = 1000;
    for(int i = 1; i <= n;i++)
        p->Map[i][i] = 0;
        for (int i = 1; i < n; i++)
        {
            scanf("%d %d", &u, &v);
            p->Map[u][v] = 1;
        }
}

void dfsmap(map p,int n,int m)
{
    

    visit[m] = 1;
    printf("%d ", m);
    for (int i = 1; i <= n;i++)
    {
        if(visit[i]==0&&p.Map[m][i]==1)
            dfsmap(p, n, i);
    }
}

void initqueue(queue *Q)
{
    Q->front = -1;
    Q->near = -1;
}
void putin(queue *Q,int n)
{
    Q->near++;
    Q->elem[Q->near] = n;
}

int output(queue *Q)
{
    Q->front++;
    return Q->elem[Q->front];
}

int Isempty(queue *Q)
{
    return (Q->front == Q->near);
}

void bfsmap(map p,int i)
{
    int k;
    queue Q;
    initqueue(&Q);
    visit[1] = 1;
    putin(&Q, 1);
    
    while(!Isempty(&Q))
    {
        k = output(&Q);
        visit[k] = 1;
        printf("%d ", k);
        for (int j = 1; j <= i;j++)
            {
                if(visit[j]==0&&p.Map[k][j]==1)
                    putin(&Q, j);
            }
    }

}

int main()
{
    queue Q;
    map p;
    int i;
    scanf("%d", &i);
    createmap(&p, i);
    // printf("dfs：");
    // dfsmap(p, i,1);
    // for (int n = 1; n <= i;n++)
    //         {for (int m = 1; m <= i;m++)
    //             printf("%d ", p.Map[n][m]);
    //             printf("\n");}
    printf("bfs：");
    bfsmap(p, i);

    return 0;
}