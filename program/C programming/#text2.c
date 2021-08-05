#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
    srand((unsigned int)time(NULL));
    int x=rand()%100+100;
    for(int i=1;i<10;i++)
        printf("%d ",rand()%100+100);
    return 0;
}
