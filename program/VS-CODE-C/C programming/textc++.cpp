#include <iostream>
using namespace std;
int main( )
{
	char a[]="morning", t;
	int i, j=0;
	for(i=1;i<7;i++)
		if(a[j]<a[i])
			{j=i;
	t=a[j];
	a[j]=a[7];
	a[7]=a[j];
	puts(a);
	printf("\n");
	}
	return 0;
}
