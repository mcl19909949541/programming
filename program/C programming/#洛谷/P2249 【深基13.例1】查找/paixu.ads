void paixu(int a[])
{   int t;
    for(int i=0;i<10-1;i++)
        for(int j=i;j<10;j++)
    {
        if(a[i]>a[j])
          t=a[i],a[i]=a[j],a[j] =t;
    }
}

