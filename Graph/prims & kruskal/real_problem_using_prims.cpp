#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define MAX 10
#define CITY_NAME_LENGTH 50

// Function to find the minimum key value vertex from the set of vertices
int minKey(int key[], bool mstSet[], int vertices) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < vertices; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the MST using the constructed array parent[]
void printMST(int parent[], int graph[MAX][MAX], int vertices, char city[MAX][CITY_NAME_LENGTH]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < vertices; i++) {
        printf("%s - %s \t%d \n", city[parent[i]], city[i], graph[i][parent[i]]);
    }
}

// Function to construct and print MST for a graph represented using adjacency matrix representation
void primMST(int graph[MAX][MAX], int vertices, char city[MAX][CITY_NAME_LENGTH]) {
    int parent[MAX];  // Array to store constructed MST
    int key[MAX];     // Key values used to pick minimum weight edge in cut
    bool mstSet[MAX]; // To represent set of vertices not yet included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Always include first 0th vertex in MST.
    key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always the root of MST

    for (int count = 0; count < vertices - 1; count++) {
        int u = minKey(key, mstSet, vertices);
        mstSet[u] = true;

        for (int v = 0; v < vertices; v++) {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, vertices, city);

    // Calculate total minimum cost
    int totalMinCost = 0;
    for (int i = 1; i < vertices; i++) {
        totalMinCost += graph[i][parent[i]];
    }
    printf("Total Minimum Cost: %d\n", totalMinCost);
}

int main() {
    FILE *file;
    file = fopen("for_prims_vertex_fixed.txt", "r"); // Assuming input is in a file named for_prims.txt

    int n, i, j, k, cost;
    char city[MAX][CITY_NAME_LENGTH];
    int graph[MAX][MAX];

    if (file == NULL) {
        printf("File not found or unable to open.\n");
        return 1;
    }

    fscanf(file, "%d", &n);

    for (i = 0; i < n; i++) {
        fscanf(file, "%s", city[i]);
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    fscanf(file, "%d", &k);

    for (i = 0; i < k; i++) {
        char source[CITY_NAME_LENGTH], dest[CITY_NAME_LENGTH];
        fscanf(file, "%s %s %d", source, dest, &cost);

        int sourceIndex = -1, destIndex = -1;

        for (j = 0; j < n; j++) {
            if (strcmp(city[j], source) == 0) {
                sourceIndex = j;
            }
            if (strcmp(city[j], dest) == 0) {
                destIndex = j;
            }
        }

        if (sourceIndex != -1 && destIndex != -1) {
            graph[sourceIndex][destIndex] = cost;
            graph[destIndex][sourceIndex] = cost; // Considering undirected graph
        } else {
            printf("Invalid city names\n");
            return 0;
        }
    }

    fclose(file);

    primMST(graph, n, city);

    return 0;
}
