
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define MAX 10
#define CITY_NAME_LENGTH 20

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

// Function to print the path based on parent array
void printPath(int parent[], int j, char city[MAX][CITY_NAME_LENGTH]) {
    if (parent[j] == -1) {
        printf("%s", city[j]);
        return;
    }

    printPath(parent, parent[j], city);
    printf(" -> %s", city[j]);
}

// Function to print the MST and the path
void printMSTWithStart(int parent[], int graph[MAX][MAX], int vertices, char city[MAX][CITY_NAME_LENGTH], int start, int end) {
    int minCost = 0;

    printf("Path: ");
    printPath(parent, end, city);
    printf("\n");

    printf("Edge \tWeight\n");
    for (int i = 1; i < vertices; i++) {
        printf("%s - %s \t%d \n", city[parent[i]], city[i], graph[i][parent[i]]);
        minCost += graph[i][parent[i]];
    }
    printf("Minimum cost is: %d\n", minCost);
}

// Function to construct and print MST for a graph represented using adjacency matrix representation
void primMST(int graph[MAX][MAX], int vertices, char city[MAX][CITY_NAME_LENGTH], int start, int end) {
    int parent[MAX];  // Array to store constructed MST
    int key[MAX];     // Key values used to pick minimum weight edge in cut
    bool mstSet[MAX]; // To represent set of vertices not yet included in MST

    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[start] = 0;
    parent[start] = -1;

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

    printMSTWithStart(parent, graph, vertices, city, start, end);
}

int main() {
    int n, k;
    FILE *file;
    file = fopen("start+end_input.txt", "r");

    if (file == NULL) {
        printf("File not found or unable to open.\n");
        return 1;
    }

    fscanf(file, "%d", &n);

    char city[MAX][CITY_NAME_LENGTH];

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s", city[i]);
    }

    int graph[MAX][MAX];
    memset(graph, 0, sizeof(graph)); // Initialize the graph matrix

    fscanf(file, "%d", &k);

    for (int i = 0; i < k; i++) {
        char source[CITY_NAME_LENGTH], dest[CITY_NAME_LENGTH];
        int cost;
        fscanf(file, "%s %s %d", source, dest, &cost);

        int sourceIndex = -1, destIndex = -1;

        for (int j = 0; j < n; j++) {
            if (strcmp(city[j], source) == 0) sourceIndex = j;
            if (strcmp(city[j], dest) == 0) destIndex = j;
        }

        if (sourceIndex != -1 && destIndex != -1) {
            graph[sourceIndex][destIndex] = cost;
            graph[destIndex][sourceIndex] = cost; // Considering undirected graph
        } else {
            printf("Invalid city names\n");
            return 0;
        }
    }

    fclose(file); // Close the file after reading

    int start, end;
    printf("Enter the starting country index: ");
    scanf("%d", &start);

    printf("Enter the ending country index: ");
    scanf("%d", &end);

    if (start < 0 || start >= n || end < 0 || end >= n) {
        printf("Invalid country indices\n");
        return 0;
    }

    primMST(graph, n, city, start, end);

    return 0;
}
