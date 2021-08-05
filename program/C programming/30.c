#include<stdio.h>
int main()
{
    int n,i;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        if(i%7==0) printf("%d ",i);
        else if(i/1000%10==7||i/100%10==7||i/10%10==7||i%10==7) printf("%d ",i);

    }
    return 0;
}
