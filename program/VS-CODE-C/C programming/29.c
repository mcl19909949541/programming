#include<stdio.h>
#include<math.h>
int main()
{
    int ce,y,m,n,a=0;
    scanf("%d",&n);
    for(ce=0;;ce+=100){
        for(y=ce+1;y<ce+100;y+=2){
            for(m=3;m<sqrt(y);m+=2){
                if(y%m==0) break;
            }
            if(m>=sqrt(y)) break;
        }
        if(y==ce+101) a++;
        if(a==n) break;

    }
    printf("%d %d\n",ce,ce+99);
    return 0;
}
