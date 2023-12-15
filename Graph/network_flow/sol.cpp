#include<bits/stdc++.h>
using namespace std ;
#define totalSize 50

int src, des ;
int vertex, edge, graph[totalSize][totalSize], resGraph[totalSize][totalSize] ;
vector< int > VertexName ;


bool bfs( int source, int dest, int parent[] )
{
    int s, desination, u ;
    queue< int > q ;
    bool visited[vertex] ;
    for( int i=0; i < vertex; i++ ) visited[i] = false ;
    s = source-1 ;
    desination = dest-1 ;
    q.push(s) ;
    visited[s] = true ;
    parent[s] = -1 ;
    while( !q.empty() ) 
    {
        u = q.front() ;
        q.pop() ;
        for ( int v=0; v<vertex; v++ ) 
        {
            if( visited[v] == false && resGraph[u][v] > 0 ) 
            {
                if (v == desination ) 
                {
                    parent[v] = u ;
                    return true ;
                }
                q.push(v) ;
                parent[v] = u ;
                visited[v] = true ;
            }
        }
    }
    return false ;
}


void read()
{
    int a, b, i, j ;
    for( i = 0; i < totalSize; i++ )
    {
        for( j = 0; j < totalSize; j++ )
        {
            graph[i][j] = 0 ;
            resGraph[i][j] = 0 ;
        }
    }
    freopen("input.txt","r", stdin ) ;
    cin >> vertex;
    cin >> src >> des >> edge ;
    graph[vertex][vertex], resGraph[vertex][vertex] ;
    for( i=0; i<edge; i++ )
    {
        int x, y, cost ;
        
        cin >> x >> y >> cost ;
        
        graph[x-1][y-1] = cost ;
        resGraph[x-1][y-1] = graph[x-1][y-1] ;
    }

}

int Ford()
{
    int i, j ;
    int parent[vertex] ;
    int maxFlow = 0 ;
    while( bfs( src, des, parent ) )
    {
        int flow = INT_MAX ;
        int u, v, s ;
        s = src-1 ;
        v = des-1 ;
        
        while( v != s ) 
        {
            u = parent[v] ;
            flow = min( flow, resGraph[u][v] ) ;
            v = parent[v] ;
        }
        
        v = des-1 ;
        
        while( v != s )
        {
            u = parent[v] ;
            resGraph[u][v] -= flow ;
            v = parent[v] ;
        }
        maxFlow += flow ;
    }
 
    return maxFlow ;
}

int main()
{
    read() ;
    int maxflow = Ford() ; 
    cout << "The bandwidth is " << maxflow << endl ;
}