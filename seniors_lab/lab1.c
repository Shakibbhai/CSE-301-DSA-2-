#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<string.h>

struct activity{
    char description[200];
    int startingTime;
    int finishingTime;
    int taskId;
};

int main()
{
    freopen("lab1.txt","r",stdin);
    puts("enter the number of activities");
    int n;
    scanf("%d",&n);
    getchar();
    struct activity activities[n];
    for(int i=0;i<n;i++)
    {
        gets(activities[i].description);
        scanf("%d %d",&activities[i].startingTime,&activities[i].finishingTime);
        activities[i].taskId=i+1;
        getchar();
    }

    for(int i=1;i<n;i++)
    {
        for(int j=n-1;j>=i;j--)
        {
            if(activities[j].finishingTime<activities[j-1].finishingTime)
            {
                struct activity temp;
                temp=activities[j];
                activities[j]=activities[j-1];
                activities[j-1]=temp;
            }
        }
    }

    for(int i=0;i<n;i++)
    {
        printf("%d. %s %d %d\n",activities[i].taskId,activities[i].description,activities[i].startingTime,activities[i].finishingTime);
    }

    char result[n][200];
    strcpy(result[0],activities[0].description);
    int j=1;
    int totalTask=1;
    int id=0;
    for(int i=1;i<n;i++)
    {
        if(activities[i].startingTime>=activities[id].finishingTime)
        {
            id=i;
            totalTask++;
            strcpy(result[j],activities[i].description);
            j++;
        }
    }

    printf("total completed task: %d\n",totalTask);
    puts("the tasks are");
    for(int i=0;i<j;i++)
    {
        printf("%s\n",result[i]);
    }
}
