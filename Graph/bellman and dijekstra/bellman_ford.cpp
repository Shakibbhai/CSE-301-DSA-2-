
#include<iostream>

using namespace std;

#define SIZE 100
#define INFINITY 1000000

int w[SIZE][SIZE], d[SIZE], prv[SIZE];
int n = 0;
string name[SIZE];

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
    // cout<<name[u]<<" "<<name[v]<<" "<<w[u][v]<<endl;
    if(d[v] > d[u] + w[u][v]){
        d[v] = d[u] + w[u][v];
        prv[v] = u;
    }
}

void traverse(int source, int v){
    if(v == source) {
        cout<<name[source]<<" -> ";
        return;
    }
    traverse(source, prv[v]);
    cout<<name[v]<<" -> ";
}

void printPath(int source){
    for(int i=0; i<n; i++){
        if(i != source){
            cout<<"Shortest path from "<<name[source]<<" to "<<name[i]<<" : ";
            traverse(source, i);
            cout<<endl;
        }

    }
}

bool bellmanFord(int source){

    initiate(source);

    for(int iter=0; iter<n-1 ;iter++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(w[i][j] != 0)
                    relax(i, j);
            }
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(d[j]> d[i]+ w[i][j] && w[i][j] != 0) return false;
        }

    }
    return true;
}

int main(){

    freopen("bell_man_input.txt","r",stdin);
    readInput();
    printGraph();

    //cout<<"n: "<<n<<endl;

    int source = 0;
    bool isPossible = bellmanFord(source);
    if(!isPossible){
        cout<<"Negative cycle found so Bellmanford is not possible."<<endl;
    }
    else{
        cout<<"d[u] after Bellman_Ford :"<<endl;
        for(int i=0; i<n; i++){
            cout<<name[i]<<":"<<d[i]<<" ";
        }
        cout<<endl;
        cout<<"parents for every node: "<<endl;
        for(int i=0; i<n; i++){
            cout<<name[i]<<":"<<name[prv[i]]<<" ";
        }
        cout<<endl;
        printPath(source);
    }



}
