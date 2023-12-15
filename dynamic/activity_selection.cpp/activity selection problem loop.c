#include<stdio.h>

int main()
{
    int activityNum;
    puts("enter activity number");
    scanf("%d",&activityNum);

    int startTime[activityNum],finishTime[activityNum];
    int trackAct[1000]={0},sortedAct[activityNum];

    puts("enter starting and ending time");
    for(int i=0;i<activityNum;i++)
    {
        scanf("%d",&startTime[i]);
    }
    for(int i=0;i<activityNum;i++)
    {
        scanf("%d",&finishTime[i]);
        if(trackAct[finishTime[i]]==0)
         trackAct[finishTime[i]]=i+1;
    }
    /// for print
    for(int i=0;i<activityNum;i++)
    {
        printf("%d  %d\n",startTime[i],finishTime[i]);
    }
    /// sorting
    for(int i=1;i<activityNum;i++)
    {
        for(int j=activityNum-1;j>=i;j--)
        {
            int temp;
            if(finishTime[j-1]>finishTime[j])
            {
                temp=finishTime[j];
                finishTime[j]=finishTime[j-1];
                finishTime[j-1]=temp;

                temp=startTime[j];
                startTime[j]=startTime[j-1];
                startTime[j-1]=temp;
            }
            if((finishTime[j-1]==finishTime[j]) && (startTime[j-1]>startTime[j]))
            {
                temp=finishTime[j];
                finishTime[j]=finishTime[j-1];
                finishTime[j-1]=temp;

                temp=startTime[j];
                startTime[j]=startTime[j-1];
                startTime[j-1]=temp;
            }
        }
    }
    // sorted
    for(int i=0;i<activityNum;i++)
    {
        printf("%d  %d\n",startTime[i],finishTime[i]);
    }

    int result[activityNum];
    int id=0,res;
    result[id]=res=trackAct[finishTime[0]];
    int cnt=0;
    for(int i=1;i<activityNum;i++)
    {
        if(startTime[i]>=finishTime[res])
        {
            id++;
           // int resl;
            result[id]=trackAct[finishTime[i]];
           // printf("%d \n",resl);
            res=i;
        }
    }
  //  printf("%d %d\n",trackAct[startTime[7]],trackAct[finishTime[7]]);
    for(int i=0;i<=id;i++)
    {
        printf("%d  \n",result[i]);
    }
    /**
    1 4 5 6 9 11 10 6 8 13 15
    5 6 9 10 12 15 18 8 10 14 21
    **/
}
