#include<stdio.h>


int a[10000];

int main(){
	int n,m,i=1;
	scanf("%d",&m);
	n=m;
	while(n!=1){
		if(n%2==0){
			n/=2;
		}else{
			n=n*3+1;
		}
		a[i]=n;
		i++;
	}
	for(int j=i-1;j>0;j--){
		printf("%d " ,a[j]);
	}
	printf("%d",m);
	return 0;
}
