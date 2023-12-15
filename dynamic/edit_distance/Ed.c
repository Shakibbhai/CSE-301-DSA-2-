/// ed problem, insert, deletion, substitution
#include<stdio.h>
#include<limits.h>
#include<string.h>

char s1[1000],s2[1000];
int b[100][100];
void res(int cnt,int p,int q);
int main()
{
    freopen("ed.txt","r",stdin);
    puts("enter the strings");
    //char s1[1000],s2[1000];
    gets(s1);
    gets(s2);
    /// converting s1 into s2
    int len1=strlen(s1);
    int len2=strlen(s2);

    int c[len1+1][len2+1];
   // int b[len1+1][len2+1];    /// match=0,insert=1,delete=2, subs=3

    for(int i=0; i<=len1; i++)
    {
        c[i][0]=i;
        b[i][0]=2;
    }
    for(int i=0; i<=len2; i++)
    {
        c[0][i]=i;
        b[0][i]=1;
    }

    /// processing
    for(int i=0; i<len1; i++)
    {
        for(int j=0; j<len2; j++)
        {
            if(s1[i]==s2[j])
            {
                c[i+1][j+1]=c[i][j];
                b[i+1][j+1]=0;
            }
            else     /// c[i-1][j-1]=3,c[i-1][j]=2,c[i][j-1]=1
            {
                if(c[i+1][j]<c[i][j+1])   /// 1<2
                {
                    if(c[i+1][j]<c[i][j])    ///1<3
                    {
                        c[i+1][j+1]=c[i+1][j]+1;
                        b[i+1][j+1]=1;
                    }
                    else
                    {
                        c[i+1][j+1]=c[i][j]+1;
                        b[i+1][j+1]=3;
                    }
                }
                else   /// 2<1
                {
                    if(c[i][j+1]<c[i][j])    /// 2<3
                    {
                        c[i+1][j+1]=c[i][j+1]+1;
                        b[i+1][j+1]=2;
                    }
                    else
                    {
                        c[i+1][j+1]=c[i][j]+1;
                        b[i+1][j+1]=3;
                    }
                }
            }
        }
    }

    /// processing
    printf("the cost is = %d \n",c[len1][len2]);

    /// PRINTING
    int cnt=c[len1][len2];
    int p=len1,q=len2;
    res(cnt,p,q);
}

void res(int cnt,int p,int q)
{
    if(cnt==0)
        return ;
    if(b[p][q]==0)
    {
        //p-=1,q-=1;
        res(cnt,p-1,q-1);
    }
    else if(b[p][q]==1)
    {
        //q-=1;
        cnt--;
        res(cnt,p,q-1);
        printf("insert %c of %s --> %c%s\n",s2[q-1],s2,s2[q-1],s1);

    }
    else if(b[p][q]==2)
    {
       // p-=1;
        cnt--;
        res(cnt,p-1,q);
        printf("delete %c from %s-->\n",s1[p-1],s1);
       /* for(int i=0;i<strlen(s1);i++)
        {

        }*/

    }
    else
    {
       // p-=1,q-=1;
        cnt--;
        res(cnt,p-1,q-1);
        printf("replace %c of %s with %c from %s\n",s1[p-1],s1,s2[q-1],s2);

    }
}

