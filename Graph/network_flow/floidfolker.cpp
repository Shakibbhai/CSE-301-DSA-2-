#include<iostream>
#include<fstream>
#include<queue>
#include<climits>

using namespace std;
#define max 20
int numV, numE;
int graph[max][max]={0};
int previous[max];
int residual[max][max];
bool visited[max];

bool bfs(int source, int sink){
    cout<<"He";
    for(int i=0;i<numV;i++){
        visited[i]=false;
    }
    queue<int> queue;
    queue.push(source);
    visited[source]=true;
    previous[source]=-1;

    while(!queue.empty()){
        int u = queue.front();
        for(int i=0;i<numV;i++){
            if(!visited[i] && residual[u][i]){
                queue.push(i);
                visited[i]=true;
                previous[i]=u;
            }

        }
    }
    return visited[sink];


}

int floidFulker(int source, int sink){
    for(int i=0;i<numV;i++){
        for(int j=0;j<numV;j++){
            residual[i][j]= graph[i][j];
        }
    }

    
    int flow=0;
    while(bfs(source,sink)==true){
        int minF = INT_MAX;
        for(int i=sink; i!=source; i=previous[i]){
            minF= min(minF,residual[previous[i]][i]);
        }
        flow +=minF;

        for(int i=sink; i!=source;i=previous[i]){
            residual[previous[i]][i] -=minF;
            residual[i][previous[i]] +=minF;

        }
    }
    return flow;
}

void read(){
    ifstream myfile("t.txt");
    myfile>> numV >> numE;
    int u,v,w;
    for(int i=0;i<numE;i++){
        myfile>> u >> v >> w;
        graph[u][v] = w;
    }

    
}
void print(){
    for(int i=0;i<numV;i++){
        for(int j=0;j<numV;j++){
            cout<< graph[i][j]<<"  ";
        }cout<<endl;
    }
}

int main(){
    read();
    print();
    cout<<numV << numE;
    cout<<endl<<endl<<floidFulker(0,5);
}

