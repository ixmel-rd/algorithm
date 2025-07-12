struct edge {
    int to, cost;
};
class DIA { // diameter of tree
  public:
    vector<vector<edge>> G;
    vi d;
    vector<bool> vis;
    int n;
    DIA(int size) {
        n = size;
        G = vector<vector<edge>>(n);
        d = vi(n);
        vector<bool> vis(n);
    }
    void add_edge(int a, int b, int c) {
        edge e = {b, c}, ee = {a, c};
        G[a].pb(e);
        G[b].pb(ee);
    }
    void bfs(int s) {
        d = vi(n, inf);
        queue<int> q;
        q.push(s);
        d[s] = 0;
        int u;
        while (!q.empty()) {
            u = q.front();
            q.pop();
            rep(i, G[u].size()) {
                edge e = G[u][i];
                if (d[e.to] == inf) {
                    d[e.to] = d[u] + e.cost;
                    q.push(e.to);
                }
            }
        }
    }
    void dia() {
        bfs(0);
        int maxv = 0, tgt = 0;
        rep(i, n) if (d[i] != inf && maxv < d[i]) {
            maxv = d[i];
            tgt = i;
        }
        bfs(tgt);
        maxv = 0;
        rep(i, n) if (d[i] != inf) maxv = max(maxv, d[i]);
        cout << maxv << endl;
    }
};
int main() {
    int n;
    cin >> n;
    DIA dia(n);
    rep(i, n - 1) {
        int s, t, w;
        cin >> s >> t >> w;
        dia.add_edge(s, t, w);
    }
    dia.dia();
}