#include<iostream>
#include<queue>
#include<functional>
#include<vector>

using namespace std;

#define SIZE 100
#define INFINITY 1000000

// struct comparePair(pair<int, int> &leftEle, pair<int, int> &rightEle){
//     return leftEle.first < rightEle.first;        
// }                                                   // why does not work

int w[SIZE][SIZE], d[SIZE], prv[SIZE];
int n = 0;
string name[SIZE];
bool isPushed[SIZE];
priority_queue< pair<int, int>, vector< pair<int, int>>, greater < pair<int, int>>> stock;  //greater<> reverse the order

void readInput(){
    int u, v;
    string s;
    while (cin>>s){
        if(s == "END")
            break;

        for(u = 0; u < n; u++){
            if(name[u] == s)
                break;
        }
        if (u == n){
            name[n] = s;
            n++;
        }

        cin >> s;
        for(v = 0; v < n; v++){
            if(name[v] == s)
                break;
        }
        if (v == n){
            name[n] = s;
            n++;
        }

        cin >> w[u][v];

    }
}

void printGraph(){   
    cout<<"Adj-Matrix is: "<<endl;
    int u, v;
    for (u = 0; u < n; u++ ){
        for(v = 0; v < n; v++){
            cout << w[u][v] << " ";
        }
        cout << "\n";
    }
}

void initiate(int source){

    for(int i=0; i<n; i++){
        d[i] = INFINITY;
        prv[i] = -1;
    }
    d[source] = 0;
}

void relax(int u, int v){
    if(d[v] >  w[u][v]){
        d[v] =  w[u][v];
        prv[v] = u;
    }
}

void dijkstra(int source){
    initiate(source);

    stock.push(make_pair(d[source], source));
    isPushed[source] = true;

    while(!stock.empty()){
        pair<int ,int> curr = stock.top();

        cout<<name[curr.second]<<" "<<endl;

        for(int i=0; i<n; i++){
            if(w[curr.second][i]){
                relax(curr.second, i);
                if(!isPushed[i]){
                    stock.push(make_pair(d[i], i));
                    isPushed[i] = true;
                }
                    
            }
               
        }
        stock.pop();
        
    }
}

int main(){

    freopen("prim_Input.txt","r",stdin);
    readInput();
    printGraph();

    int source = 0;
    dijkstra(source);

    cout<<"d[u] after dijkstra :"<<endl;
    for(int i=0; i<n; i++){
        cout<<name[i]<<"-"<<d[i]<<" ";
    }
    cout<<endl;
    cout<<"parents for every node: "<<endl;
    for(int i=0; i<n; i++){
        cout<<name[i]<<"-"<<name[prv[i]]<<" ";
    }
    cout<<endl;

    vector< pair<string, string> > mst;
    int maxflow = 0;
    cout<<"Selected edges are: "<<endl;
    for(int i=1; i<n; i++){
        mst.push_back(make_pair(name[prv[i]], name[i]));
        cout<<name[prv[i]]<< " - " <<name[i]<<endl;
        maxflow += d[i];
    }

    cout<<"maxFlow is : "<<maxflow<<endl;
}