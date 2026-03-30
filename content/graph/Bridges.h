
/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Description: Find Bridges
 * Time: O(V+E)
 * Status: Tested on kattis:shortestpath3
 */


void dfs_bridges(int u, int p, vector<pair<int, int>>& bridges) {
    tin[u] = low[u] = ++timer;
    
    for (int v : adj[u]) {
        if (v == p) continue;
        if (tin[v] != -1) {
            low[u] = min(low[u], tin[v]);
        } else {
            dfs_bridges(v, u, bridges);
            low[u] = min(low[u], low[v]);
            
            // Bridge condition: no path from v to u or above
            if (low[v] > tin[u]) {
                bridges.push_back({u, v});
            }
        }
    }
}