/* memorized version */

#include<bits/stdc++.h>
using namespace std;

int totalCost(int stairIndex,vector<int>&height,vector<int>&DP)
{
    if(stairIndex==0) return 0;
    if(DP[stairIndex]!=-1) return DP[stairIndex];

    int left,right;
    left=totalCost(stairIndex-1,height,DP)+abs(height[stairIndex]-height[stairIndex-1]);
    right=INT_MAX;
    if(stairIndex>1)
    right=totalCost(stairIndex-2,height,DP)+abs(height[stairIndex]-height[stairIndex-2]);

    DP[stairIndex]=min(right,left);

    return DP[stairIndex];
}

int main()
{
    int stairNumber;
    cin>>stairNumber;
    vector<int>height(stairNumber);
    for(int i=0;i<stairNumber;i++)
    {
        cin>>height[i];
    }

    vector<int>DP(stairNumber,-1);
    cout<<"total cost: "<<totalCost(stairNumber-1,height,DP);
}

