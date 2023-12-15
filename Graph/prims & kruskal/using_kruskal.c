#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CITIES 50
#define MAX_LEN 20

// Structure to represent an edge in the graph
struct Edge {
    int source, destination, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

void kruskalMST(int numCities, int numEdges, struct Edge edges[]) {
    struct Edge result[numCities];
    int e = 0;
    int i = 0;

    // Sort all the edges in non-decreasing order of their weight
    for (i = 0; i < numEdges; ++i) {
        for (int j = i + 1; j < numEdges; ++j) {
            if (edges[i].weight > edges[j].weight) {
                struct Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }

    // Allocate memory for creating subsets
    struct Subset *subsets = (struct Subset *)malloc(numCities * sizeof(struct Subset));

    // Create subsets for each city
    for (i = 0; i < numCities; ++i) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    i = 0;

    // Construct the MST
    while (e < numCities - 1) {
        struct Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.source);
        int y = find(subsets, next_edge.destination);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    int minimumCost = 0;
    printf("The minimum cost to build the network is:\n");
    for (i = 0; i < e; ++i) {
        printf("Connecting %d to %d with cost %d\n", result[i].source, result[i].destination, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Total cost: %d\n", minimumCost);
    free(subsets);
}

int main() {
    int numCities, numEdges;
    struct Edge edges[MAX_CITIES];
    char cities[MAX_CITIES][MAX_LEN];

    printf("Enter the number of cities: ");
    scanf("%d", &numCities);

    printf("Enter the city names:\n");
    for (int i = 0; i < numCities; ++i) {
        scanf("%s", cities[i]);
    }

    printf("Enter the number of connections: ");
    scanf("%d", &numEdges);

    printf("Enter connections in the format 'source destination weight':\n");
    for (int i = 0; i < numEdges; ++i) {
        char source[MAX_LEN], destination[MAX_LEN];
        int weight;
        scanf("%s %s %d", source, destination, &weight);

        int srcIndex, destIndex;
        for (int j = 0; j < numCities; ++j) {
            if (strcmp(cities[j], source) == 0) {
                srcIndex = j;
            }
            if (strcmp(cities[j], destination) == 0) {
                destIndex = j;
            }
        }

        edges[i].source = srcIndex;
        edges[i].destination = destIndex;
        edges[i].weight = weight;
    }

    kruskalMST(numCities, numEdges, edges);

    return 0;
}
