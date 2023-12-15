
    #include<stdio.h>
    int fibo_no[100]={-1};
    int fibo(int m){
    if(m<=1){
    return m;
    }
     else if (fibo_no[m]>=0) {
        fibo_no[m]=fibo(m-1)+fibo(m-2);
    return fibo_no[m];
    }
    }
    int main()
    {
    int n,i;
    printf("enter the number of series:");
    scanf("%d",&n);
    printf("Dynamic series:\n");
    for(i=0;i<n;i++){
    printf("%d\n",fibo(i));
    }
    return 0;
    }
