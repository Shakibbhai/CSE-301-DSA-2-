#include <bits/stdc++.h>
using namespace std;


int minimumPathSum(vector<vector<int>>& triangle, int n,int m){
	vector<vector<int>>DP(n,vector<int>(m,0));
	for(int i=0;i<m;i++) DP[n-1][i]=triangle[n-1][i];

	for(int i=n-2;i>=0;i--)
	{
		for(int j=m-1;j>=0;j--)
		{
			int up=INT_MAX,upRight=INT_MAX,upLeft=INT_MAX;
            up=triangle[i][j]+DP[i+1][j];
			if(j>0)
            upLeft=triangle[i][j]+DP[i+1][j-1];
			DP[i][j]=min(up,upLeft);
			if(j<m)
			upRight=triangle[i][j]+DP[i+1][j+1];
			DP[i][j]=min(DP[i][j],upRight);
		}
	}

	int mini=1e9;
	for(int i=0;i<m;i++)
    {
        mini=min(mini,DP[0][i]);
    }

    return mini;
}

int main()
{
    freopen("rock.txt","r",stdin);
    int n,m;cin>>n>>m;
    vector<vector<int>>rock(n,vector<int>(m));

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>>rock[i][j];
        }
    }

    cout<<minimumPathSum(rock,n,m);
}
