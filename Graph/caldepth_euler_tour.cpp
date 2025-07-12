class CalDepth {
  public:
    int n;
    vvi G;
    vi l, r;
    vi dep, tour;
    CalDepth(int size) {
        n = size;
        G = vvi(n);
    }
    void add_edge(int a, int b) {
        G[a].pb(b);
        G[b].pb(a);
    }
    void bfs(int s) {
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int a = q.front();
            q.pop();
            rep(i, G[a].size()) {
                int to = G[a][i];
                if (dep[to] > dep[a] + 1) {
                    dep[to] = dep[a] + 1;
                    q.push(to);
                }
            }
        }
    }
    void dfs(int a) {
        tour.pb(a);
        rep(i, G[a].size()) {
            int to = G[a][i];
            if (dep[to] > dep[a])
                dfs(to);
        }
        tour.pb(a);
    }
    vi caldepth(int s) {
        dep = vi(n, inf);
        dep[s] = 0;
        bfs(s);
        return dep;
    }
    void eulertour(int s) {
        l = vi(n, n);
        r = vi(n);
        tour.clear();

        caldepth(s);
        dfs(s);

        rep(i, tour.size()) {
            cmin(l[tour[i]], i);
            cmax(r[tour[i]], i);
        }

        // return l,r,tour [l,r]
    }
    void et(int s) { eulertour(s); }
};
