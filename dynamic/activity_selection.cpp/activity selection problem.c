#include<stdio.h>

int startingTime[100],endingTime[100];
int trackActivityEnd[100],trackActivityStart[100],resultantActivity[100];
int activityNumber=0;

void recursiveActivitySelector(int first,int track)
{
    int id=1;
    while((id<=activityNumber) &&(startingTime[id]<endingTime[first]))
    {
        id++;
    }
    if(id<=activityNumber)
    {
        int activity;
        activity=resultantActivity[track]=trackActivityStart[startingTime[id]];
        track++;
        recursiveActivitySelector(activity,track);
    }
}

int main()
{
    puts("how many activites are there?");
    scanf("%d",&activityNumber);
    puts("enter the starting time and finishing time");
    for(int i=1;i<=activityNumber;i++)
    {
        scanf("%d",&startingTime[i]);
        scanf("%d",&endingTime[i]);
        trackActivityEnd[endingTime[i]]=i;
       /// trackActivityStart[startingTime[i]]=i;
    }
    /// bubble sort on finishing time
    for(int i=activityNumber;i>0;i--)
    {
        for(int j=1;j<i;j++)
        {
            int temp;
            if(endingTime[i]<=endingTime[j])
            {
                temp=endingTime[i];
                endingTime[i]=endingTime[j];
                endingTime[j]=temp;
            }
        }
    }
    for(int i=1;i<=activityNumber;i++)
    {
        printf("%d ",endingTime[i]);
    }
    int start,track=0;
    start=resultantActivity[0]=trackActivityEnd[endingTime[0]];
    track++;
    recursiveActivitySelector(start,track);

    for(int i=0;i<track;i++)
    {
        printf("%d ",resultantActivity[i]);
    }
}
