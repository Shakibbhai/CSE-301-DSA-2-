#include <iostream>
#include <fstream>
#include <queue>
#include <climits>

using namespace std;

const int maxV = 20;
int numV, numE;
int graph[maxV][maxV] = {0};
int previous[maxV];
int residual[maxV][maxV];
bool visited[maxV];

bool bfs(int source, int sink);
int fordFulkerson(int source, int sink);
void read();
void print();

int main() {
    read();
    print();
    cout << numV << " " << numE << endl;
    cout << "Maximum Flow: " << fordFulkerson(0, 5) << endl;
}

bool bfs(int source, int sink) {
    for (int i = 0; i < numV; i++) {
        visited[i] = false;
    }
    queue<int> myQueue;
    myQueue.push(source);
    visited[source] = true;
    previous[source] = -1;

    while (!myQueue.empty()) {
        int u = myQueue.front();
        myQueue.pop();
        for (int i = 0; i < numV; i++) {
            if (!visited[i] && residual[u][i]) {
                myQueue.push(i);
                visited[i] = true;
                previous[i] = u;
            }
        }
    }
    return visited[sink];
}

int fordFulkerson(int source, int sink) {
    for (int i = 0; i < numV; i++) {
        for (int j = 0; j < numV; j++) {
            residual[i][j] = graph[i][j];
        }
    }

    int maxFlow = 0;
    while (bfs(source, sink)) {
        int minCapacity = INT_MAX;
        for (int i = sink; i != source; i = previous[i]) {
            int parent = previous[i];
            minCapacity = min(minCapacity, residual[parent][i]);
        }
        maxFlow += minCapacity;

        for (int i = sink; i != source; i = previous[i]) {
            int parent = previous[i];
            residual[parent][i] -= minCapacity;
            residual[i][parent] += minCapacity;
        }
    }
    return maxFlow;
}

void read() {
    ifstream myfile("ford.txt");
    myfile >> numV >> numE;
    int u, v, w;
    for (int i = 0; i < numE; i++) {
        myfile >> u >> v >> w;
        graph[u][v] = w;
    }
}

void print() {
    for (int i = 0; i < numV; i++) {
        for (int j = 0; j < numV; j++) {
            cout << graph[i][j] << "  ";
        }
        cout << endl;
    }
}
