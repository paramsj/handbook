/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Description: Find Articulation Points
 * Time: O(V+E)
 * Status: Tested on kattis:shortestpath3
 */

void dfs_ap(int u, int p, vector<bool>& is_ap) {
    tin[u] = low[u] = ++timer;
    int children = 0;
    
    for (int v : adj[u]) {
        if (v == p) continue;
        if (tin[v] != -1) {
            // Back-edge: v was visited before u
            low[u] = min(low[u], tin[v]);
        } else {
            // Tree-edge
            children++;
            dfs_ap(v, u, is_ap);
            low[u] = min(low[u], low[v]);
            
            // If not root and child v has no back-edge to u or above
            if (p != -1 && low[v] >= tin[u]) {
                is_ap[u] = true;
            }
        }
    }
    // Special case: root is an AP if it has more than 1 child in DFS tree
    if (p == -1 && children > 1) {
        is_ap[u] = true;
    }
}