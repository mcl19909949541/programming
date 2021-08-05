#include<stdio.h>
#include<time.h>
void timesum(int AH,int AM,int AS,int BH,int BM,int BS)
{
    int h=0,m=0,s=0;
    if(AS+BS>59) s=(AS+BS)-60,m++;
    else s=AS+BS;
    if(AM+BM>59) m+=((AM+BM)-60),h++;
    else m=AM+BM;
    h+=(AH+BH);
    printf("%d %d %d\n",h,m,s);

}
int main()

{
    int  AH,AM,AS,BH,BM,BS;
    scanf("%d%d%d%d%d%d%d",&AH,&AM,&AS,&BH,&BM,&BS);
    timesum(AH,AM,AS,BH,BM,BS);
    return 0;
}
