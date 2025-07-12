class Cent {
  public:
    int n;
    vi co, cent;
    vvi G;
    Cent(int size) {
        n = size;
        G = vvi(n);
    }
    void add_edge(int a, int b) {
        G[a].pb(b);
        G[b].pb(a);
    }
    void dfs(int u, int prev) {
        co[u] = 1;
        bool is_cent = true;
        for (auto v : G[u])
            if (v != prev) {
                dfs(v, u);
                co[u] += co[v];
                if (co[v] > n / 2)
                    is_cent = false;
            }
        if (n - co[u] > n / 2)
            is_cent = false;
        if (is_cent)
            cent.pb(u);
    }
    vi center() {
        co = vi(n);
        cent = vi();
        dfs(0, -1);
        return cent;
    }
};
signed main() {
    int n;
    cin >> n;
    Cent ce(n);
    rep(i, n - 1) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        ce.add_edge(a, b);
    }
    vi cent = ce.center(), co = ce.co;
}
