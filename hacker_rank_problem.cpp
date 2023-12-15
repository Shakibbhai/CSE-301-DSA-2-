#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int to, length, destructionCost;
};

struct Node {
    int vertex, distance;
};

struct CompareNode {
    bool operator()(const Node& a, const Node& b) {
        return a.distance > b.distance;
    }
};

int findShortestPath(int N, const vector<vector<Edge>>& graph) {
    priority_queue<Node, vector<Node>, CompareNode> pq;
    vector<int> distance(N + 1, INT_MAX);
    vector<bool> visited(N + 1, false);

    distance[1] = 0;
    pq.push({1, 0});

    while (!pq.empty()) {
        int u = pq.top().vertex;
        pq.pop();

        if (visited[u]) continue;

        visited[u] = true;

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int newDistance = distance[u] + edge.length;

            if (newDistance < distance[v]) {
                distance[v] = newDistance;
                pq.push({v, newDistance});
            }
        }
    }

    return distance[N];
}

int findMinimumCost(int N, const vector<vector<Edge>>& graph, int shortestPath) {
    int minCost = INT_MAX;

    for (int u = 1; u <= N; ++u) {
        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int destroyedPath = findShortestPath(N, graph);
            int cost = edge.destructionCost + destroyedPath - shortestPath;

            minCost = min(minCost, cost);
        }
    }

    return minCost;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<Edge>> graph(N + 1);

    for (int i = 0; i < M; ++i) {
        int X, Y, D, C;
        cin >> X >> Y >> D >> C;

        graph[X].push_back({Y, D, C});
        graph[Y].push_back({X, D, C});
    }

    int shortestPath = findShortestPath(N, graph);
    int result = findMinimumCost(N, graph, shortestPath);

    cout << result << endl;

    return 0;
}

/*#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

struct Edge {
    int to, length, destructionCost;
};

struct Node {
    int vertex, distance;
};

struct CompareNode {
    bool operator()(const Node& a, const Node& b) {
        return a.distance > b.distance;
    }
};

int findShortestPath(int N, const vector<vector<Edge>>& graph) {
    priority_queue<Node, vector<Node>, CompareNode> pq;
    vector<int> distance(N + 1, INT_MAX);
    vector<bool> visited(N + 1, false);

    distance[1] = 0;
    pq.push({1, 0});

    while (!pq.empty()) {
        int u = pq.top().vertex;
        pq.pop();

        if (visited[u]) continue;

        visited[u] = true;

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int newDistance = distance[u] + edge.length;

            if (newDistance < distance[v]) {
                distance[v] = newDistance;
                pq.push({v, newDistance});
            }
        }
    }

    return distance[N];
}

int findMinimumCost(int N, const vector<vector<Edge>>& graph, int shortestPath) {
    int minCost = INT_MAX;

    for (int u = 1; u <= N; ++u) {
        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int destroyedPath = findShortestPath(N, graph);
            int cost = edge.destructionCost + destroyedPath - shortestPath;

            minCost = min(minCost, cost);
        }
    }

    return minCost;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<Edge>> graph(N + 1);

    for (int i = 0; i < M; ++i) {
        int X, Y, D, C;
        cin >> X >> Y >> D >> C;

        graph[X].push_back({Y, D, C});
        graph[Y].push_back({X, D, C});
    }

    int shortestPath = findShortestPath(N, graph);
    int result = findMinimumCost(N, graph, shortestPath);

    cout << result << endl;

    return 0;
}
*/
