/* memorized version */

#include<bits/stdc++.h>
using namespace std;

int totalSteps(int stairIndex,vector<int>&DP)
{
    if(stairIndex==0) return 1;
    if(DP[stairIndex]!=-1) return DP[stairIndex];

    int left,right;
    left=totalSteps(stairIndex-1,DP);
    right=1;
    if(stairIndex>1)
    right=totalSteps(stairIndex-2,DP);

    DP[stairIndex]=right+left;

    return DP[stairIndex];
}

int main()
{
    int stairNumber;
    cin>>stairNumber;

    vector<int>DP(stairNumber,-1);
    cout<<"total distinct steps: "<<totalSteps(stairNumber-1,DP);
}
