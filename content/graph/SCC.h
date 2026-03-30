
/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Converts Graph into a DAG.
 * Time: $O(|V|+|E|)$
 * Status: stress-tested
 */

void dfs(int u, vector<vector<int>> &g, vector<int> &visited, stack<int> &s) {
    visited[u] = 1;
    for(auto v : g[u]) {
        if(!visited[v]) dfs(v, g, visited, s);
    }
    s.push(u);
}

void dfs1(int u, vector<vector<int>> &g_dash, vector<int> &visited, int scc, vector<int> &res) {
    visited[u] = 1;
    res[u] = scc;
    for(auto v : g_dash[u]) {
        if(!visited[v]) dfs1(v, g_dash, visited, scc, res);
    }
}
vector<int> kosaraju(int n, vector<vector<int>> &g) {
    stack<int> s;
    vector<int> visited(n + 1, 0);
    for(int i = 1; i <= n; i++) {
        if(!visited[i]) dfs(i, g, visited, s);
    }
    vector<vector<int>> g_dash(n + 1);
    for(int i = 1; i <= n; i++) {
        for(auto v : g[i]) g_dash[v].push_back(i);
    }
    fill(visited.begin(), visited.end(), 0);
    vector<int> res(n + 1, 0);
    int scc_count = 0;
    
    while(!s.empty()) {
        int node = s.top();
        s.pop();
        if(!visited[node]) {
            scc_count++;
            dfs1(node, g_dash, visited, scc_count, res);
        }
    }
    return res;
}

