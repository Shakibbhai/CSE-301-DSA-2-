/// memorized top-down approach

#include<stdio.h>
#include<limits.h>
int nsu[1280000];

int setNSU(int n)
{
    /// base case
    if(nsu[n]>=0) return nsu[n];
    if(n<=2) nsu[n]=n;
    else nsu[n]=setNSU(n-1)+setNSU(n-2)+setNSU(n-3);      /// 0 1 2 3 6 11 20   \\  0 1 2 3 6 12 23
    return nsu[n];
}

int main()
{
    puts("we have an nsu series(- -)");
    puts("which nth number in the nsu series do you want?");
    int n;
    scanf("%d",&n);

    for(int i=0;i<1280000;i++)
        nsu[i]=INT_MIN;

    printf("the nth number in the nsu series is :  %d",setNSU(n));

}

