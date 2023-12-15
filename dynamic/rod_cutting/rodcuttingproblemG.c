/// general just showing the revenue for one rod
#include<stdio.h>
#include<limits.h>

int main()
{
    freopen("rodc.txt","r",stdin);
    puts("enter the rod length");
    int length;
    scanf("%d",&length);
    int price[length+1];
    price[0]=0;
    int revenue[length+1];
    int saveP[length+1];
    puts("enter the prices");
    for(int i=1;i<=length;i++)
    {
        scanf("%d",&price[i]);
        revenue[i]=INT_MIN;
    }
    revenue[0]=0,saveP[0]=0;
    for(int i=1;i<=length;i++)
    {
        int q=INT_MIN;
        for(int j=1;j<=i;j++)
        {
            if(q<(price[j]+revenue[i-j]))
            {
                q=price[j]+revenue[i-j];
                saveP[i]=j;
            }
        }
        revenue[i]=q;
    }

    printf("%d \n",revenue[length]);

    /// cutting points
    for(int i=length;i>0;)
    {
        printf("%d ",saveP[i]);
        i-=saveP[i];
    }
}
