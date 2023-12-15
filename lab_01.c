#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int chocolates[MAX_N];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &chocolates[i]);
    }

    int friends[MAX_N][MAX_N] = {0};

    for (int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        friends[x - 1][y - 1] = 1;
        friends[y - 1][x - 1] = 1;
    }

    int visited[MAX_N] = {0};
    int min_chocolates = 0;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int queue[MAX_N];
            int front = 0, rear = 0;

            queue[rear++] = i;
            visited[i] = 1;

            int min_choco_for_group = chocolates[i];

            while (front < rear) {
                int current = queue[front++];
                for (int friend_id = 0; friend_id < n; ++friend_id) {
                    if (!visited[friend_id] && friends[current][friend_id]) {
                        queue[rear++] = friend_id;
                        visited[friend_id] = 1;
                        min_choco_for_group = (chocolates[friend_id] < min_choco_for_group) ? chocolates[friend_id] : min_choco_for_group;
                    }
                }
            }

            min_chocolates += min_choco_for_group;
        }
    }

    printf("%d\n", min_chocolates);

    return 0;
}
