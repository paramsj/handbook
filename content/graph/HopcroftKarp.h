/**
 * Author: Adam Soltan
 * Date: 2026-01-13
 * License: CC0
 * Description: Description: Fast bipartite matching algorithm. Graph $adj$ should be a list of neighbors of the left partition, and $matchR$ should be an array of size $M$ initialized to $0$. Returns the size of the matching in $O(E\sqrt{V})$. $matchR[i]$ will be the match for vertex $i$ on the right side, or $0$ if it is not matched.
 * Time: O(E \sqrt{V})
 * Status: stress-tested by MinimumVertexCover and tested on Library Checker
 */


vector<int> adj[MAXN];
int matchL[MAXN], matchR[MAXM], dist[MAXN];
int n, m; // n: size of U, m: size of V

bool bfs() {
    queue<int> q;
    for (int u = 1; u <= n; u++) {
        if (matchL[u] == 0) {
            dist[u] = 0;
            q.push(u);
        } else {
            dist[u] = INF;
        }
    }
    dist[0] = INF;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (dist[u] < dist[0]) {
            for (int v : adj[u]) {
                if (dist[matchR[v]] == INF) {
                    dist[matchR[v]] = dist[u] + 1;
                    q.push(matchR[v]);
                }
            }
        }
    }
    return dist[0] != INF;
}

bool dfs(int u) {
    if (u != 0) {
        for (int v : adj[u]) {
            if (dist[matchR[v]] == dist[u] + 1) {
                if (dfs(matchR[v])) {
                    matchR[v] = u;
                    matchL[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int hopcroft_karp() {
    int matching = 0;
    // Reset matches
    for (int i = 0; i <= n; i++) matchL[i] = 0;
    for (int i = 0; i <= m; i++) matchR[i] = 0;

    while (bfs()) {
        for (int u = 1; u <= n; u++) {
            if (matchL[u] == 0 && dfs(u)) {
                matching++;
            }
        }
    }
    return matching;
}