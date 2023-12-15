/* memorized version */

#include<bits/stdc++.h>
using namespace std;

int totalCost(int stairIndex,int k,vector<int>&height,vector<int>&DP)
{
    if(stairIndex==0)
        return 0;
    if(DP[stairIndex]!=-1)
        return DP[stairIndex];

    //int t=max(0,k);
    int cost=INT_MAX,right;
    for(int i=1; i<=k; i++)
    {
        right=INT_MAX;
        if(stairIndex>=i)
            right=totalCost(stairIndex-i,k,height,DP)+abs(height[stairIndex]-height[stairIndex-i]);
        cost=min(right,cost);
    }
    DP[stairIndex]=cost;

    return DP[stairIndex];
}

int main()
{
    int stairNumber,k;
    cin>>stairNumber>>k;
    vector<int>height(stairNumber);
    for(int i=0; i<stairNumber; i++)
    {
        cin>>height[i];
    }

    vector<int>DP(stairNumber,-1);
    cout<<totalCost(stairNumber-1,k,height,DP);
}


