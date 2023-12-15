#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

int numberOfCity;
int cityGraph[100][100];
char route[100];

int main()
{
    freopen("LAB2.txt","r",stdin);
    puts("enter the number of city");
    scanf("%d",&numberOfCity);
    bool ok=false;
    puts("how many connection?");
    int numberOfConnection;
    scanf("%d",&numberOfConnection);
    getchar();

    puts("enter the connection and distance");
    for(int i=0; i<numberOfConnection; i++)
    {
        char u,v;
        int distance;
        scanf("%c%c%d",&u,&v,&distance);
        getchar();
        cityGraph[u-'A'][v-'A']=distance;
        cityGraph[v-'A'][u-'A']=distance;
    }

    puts("enter the source and destination");
    char source,destination;
    scanf("%c%c",&source,&destination);
    int u,v;
    u=source-'A';
    int end=1;
    int id;
    route[0]=source;
    int j=1;
    int markDestination=0;
    while(end)
    {
        int min=INT_MAX;
        ok=false;
        for(int i=0; i<numberOfCity; i++)
        {
            v=i;
            if(cityGraph[u][v])
            {
                if(cityGraph[u][v]<min)
                {
                    id=v;
                    min=cityGraph[u][v];
                    cityGraph[id][u]=0;
                }
                ok=true;
            }
        }
        route[j]=id+'A';
        u=id;
        j++;
        if((id+'A')==destination)
        {
            ok=true;
            break;
        }
        if(ok==false) break;
    }
    if(!ok)
        puts("not found destination");
    else
    {
        puts("found");
        puts("best route: ");
        for(int i=0; i<j; i++)
        {
            printf("%c ",route[i]);
        }
    }
}
