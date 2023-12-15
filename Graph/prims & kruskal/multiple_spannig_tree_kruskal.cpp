#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_set>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    string source, destination;
    int weight;
};

// Structure to represent a disjoint set
struct DisjointSet {
    map<string, int> cityToId;
    int *parent, *rank;
    int n;

    DisjointSet(map<string, int>& cityMap) {
        cityToId = cityMap;
        this->n = cityMap.size();
        parent = new int[n];
        rank = new int[n];

        // Initialize parent and rank
        for (auto &city : cityMap) {
            parent[city.second] = city.second;
            rank[city.second] = 0;
        }
    }

    // Find set of an element (uses path compression technique)
    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    // Union by rank
    void merge(int x, int y) {
        x = find(x);
        y = find(y);

        if (rank[x] > rank[y]) {
            parent[y] = x;
        } else {
            parent[x] = y;
            if (rank[x] == rank[y]) {
                rank[y]++;
            }
        }
    }
};

// Kruskal's algorithm to find Minimum Spanning Tree
void kruskalMST(int numCities, vector<Edge>& edges, map<string, int>& cityMap) {
    DisjointSet ds(cityMap);

    // Sort edges in ascending order based on their weights
    sort(edges.begin(), edges.end(), [](Edge &a, Edge &b) {
        return a.weight < b.weight;
    });

    int totalCost = 0;
    unordered_set<string> visited;
    vector<int> componentCosts;

    for (Edge &edge : edges) {
        int sourceId = cityMap[edge.source];
        int destId = cityMap[edge.destination];

        int sourceParent = ds.find(sourceId);
        int destinationParent = ds.find(destId);

        if (sourceParent != destinationParent) {
            visited.insert(edge.source);
            visited.insert(edge.destination);
            totalCost += edge.weight;
            ds.merge(sourceParent, destinationParent);
        }
    }

    if (!visited.empty()) {
        componentCosts.push_back(totalCost);
        totalCost = 0;
    }

    for (Edge &edge : edges) {
        int sourceId = cityMap[edge.source];
        int destId = cityMap[edge.destination];

        int sourceParent = ds.find(sourceId);
        int destinationParent = ds.find(destId);

        if (sourceParent != destinationParent) {
            visited.insert(edge.source);
            visited.insert(edge.destination);
            totalCost += edge.weight;
            ds.merge(sourceParent, destinationParent);
            componentCosts.push_back(edge.weight);
        }
    }

    cout << "Total cost of the network: " << totalCost << endl;

    int componentNum = 1;
    int start = 0;
    for (int i = 0; i < visited.size(); ++i) {
        if (visited.find(cityMap.begin()->first) != visited.end()) {
            start = i;
            break;
        }
    }

    for (int i = start; i < visited.size(); ++i) {
        if (visited.find(cityMap.begin()->first) != visited.end()) {
            cout << "For the " << componentNum << " connected component:" << endl;
            cout << "The minimum cost to build the network is:" << endl;
            for (int j = start; j < visited.size(); ++j) {
                for (int k = start; k < visited.size(); ++k) {
                    if (componentCosts[j] == edges[k].weight) {
                        cout << "Connecting " << edges[k].source << " to " << edges[k].destination << " with cost " << edges[k].weight << endl;
                    }
                }
            }
            cout << "Total cost: " << componentCosts[i] << endl;
            ++componentNum;
        }
    }
}

int main() {
    int numCities, numEdges;
    map<string, int> cityMap;
    vector<Edge> edges;

    ifstream file("prev_lav.txt"); // Change "input.txt" to your file name

    if (file.is_open()) {
        file >> numCities;

        for (int i = 0; i < numCities; ++i) {
            string city;
            file >> city;
            cityMap[city] = i;
        }

        file >> numEdges;

        for (int i = 0; i < numEdges; ++i) {
            string source, destination;
            int weight;
            file >> source >> destination >> weight;
            edges.push_back({source, destination, weight});
        }

        file.close();

        kruskalMST(numCities, edges, cityMap);
    } else {
        cout << "Unable to open file" << endl;
    }

    return 0;
}
