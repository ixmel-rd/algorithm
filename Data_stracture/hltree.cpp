class HeavyLight {
  public:
    int pathCount, n;
    vi size, parent, in, out, path, pathRoot;
    vvi tree;

    HeavyLight(vvi t)
        : pathCount(0), n(t.size()), size(n), parent(n), in(n), out(n), path(n),
          pathRoot(n), tree(t) {
        int time = 0;
        dfs(0, -1, time);
        buildPaths(0, newPath(0));
    }
    void dfs(int u, int p, int &k) {
        in[u] = k++, parent[u] = p, size[u] = 1;
        for (auto v = tree[u].begin(); v != tree[u].end(); v++)
            if (*v != p)
                dfs(*v, u, k), size[u] += size[*v];
        out[u] = k++;
    }
    int newPath(int u) {
        pathRoot[pathCount] = u;
        return pathCount++;
    }
    void buildPaths(int u, int pt) {
        path[u] = pt;
        for (auto v = tree[u].begin(); v != tree[u].end(); v++)
            if (*v != parent[u]) {
                buildPaths(*v, 2 * size[*v] >= size[u] ? pt : newPath(*v));
            }
    }
    bool inAncestor(int p, int ch) {
        return in[p] <= in[ch] && out[ch] <= out[p];
    }
    int lca(int a, int b) {
        for (int root; !inAncestor(root = pathRoot[path[a]], b);
             a = parent[root])
            ;
        for (int root; !inAncestor(root = pathRoot[path[b]], a);
             b = parent[root])
            ;
        return inAncestor(a, b) ? a : b;
    }
};