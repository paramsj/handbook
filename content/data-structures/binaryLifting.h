/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Useful for LCA and querying on paths of the tree
 * Status: Stress-tested
 */

const int N = 200005;
const int LOG = 22;
int parent[N+1][LOG+1];
int query[N+1][LOG+1];
void dfs(int u,int par,vector<vector<int>> &g,vector<int> &depth) {
   parent[u][0] = par; // can add query info here
   query[u][0] = ;// some info
   for(auto v : g[u]) {
       if(v!=par) {
           depth[v] = depth[u] + 1;
           dfs(v,u,g,depth);
       }
   }
}
int merge(int a,int b,vector<int> &depth) {
   if(depth[a]<depth[b]) {
       swap(a,b);
   }
   int ans = 1e18;
   int k = depth[a] - depth[b];
   for(int i=0;i<LOG;i++) {
       if(k&(1LL<<i)) {
           ans = min(ans,query[a][i]);
           a = parent[a][i]; // can add query info here
       }
   }
   if(a==b) {
       return a;
   }
   for(int i=LOG;i>=0;i--) {
       if(parent[a][i]!=parent[b][i]) {
           ans = min(ans,query[a][i]);
           ans = min(ans,query[b][i]);
           a = parent[a][i];
           b = parent[b][i]; // can add query info here
       }
   }
   ans = min(ans,query[a][0]);
   ans = min(ans,query[b][0]);
   return ans; // lca will be parent[a][0]
}
// Usage :
dfs(1,0,g,depth);
for(int i=1;i<=LOG;i++) {
    for(int j=1;j<=n;j++) {
        parent[j][i] = parent[parent[j][i-1]][i-1]; // here query also
        query[j][i] = min(query[j][i-1],query[parent[j][i-1]][i-1]);
    }
}
