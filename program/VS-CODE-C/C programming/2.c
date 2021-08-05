#include <stdio.h>
int main()
{

    flat r,h,l,s,sq,vq,vz;
     scanf("%f%f",&r,&h);
l=2*3.1415926*r;
s=3.1415926*r*r;
sq=4*3.1415926*r*r;
vq=(4.0/3)*3.1415926*r*r*r;
vz=3.1415926*r*r*h;
printf("%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n",l,s,sq,vq,vz);
return 0;
}
