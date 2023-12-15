#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int N = 100; // Maximum number of nodes
const int INF = INT_MAX;

struct Edge {
    int to, capacity, flow;
};

vector<Edge> graph[N];
vector<int> parent(N);

// Add an edge to the graph.
void addEdge(int from, int to, int capacity) {
    graph[from].push_back({to, capacity, 0});
    graph[to].push_back({from, capacity, 0});
}

// Ford-Fulkerson algorithm using BFS.
int fordFulkerson(int source, int sink) {
    int maxFlow = 0;

    while (true) {
        fill(parent.begin(), parent.end(), -1);
        queue<pair<int, int>> q;
        q.push({source, INF});

        while (!q.empty()) {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (Edge &e : graph[cur]) {
                if (parent[e.to] == -1 && e.capacity - e.flow > 0) {
                    int newFlow = min(flow, e.capacity - e.flow);
                    parent[e.to] = cur;
                    if (e.to == sink) {
                        maxFlow += newFlow;
                        int v = e.to;
                        while (v != source) {
                            int u = parent[v];
                            for (Edge &backEdge : graph[u]) {
                                if (backEdge.to == v) {
                                    backEdge.flow += newFlow;
                                    break;
                                }
                            }
                            for (Edge &forwardEdge : graph[v]) {
                                if (forwardEdge.to == u) {
                                    forwardEdge.flow -= newFlow;
                                    break;
                                }
                            }
                            v = u;
                        }
                        break;
                    }
                    q.push({e.to, newFlow});
                }
            }
        }

        if (parent[sink] == -1)
            break;
    }

    return maxFlow;
}

int main() {
    int n, s, t, e;
    cin >> n;
    cin >> s >> t >> e;

    for (int i = 0; i < e; i++) {
        int u, v, capacity;
        cin >> u >> v >> capacity;
        addEdge(u, v, capacity);
    }

    int maxFlow = fordFulkerson(s, t);
    cout << "The bandwidth is " << maxFlow << endl;

    return 0;
}

