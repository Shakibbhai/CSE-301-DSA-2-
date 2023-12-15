/// n choose r --> combination problem

#include<stdio.h>
#include<limits.h>
int com[1280][1280];

int giveMin(int a,int b)
{
    if(a<=b)
        return a;
    else
        return b;
}

int giveCom(int n,int r)
{
    if(com[n][r]>=0)
        return com[n][r];
    if(r==0 || r==1)
        com[n][r]=n;
    else if(r==n)
        com[n][r]=1;
    else
    {
        com[n][r]=giveCom(n-1,r)+giveCom(n-1,r-1);
    }
    return com[n][r];
}

int main()
{
    puts("let's look at the n choose r problem, a combination problem (--)");
    puts("enter n and r");
    int n,r;
    scanf("%d%d",&n,&r);

    for(int i=0; i<=n; i++)
    {
        for(int j=0; j<=giveMin(i,r); j++)
            com[i][j]=INT_MIN;
    }

    printf("the n choose r = %d \n",giveCom(n,r));
}
