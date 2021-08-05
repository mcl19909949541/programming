void Quicksort (int A[],int n,int left,int right)
{
    int i,j,t;
    if(left<right)
    {
        i=left;
        j=right+1;

    while(1){
        while(i+1<n&&A[++i]<A[left]);
        while(j-1>-1&&A[--j]>A[left]);
        if(i>=j) break;
        t=A[i],A[i]=A[j],A[j]=t;

    }
    t=A[left],A[left]=A[j],A[j]=t;
    Quicksort(A,n,left,j-1);
    Quicksort(A,n,j+1,right);
}
}
