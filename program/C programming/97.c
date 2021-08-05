#include<stdio.h>
struct info
{
    char name[20];
    int cnt1,time1,cnt2,time2,cnt3,time3,cnt4,time4;
    int sumtime,sumcnt;
};
int main()
{
    int n,i;
    int maxcnt=0;
    int mintime=0;
    int pos=0;
    scanf("%d",&n);
    struct info A[n];
    for(i=0;i<n;i++)
    {
        scanf("%s%d%d%d%d%d%d%d%d",A[i].name,&A[i].cnt1,&A[i].time1,&A[i].cnt2,&A[i].time2,&A[i].cnt3,&A[i].time3,&A[i].cnt4,&A[i].time4);
        A[i].sumtime=A[i].time1!=0?(A[i].cnt1-1)*20+A[i].time1:0;
        A[i].sumtime=A[i].time2!=0?(A[i].cnt2-1)*20+A[i].time2:0;
        A[i].sumtime=A[i].time3!=0?(A[i].cnt3-1)*20+A[i].time3:0;
        A[i].sumtime=A[i].time4!=0?(A[i].cnt4-1)*20+A[i].time4:0;
        A[i].sumcnt=(A[i].time1==0?0:1)+(A[i].time2==0?0:1)+(A[i].time3==0?0:1)+(A[i].time4==0?0:1);
        if((A[i].sumcnt>maxcnt)||((A[i].sumcnt==maxcnt&&mintime>A[i].sumtime)))
        {
            pos=i;
            maxcnt=A[i].sumcnt;
            mintime=A[i].sumtime;
        }
    }
    printf("%s %d %d",A[pos].name,maxcnt,mintime);
    return 0;

}

