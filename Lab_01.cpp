#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

int main() {
    long long int n, m,i;
    cin >> n >> m;

    vector<long long int> chocolates(n);
    for (i = 0; i < n; ++i) {
        cin >> chocolates[i];
    }

    vector<set<long long int>> friends(n);

    for (i = 0; i < m; ++i) {
        long long int x, y;
        cin >> x >> y;
        friends[x - 1].insert(y - 1);
        friends[y - 1].insert(x - 1);
    }

    vector<bool> visited(n, false);
    long long int min_chocolates = 0;

    for (i = 0; i < n; ++i) {
        if (!visited[i]) {
            queue<long long int> bfs;
            bfs.push(i);
            visited[i] = true;

            long long int min_choco_for_group = chocolates[i];

            while (!bfs.empty()) {
                int current = bfs.front();
                bfs.pop();

                for (long long int friend_id : friends[current]) {
                    if (!visited[friend_id]) {
                        bfs.push(friend_id);
                        visited[friend_id] = true;
                        min_choco_for_group = min(min_choco_for_group, chocolates[friend_id]);
                    }
                }
            }

            min_chocolates += min_choco_for_group;
        }
    }

    cout << min_chocolates << endl;

    return 0;
}
