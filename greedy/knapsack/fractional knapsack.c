#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct item{
    int itemId;
    double weight;
    double benefit;
    double value;
};

int main()
{
    //freopen("np.txt","r",stdin);
    int n;
    scanf("%d",&n);
    struct item items[n];
    for(int i=0;i<n;i++)
    {
        scanf("%lf%lf ",&items[i].weight,&items[i].benefit);
        items[i].itemId=i+1;
        items[i].value=items[i].benefit/items[i].weight;
    }

    for(int i=1;i<n;i++)
    {
        for(int j=n-1;j>=i;j--)
        {
            if(items[j].value>items[j-1].value)
            {
                struct item temp;
                temp=items[j];
                items[j]=items[j-1];
                items[j-1]=temp;
            }
        }
    }

    double targetWeight,weighttemp;
    scanf("%lf",&targetWeight);
    weighttemp=targetWeight;
    struct item soltn[n];
    int i;
    double totalbenefit=0;
    for(i=0;i<n;i++)
    {
        if(items[i].weight<=targetWeight)
        {
            soltn[i]=items[i];
            targetWeight-=items[i].weight;
            totalbenefit+=items[i].benefit;
        }
        else
            break;
    }
    if(i<n)
    {
        soltn[i]=items[i];
        soltn[i].weight=targetWeight;
        soltn[i].benefit=items[i].value*targetWeight;
        totalbenefit+=soltn[i].benefit;
    }

    printf("total benefit: %lf\n",totalbenefit);
    for(int j=0;j<=i;j++)
    {
        printf("%d. of weight %lf of benefit %lf\n",soltn[j].itemId,soltn[j].weight,soltn[j].benefit);
    }
}
