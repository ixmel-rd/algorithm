// ARC090 D
class UnionFind {
  public:
    vi parent;
    vi dist;
    UnionFind(int x = 1) {
        parent = vi(x, -1);
        dist = vi(x);
    }
    int find(int x) {
        if (parent[x] < 0)
            return x;
        int r = find(parent[x]);
        dist[x] += dist[parent[x]];
        return parent[x] = r;
    }
    Def depth(int x) {
        find(x);
        return dist[x];
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) { return -parent[find(x)]; }
    void unite(int x, int y, Def k = 0) {
        k += depth(y);
        k -= depth(x);
        k *= -1;
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        if (size(x) < size(y)) {
            swap(x, y);
            k *= -1;
        }
        parent[x] += parent[y];
        parent[y] = x;
        dist[y] = k;
    }
    int diff(int x, int y) { return depth(x) - depth(y); }
};
int main() {
    int n, q;
    cin >> n >> q;
    UnionFind uf(n);
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        if (uf.same(a, b)) {
            if (uf.diff(a, b) != c) {
                cout << "No" << endl;
                return 0;
            }
        } else
            uf.unite(a, b, c);
    }
    cout << "Yes" << endl;
}
