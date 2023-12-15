/// string or list of characters , one solution.

#include<stdio.h>
#include<limits.h>

int main()
{
    freopen("lcb.txt","r",stdin);
    puts("enter the characters sequences and sizes");
    int m,n;
    scanf("%d%d",&m,&n);
    getchar();
    char x[m+1],y[n+1];
    for(int i=1; i<=m; i++)
    {
        scanf("%c",&x[i]);
    }
    getchar();
    for(int i=1; i<=n; i++)
    {
        scanf("%c",&y[i]);
    }

    /// processing
    int c[m+1][n+1],b[m+1][n+1];       /// equal= 0, left=1,up=2
    for(int i=0; i<=n; i++)
        c[0][i]=0;
    for(int i =0; i<=m; i++)
        c[i][0]=0;

    /// b and c together
    for(int i=1; i<=m; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(x[i]==y[j])    /// case 1
            {
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]=0;
            }
            else     /// case 2
            {
                if(c[i-1][j]>=c[i][j-1])
                {
                    c[i][j]=c[i-1][j];
                    b[i][j]=2;
                }
                else
                {
                    c[i][j]=c[i][j-1];
                    b[i][j]=1;
                }
            }
        }
    }

    /// printing
    printf("the lcs is = %d\n",c[m][n]);

    char res[c[m][n]];
    int k=0,i=m,j=n;
    int cnt=c[m][n];
    while(cnt)
    {
        if(b[i][j]==0)
        {
            res[k]=x[i];
            k++;
            cnt--;
            i-=1,j-=1;
        }
        else if(b[i][j]==1)
        {
            j-=1;
        }
        else
        {
            i-=1;
        }
    }
    for(int i=c[m][n]-1;i>-1;i--)
    {
        printf("%c ",res[i]);
    }
}
