class LCA {
  public:
    int N, root, max_log;
    vvi G, parent;
    vi depth;
    LCA(int size) {
        N = size;
        G = vvi(size);
        max_log = 20;
        depth = vi(size);
        parent = vvi(max_log, vi(size));
    }
    void add_edge(int a, int b) {
        G[a].pb(b);
        G[b].pb(a);
    }
    void dfs(int v, int p, int d) {
        parent[0][v] = p;
        depth[v] = d;
        rep(i, G[v].size()) if (G[v][i] != p) dfs(G[v][i], v, d + 1);
    }
    void init() {
        root = 0;
        dfs(root, -1, 0);
        for (int k = 0; k + 1 < max_log; k++) { // doubling
            for (int v = 0; v < N; v++) {
                if (parent[k][v] < 0)
                    parent[k + 1][v] = -1;
                else
                    parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
    }
    int lca(int u, int v) {
        if (depth[u] > depth[v])
            swap(u, v);
        rep(k, max_log) if ((depth[v] - depth[u]) >> k & 1) v = parent[k][v];
        if (u == v)
            return u;
        for (int k = max_log - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
};
