#include<bits/stdc++.h>

using namespace std;

int numVertices, numEdges;
int graph[10000][10000];
vector<string> vertices;
map<string, int> temp;
set<pair<int, pair<string, string>>> edges;
set<pair<int, pair<string, string>>> A;
vector<set<string>> sets;
int in = 0;
int totalWeight = 0;
int optweight=0;

void getInput() {
    freopen("kruskalLab.txt", "r", stdin);
    cin >> numVertices >> numEdges;
    graph[numVertices][numVertices];

   // vertices.clear();  // Clear the vertices set

    for (int i = 0; i < numEdges; i++) {
        string u, v;
        int w;
        cin >> u >> v >> w;
        totalWeight += w;
        cout<<totalWeight;
        cout<<"\n";

        // Add unique vertices to the 'vertices' set
        if (find(vertices.begin(), vertices.end(), u) == vertices.end()) {
            vertices.push_back(u);
            temp[u] = in;
            in++;
        }
        if (find(vertices.begin(), vertices.end(), v) == vertices.end()) {
            vertices.push_back(v);
            temp[v] = in;
            in++;
        }

        edges.insert({w, {u, v}});
    }
}

void primMST() {
    int parent[numVertices];
    int key[numVertices];
    bool mstSet[numVertices];

    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX, mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = -1;

        // Find the vertex with the minimum key value that is not yet included in MST
        for (int v = 0; v < numVertices; v++) {
            if (!mstSet[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices
        for (int v = 0; v < numVertices; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    cout << "Minimum Spanning Tree:\n";
    for (int i = 1; i < numVertices; i++) {
        cout << vertices[parent[i]] << " - " << vertices[i] << "  Weight: " << graph[parent[i]][i] << "\n";
        optweight+=graph[parent[i]][i];
    }
}

int main() {
    getInput();
    cout << "Index:" << in << endl;
    for (auto it : vertices) {
        cout << temp[it] << " " << it << endl;
    }
    for (int i = 0; i < numVertices; i++) {
        for (int k = 0; k < numVertices; k++) {
            graph[i][k] = 0;
        }
    }
    for (auto it : edges) {
        graph[temp[it.second.first]][temp[it.second.second]] = it.first;
        graph[temp[it.second.second]][temp[it.second.first]] = it.first;
    }
    for (int i = 0; i < numVertices; i++) {
        for (int k = 0; k < numVertices; k++) {
            cout << graph[i][k] << " ";
        }
        cout << endl;
    }

    primMST();
    cout<<endl;

    cout<<"Optimized weight: "<<optweight<<endl;

    cout<<"Amount can be saved: "<<totalWeight-optweight<<endl;

    return 0;
}
