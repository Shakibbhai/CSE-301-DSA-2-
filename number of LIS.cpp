/**
--> this solution contains a naive approach to LIS problem.
--> this approach includes time complexity o(n^2)
**/

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>


void printAns(int index,int positionArray[],int arr[])
{
    if(positionArray[index]==-1)
    {
        printf("%d ",arr[index]);
        return ;
    }
    printAns(positionArray[index],positionArray,arr);

    printf("%d ",arr[index]);

}


int main()
{

    /** taking input from file **/
    freopen("LIS.txt","r",stdin);


    /** input section. **/
    puts("enter the number of elements");
    int arraySize;
    scanf("%d",&arraySize);

    puts("enter the array");
    int arr[arraySize];
    for(int i=0; i<arraySize; i++)
    {
        scanf("%d",&arr[i]);
    }


    /** two arrays to store the length of subsequence and track the position **/
    int lengthArray[arraySize];
    int positionArray[arraySize];


    /** initialize lengthArray and positionArray **/
    lengthArray[0]=1;
    positionArray[0]=-1;


    /** processing section
        formula : 1+max(L[j] && aj<ai
        taking some variables to store maximum length and position
    **/
    int maxLength;
    int position;
    int finalLength=0;
    int finalPosition;
    int ansIdx;
    int cnt[10]={1};
    int t=1;

    for(int i=1; i<arraySize; i++)
    {
        maxLength=0;
        position=-1;

        for(int j=0;j<i;j++)
        {
            if(arr[j]<arr[i] && lengthArray[j]>maxLength)
            {
                maxLength=lengthArray[j];
                position=j;
                cnt[i]=cnt[j];

            }
            else if(arr[j]<arr[i] && lengthArray[j]==maxLength)
            {
                if(arr[position]>arr[j])
                {
                    position=j;
                }
                cnt[i]+=cnt[j];
                t++;
            }
        }

        lengthArray[i]=maxLength+1;
        positionArray[i]=position;

        if(finalLength<lengthArray[i])    /** this is basically on-time tracking **/
        {
            finalLength=lengthArray[i];
            finalPosition=positionArray[i];
            ansIdx=i;
        }
    }

    int total=0;
    for(int i=0;i<arraySize;i++)
       if(finalLength==lengthArray[i])
        total+=cnt[i];

    printf("total= %d ",total);

    /** print the length **/
    printf("length = %d \n",finalLength);


    /** recursive function to print all the elements in the sequence **/
    printAns(ansIdx,positionArray,arr);

    puts("");


    /** time and date, experimenting just. ;) **/
    printf("time: %s  \ndate: %s",__TIME__,__DATE__);

}

