#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

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

    int minimumCost = 0;
    vector<Edge> result;

    for (Edge &edge : edges) {
        int sourceId = cityMap[edge.source];
        int destId = cityMap[edge.destination];

        int sourceParent = ds.find(sourceId);
        int destinationParent = ds.find(destId);

        if (sourceParent != destinationParent) {
            result.push_back(edge);
            minimumCost += edge.weight;
            ds.merge(sourceParent, destinationParent);
        }
    }

    cout << "The minimum cost to build the network is:" << endl;
    for (Edge &edge : result) {
        cout << "Connecting " << edge.source << " to " << edge.destination << " with cost " << edge.weight << endl;
    }
    cout << "Total cost: " << minimumCost << endl;
}

int main() {
    int numCities, numEdges,weight;
    string city, source, destination;
    map<string, int> cityMap;
    vector<Edge> edges;
                    ifstream file("newwork.txt");
         if (file.is_open()) {
        file >> numCities;

        for (int i = 0; i < numCities; ++i) {
            file >> city;
            cityMap[city] =i;
        }
        file >> numEdges;

        for (int i = 0; i < numEdges; ++i) {
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
