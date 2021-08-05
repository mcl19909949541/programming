#include<stdio.h>
inline int xchg(unsigned char n)
{
    n=n>>4|n<<4;
    return n;
}
int main()
{
    unsigned char n;
    scanf("%d",&n);
    printf("%d\n",xchg(n));
    return 0;
}
