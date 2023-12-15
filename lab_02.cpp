#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> chocolates(n);
    for (int i = 0; i < n; ++i) {
        cin >> chocolates[i];
    }

    vector<vector<int>> adjList(n);
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        adjList[x - 1].push_back(y - 1);
        adjList[y - 1].push_back(x - 1);
    }

    vector<bool> visited(n, false);
    int minChocolates = 0;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            queue<int> bfsQueue;
            bfsQueue.push(i);
            visited[i] = true;

            int minChocolateInGroup = chocolates[i];

            while (!bfsQueue.empty()) {
                int current = bfsQueue.front();
                bfsQueue.pop();

                for (int neighbor : adjList[current]) {
                    if (!visited[neighbor]) {
                        bfsQueue.push(neighbor);
                        visited[neighbor] = true;
                        minChocolateInGroup = min(minChocolateInGroup, chocolates[neighbor]);
                    }
                }
            }

            minChocolates += minChocolateInGroup;
        }
    }

    cout << minChocolates << endl;

    return 0;
}
