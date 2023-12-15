/// 0/1 knapsack
/**
--> actually sorting is not necessary in top-down approach but in the bottom-up approach,
    sorting is required in that sense, we will sequentially solve sub problem, which we
    consider will be needed.
**/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct iteminfo
{
    int itemNo;
    int value;
    int weight;
};

int main()
{
    freopen("o1knapsack.txt","r",stdin);
    puts("enter the number of items and weight of the sack");
    int itemNum,sackWeight;
    scanf("%d%d",&itemNum,&sackWeight);

    struct iteminfo itemInfo[itemNum];

    puts("enter the weight and price");
    for(int i=0; i<itemNum; i++)
    {
        scanf("%d",&itemInfo[i].weight);
    }

    for(int i=0; i<itemNum; i++)
    {
        scanf("%d",&itemInfo[i].value);
        itemInfo[i].itemNo=i+1;
    }

    int p[itemNum+1][sackWeight+1];

    // setting part
    for(int i=0; i<=sackWeight; i++)
    {
        p[0][i]=0;
    }

    for(int i=0; i<=itemNum; i++)
    {
        p[i][0]=0;
    }

    // sorting
    for(int i=1; i<itemNum; i++)
    {
        for(int j=itemNum-1; j>i; j--)
        {
            if(itemInfo[i].weight>itemInfo[j].weight)
            {
                struct iteminfo temp;
                temp=itemInfo[i];
                itemInfo[i]=itemInfo[j];
                itemInfo[j]=temp;
            }
        }
    }

    for(int i=0; i<itemNum; i++)
    {
        printf("%d %d %d\n",itemInfo[i].weight,itemInfo[i].value,itemInfo[i].itemNo);
    }

    // main task
    for(int i=1; i<=itemNum; i++)
    {
        for(int j=1; j<=sackWeight; j++)
        {
            if(itemInfo[i-1].weight>j)
            {
                p[i][j]=p[i-1][j];
            }
            else
            {
                int t1,t2;
                t1=itemInfo[i-1].value+p[i-1][j-itemInfo[i-1].weight];
                t2=p[i-1][j];
                if(t1>t2)
                {
                    p[i][j]=t1;
                }
                else
                {
                    p[i][j]=t2;
                }
            }
        }
    }

    for(int i=0;i<=itemNum;i++)
    {
        for(int j=0;j<=sackWeight;j++)
        {
             printf("%d ",p[i][j]);
        }
        puts("");
    }

    // result
    printf("\ntotal = %d\n",p[itemNum][sackWeight]);

    // finding the item
    int x[itemNum+1];
    int a,b,profit;
    a=itemNum,b=sackWeight;
    profit=p[a][b];
    x[0]=-1;

    while(profit>0)
    {
        if(p[a][b]==p[a-1][b])
        {
            x[itemInfo[a-1].itemNo]=0;
            a--;
        }
        else
        {
            x[itemInfo[a-1].itemNo]=1;
            profit-=itemInfo[a-1].value;
            b=b-itemInfo[a-1].weight;
            a--;
        }
    }

    for(int i=1;i<=itemNum;i++)
    {
        printf("%d ",x[i]);
    }
}
